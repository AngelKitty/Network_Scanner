// SnifferScan.cpp : implementation file
//

#include "stdafx.h"
#include "Scanner.h"
#include "SnifferScan.h"
#include "SSSelectIP.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include	<ws2tcpip.h>

#define MAXIP 20
#define LIST_RECEIVE_TIME 0
#define LIST_RECEIVE_PROTOCOL 1
#define LIST_RECEIVE_SOURCEIP 2
#define LIST_RECEIVE_SOURCEPORT 3
#define LIST_RECEIVE_DESTIP 4
#define LIST_RECEIVE_DESTPORT 5
#define LIST_RECEIVE_LEN 6
#define LIST_RECEIVE_CONTENT 7

#define SIO_RCVALL _WSAIOW(IOC_VENDOR,1)
#define MAX_PACK_LEN 65535
#define MAX_PACK_SAVE_LEN 3000
#define MAX_PACK_NUM 10000

int SaveBufLen[MAX_PACK_NUM];
char SaveBuf[MAX_PACK_NUM][MAX_PACK_SAVE_LEN];

typedef struct SSThreadParamStruct{
	CSnifferScan *ptr;
	CString strIP;
	BOOL g_bSSRunning;
	int iIndex;
}SSTHREADPARAM;
SSTHREADPARAM SSThreadParam[MAXIP];
CStringArray g_saKeyword;
UINT SnifferThread(LPVOID pParam);
int g_iSSThreadCount;
int g_iSSTotalNum;
/////////////////////////////////////////////////////////////////////////////
// CSnifferScan dialog


CSnifferScan::CSnifferScan(CWnd* pParent /*=NULL*/)
	: CDialog(CSnifferScan::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSnifferScan)
	m_strComment = _T("");
	m_strKeyword = _T("");
	m_strContent = _T("");
	//}}AFX_DATA_INIT
}


void CSnifferScan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSnifferScan)
	DDX_Control(pDX, IDC_LISTKeyword, m_ctlListKeyword);
	DDX_Control(pDX, IDC_LISTReceive, m_ctlListReceive);
	DDX_Text(pDX, IDC_EDITComment, m_strComment);
	DDX_Text(pDX, IDC_EDITKeyword, m_strKeyword);
	DDX_Text(pDX, IDC_EDITContent, m_strContent);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSnifferScan, CDialog)
	//{{AFX_MSG_MAP(CSnifferScan)
	ON_BN_CLICKED(IDC_BUTTONStart, OnBUTTONStart)
	ON_BN_CLICKED(IDC_BUTTONStop, OnBUTTONStop)
	ON_NOTIFY(NM_CLICK, IDC_LISTReceive, OnClickLISTReceive)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTReceive, OnDblclkLISTReceive)
	ON_BN_CLICKED(IDC_BUTTONClear, OnBUTTONClear)
	ON_BN_CLICKED(IDC_BUTTONAddKW, OnBUTTONAddKW)
	ON_BN_CLICKED(IDC_BUTTONDeleteKW, OnBUTTONDeleteKW)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSnifferScan message handlers

BOOL CSnifferScan::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//MessageBox("ok");
	m_ctlListReceive.InsertColumn(LIST_RECEIVE_TIME,"时间",LVCFMT_LEFT,50);
	m_ctlListReceive.InsertColumn(LIST_RECEIVE_PROTOCOL,"协议",LVCFMT_LEFT,50);
	m_ctlListReceive.InsertColumn(LIST_RECEIVE_SOURCEIP,"源IP",LVCFMT_LEFT,100);
	m_ctlListReceive.InsertColumn(LIST_RECEIVE_SOURCEPORT,"源端口",LVCFMT_LEFT,80);
	m_ctlListReceive.InsertColumn(LIST_RECEIVE_DESTIP,"目地IP",LVCFMT_LEFT,100);
	m_ctlListReceive.InsertColumn(LIST_RECEIVE_DESTPORT,"目地端口",LVCFMT_LEFT,80);
	m_ctlListReceive.InsertColumn(LIST_RECEIVE_LEN,"长度",LVCFMT_LEFT,50);
	m_ctlListReceive.InsertColumn(LIST_RECEIVE_CONTENT,"内容",LVCFMT_LEFT,270);
	m_ctlListReceive.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	WSADATA wsaData;
	WORD wVersion;
	wVersion = MAKEWORD(2,0);
	if(WSAStartup(wVersion,&wsaData)){
		MessageBox("套接字初始化错误！");
		return false;
	}
	
	struct 	hostent *pHost = gethostbyname("");
	if(pHost==NULL){
		MessageBox("无法获得主机名");
		return false;
	}

	g_iSSThreadCount = 0;
	for(int i=0;i<MAXIP;i++){
		char *ptrIP=pHost->h_addr_list[i];
		if(ptrIP==NULL){
			break;
		}
		LPCSTR psz=inet_ntoa(*(struct in_addr *)ptrIP);
		if(psz!=NULL){
			SSThreadParam[i].ptr = this;
			SSThreadParam[i].strIP.Format("%s",psz);
			SSThreadParam[i].g_bSSRunning = false;
			SSThreadParam[i].iIndex = g_iSSThreadCount;
			g_iSSThreadCount++;
		}else{
			break;
		}
	}
	if(g_iSSThreadCount<=0){
		MessageBox("无法将主机名转为IP地址！");
		return false;
	}
	CString strTemp;
	char buff[MAX_PATH];
	int iCount = GetPrivateProfileInt("SnifferScan","Count",0,INIFILENAME);
	for(i=0;i<iCount;i++){
		strTemp.Format("Item%d",i+1);
		GetPrivateProfileString("SnifferScan",strTemp,"",buff,MAX_PATH,INIFILENAME);
		strTemp.Format("%s",buff);
		if(strTemp=="")
			break;
		m_ctlListKeyword.AddString(strTemp);
	}
	UpdateData(false);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSnifferScan::OnBUTTONStart() 
{
	// TODO: Add your control notification handler code here
	CString strTemp;
	UpdateData(true);
	if(g_iSSThreadCount==0){
		MessageBox("本地IP地址读取出错！");
		return ;
	}
	int iSel =0;
	if(g_iSSThreadCount>=1){
		CSSSelectIP dlg;
		for(int i=0;i<g_iSSThreadCount;i++){
			dlg.strIP[i]=SSThreadParam[i].strIP;
		}
		dlg.iTotalIP =g_iSSThreadCount;
		if(dlg.DoModal()!=IDOK)
			return;
		iSel = dlg.iCurSel;
	}
		if(SSThreadParam[iSel].g_bSSRunning){
			m_strComment.Format("正在监听%s",SSThreadParam[iSel].strIP);
		}else{
			g_saKeyword.RemoveAll();
			for(int kw=0;kw<m_ctlListKeyword.GetCount();kw++){
				m_ctlListKeyword.GetText(kw,strTemp);
				strTemp.MakeUpper();
				g_saKeyword.Add(strTemp);
			}
			if(g_saKeyword.GetSize()==0){
				MessageBox("没有要监测的关键字，监测未开起！");
				return;
			}
			AfxBeginThread(SnifferThread,&SSThreadParam[iSel],THREAD_PRIORITY_NORMAL);
			m_strComment.Format("监听%s线程正在运行中...",SSThreadParam[iSel].strIP);
			Sleep(100);
		}
		UpdateData(false);
	}

UINT SnifferThread(LPVOID pParam){
	SSTHREADPARAM *threadParam=(SSTHREADPARAM *)pParam;
	CSnifferScan *ptr = threadParam->ptr;
	CString strIP = threadParam->strIP;
	CListBox *pListKeyword = (CListBox *)&ptr->m_ctlListKeyword;
	CString strTemp;

	SOCKET sock;
	SOCKADDR_IN addr_local,addr_remote;
	int buflen=sizeof(addr_remote);
	if((sock=socket(AF_INET,SOCK_RAW,IPPROTO_IP))==INVALID_SOCKET){
		AfxMessageBox("套接字创建出错");
		return 1;
	}

	BOOL flag = true;
	if(setsockopt(sock,IPPROTO_IP,IP_HDRINCL,(char *)&flag,sizeof(flag))==SOCKET_ERROR){
		AfxMessageBox("套接字选项IP_HDRINCL出错");
		shutdown(sock,2);
		return 2;
	}

	int nTimeOver=500;
	if(setsockopt(sock,SOL_SOCKET,SO_RCVTIMEO,(char *)&nTimeOver,sizeof(nTimeOver))==SOCKET_ERROR){
		AfxMessageBox("设置超时时间出错");
		shutdown(sock,2);
		closesocket(sock);
		return 3;
	}

	int localPort=GetPrivateProfileInt("SnifferScan","LocalPort",5000,INIFILENAME);
	addr_local.sin_family = AF_INET;
	addr_local.sin_port=htons(localPort);
	addr_local.sin_addr.S_un.S_addr=inet_addr(strIP);
	if(bind(sock,(PSOCKADDR)&addr_local,sizeof(addr_local))==SOCKET_ERROR){
		AfxMessageBox("绑定本地端口出错");
		shutdown(sock,2);
		closesocket(sock);
		return 4;
	}
	DWORD dwBufferLen[10];
	DWORD dwBufferInLen=1;
	DWORD dwBytesReturned=0;
	if(WSAIoctl(sock,SIO_RCVALL,&dwBufferInLen,sizeof(dwBufferInLen),&dwBufferLen,sizeof(dwBufferLen),&dwBytesReturned,NULL,NULL)==SOCKET_ERROR){
		AfxMessageBox("WSAIoctl设置出错，当羊版本不支持无线网卡");
		shutdown(sock,2);
		closesocket(sock);
		return 5;
	}

	threadParam->g_bSSRunning=true;
	g_iSSTotalNum=0;
	UCHAR RecvBuf[MAX_PACK_LEN];
	IPHEADER *pIPHead=(IPHEADER *)RecvBuf;
	int iIPLen=sizeof(IPHEADER);
	int iTcpLen=sizeof(TCPHEADER);
	int iUdpLen=sizeof(UDPHEADER);
	int iIcmpLen=sizeof(ICMPHEADER);
	TCPHEADER *pTcpHead=(TCPHEADER *)(RecvBuf+iIPLen);
	UDPHEADER *pUdpHead=(UDPHEADER *)pTcpHead;
	ICMPHEADER *pIcmpHead=(ICMPHEADER *)pTcpHead;
	char *pTcpData = (char *)(RecvBuf+iIPLen+iTcpLen);
	char *pUdpData = (char *)(RecvBuf+iIPLen+iUdpLen);
	char *pIcmpData = (char *)(RecvBuf+iIPLen+iIcmpLen);
	while(threadParam->g_bSSRunning&&g_iSSTotalNum<MAX_PACK_NUM){
		memset(RecvBuf,0,sizeof(RecvBuf));
		int retlen=recvfrom(sock,(char *)RecvBuf,MAX_PACK_LEN,0,(LPSOCKADDR)&addr_remote,&buflen);
		if(retlen==SOCKET_ERROR||retlen<50)
			continue;

		strTemp="";
		for(int vc=0;vc<retlen;vc++){
			UCHAR uc=RecvBuf[vc];
			if(uc>31&&uc<128){
				if(uc>'a'-1 && uc<'z'+1){
					uc=uc-'a'+'A';
				}
				strTemp+=uc;
			}
		}
		BOOL bHavePass=false;
		for(int pw=0;pw<g_saKeyword.GetSize();pw++){
			if(strTemp.Find(g_saKeyword.GetAt(pw))>=0){
				bHavePass=true;
				break;
			}
		}
		if(bHavePass){
			continue;
		}
		int copylen=retlen;
		if(copylen>MAX_PACK_SAVE_LEN)
			copylen=MAX_PACK_SAVE_LEN;
		SaveBufLen[g_iSSTotalNum]=retlen;
		memcpy((char *)SaveBuf[g_iSSTotalNum],(char *)RecvBuf,copylen);
		CTime time=CTime::GetCurrentTime();
		ptr->m_ctlListReceive.InsertItem(g_iSSTotalNum,time.Format("%H:%M:%S"));
		ptr->m_ctlListReceive.SetItemText(g_iSSTotalNum,LIST_RECEIVE_SOURCEIP,IPIntToStr(pIPHead->sourceIP));
		ptr->m_ctlListReceive.SetItemText(g_iSSTotalNum,LIST_RECEIVE_DESTIP,IPIntToStr(pIPHead->desrIP));

		CString strSourcePort,strDestPort,strMsg="";
		int iDataLen=0,i;
		switch(pIPHead->proto){
		case 1:
			strSourcePort="/";
			strDestPort="/";
			ptr->m_ctlListReceive.SetItemText(g_iSSTotalNum,LIST_RECEIVE_PROTOCOL,"ICMP");
			iDataLen=retlen-(iIPLen+iIcmpLen);
			for(i=0;i<iDataLen;i++){
				strTemp.Format("%02x ",(UCHAR)(pIcmpHead+i));
				strMsg+=strTemp;
			}
			break;
		case 6:
			strSourcePort.Format("%d",ntohs(pTcpHead->th_sport));
			strDestPort.Format("%d",ntohs(pTcpHead->th_dport));
			ptr->m_ctlListReceive.SetItemText(g_iSSTotalNum,LIST_RECEIVE_PROTOCOL,"TCP");
			iDataLen=retlen-(iIPLen+iTcpLen);
			for(i=0;i<iDataLen;i++){
				strTemp.Format("%02x ",(UCHAR)(pTcpHead+i));
				strMsg+=strTemp;
			}
			break;
		case 17:
			strSourcePort.Format("%d",ntohs(pUdpHead->uh_sport));
			strDestPort.Format("%d",ntohs(pUdpHead->uh_dport));
			ptr->m_ctlListReceive.SetItemText(g_iSSTotalNum,LIST_RECEIVE_PROTOCOL,"UDP");
			iDataLen = retlen-(iIPLen+iUdpLen);
			for(i=0;i<iDataLen;i++){
				strTemp.Format("%02x ",(UCHAR)(pUdpHead+i));
				strMsg+=strTemp;
			}
			break;
		default:
			ptr->m_ctlListReceive.SetItemText(g_iSSTotalNum,LIST_RECEIVE_PROTOCOL,"ETC");
			break;
		}
		strTemp.Format("%d",retlen);
		ptr->m_ctlListReceive.SetItemText(g_iSSTotalNum,LIST_RECEIVE_LEN,strTemp);
		ptr->m_ctlListReceive.SetItemText(g_iSSTotalNum,LIST_RECEIVE_SOURCEPORT,strSourcePort);
		ptr->m_ctlListReceive.SetItemText(g_iSSTotalNum,LIST_RECEIVE_DESTPORT,strDestPort);
		ptr->m_ctlListReceive.SetItemText(g_iSSTotalNum,LIST_RECEIVE_CONTENT,strMsg);
		g_iSSTotalNum++;
	}
	shutdown(sock,2);
	closesocket(sock);
	threadParam->g_bSSRunning=false;
	return 0;

}
	
void CSnifferScan::OnBUTTONStop() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	for(int i=0;i<g_iSSThreadCount;i++){
		SSThreadParam[i].g_bSSRunning=false;
	}
	m_strComment="线程已关闭";
	UpdateData(false);
}

void CSnifferScan::OnClickLISTReceive(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CSnifferScan::OnDblclkLISTReceive(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION posReceive=m_ctlListReceive.GetFirstSelectedItemPosition();
	if(posReceive==NULL){
		*pResult = 0;
		return;
	}
	int index=m_ctlListReceive.GetNextSelectedItem(posReceive);
	UpdateData(true);
	CString strTemp;
	int showlen=SaveBufLen[index];
	if(showlen>MAX_PACK_SAVE_LEN)
		showlen=MAX_PACK_SAVE_LEN;
	int iOffset=0;
	int packlen=sizeof(IPHEADER);
	m_strContent="IP包头:";
	for(int i=0;i<packlen;i++){
		strTemp.Format("%02X",(UCHAR)SaveBuf[index][iOffset+i]);
		m_strContent+=strTemp;
	}
	m_strContent+="\r\n";
	iOffset+=packlen;
	strTemp=m_ctlListReceive.GetItemText(index,LIST_RECEIVE_PROTOCOL);
	if(strTemp=="TCP"){
		packlen=sizeof(TCPHEADER);
		m_strContent+="TCP包头:";
	}else if(strTemp=="UDP"){
		packlen=sizeof(UDPHEADER);
		m_strContent+="UDP包头:";
	}else if(strTemp=="ICMP"){
		packlen=sizeof(ICMPHEADER);
		m_strContent+="ICMP包头:";
	}else if(strTemp=="ETC"){
		packlen=0;
	}

	for(i=0;i<packlen;i++){
		strTemp.Format("%02X",(UCHAR)SaveBuf[index][iOffset+i]);
		m_strContent+=strTemp;
	}
	m_strContent+="\r\n";
	iOffset+=packlen;
	m_strContent+="内容:\r\n";
	for(i=0;i<showlen-iOffset;i++){
		strTemp.Format("%c",(UCHAR)SaveBuf[index][iOffset+i]);
		m_strContent+=strTemp;
	}
	UpdateData(false);

	*pResult = 0;
}

void CSnifferScan::OnBUTTONClear() 
{
	// TODO: Add your control notification handler code here
	m_ctlListReceive.DeleteAllItems();
	m_strContent="";
	g_iSSTotalNum=0;
	UpdateData(false);
}

void CSnifferScan::OnBUTTONAddKW() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if(m_strKeyword==""){
		MessageBox("关键字不要为空");
		return;
	}
	m_ctlListKeyword.AddString(m_strKeyword);
	m_strKeyword="";
	UpdateData(false);
}

void CSnifferScan::OnBUTTONDeleteKW() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	int sel = m_ctlListKeyword.GetCurSel();
	if(sel!=LB_ERR){
		m_ctlListKeyword.DeleteString(sel);
	}
	UpdateData(false);
}
