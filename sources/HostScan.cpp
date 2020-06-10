// HostScan.cpp : implementation file
//

#include "stdafx.h"
#include "Scanner.h"
#include "HostScan.h"
#include <ws2tcpip.h>
#include "CmdDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	ICMP_ECHO		8;
#define	ICMP_ECHOREPLY	0;
#define	IPHEADLEN		sizeof(IPHEADER)
#define ICMPHEADLEN		sizeof(ICMPHEADER)
#define	ICMPHEADMINLEN	8
#define	IPICMPHEADLEN	(IPHEADLEN+ICMPHEADLEN)

#define	SIO_RCVALL		_WSAIOW(IOC_VENDOR,1)
#define	STATUS_FALLED	0xFFFF
 
typedef	struct HSThreadParamStruct{
	UCHAR		a,b,c,d;
	int			index;
	CHostScan	*ptr;
}HSTHREADPARAM;

HSTHREADPARAM	ThreadParam;
UINT	ThreadRawReceive(LPVOID pParam);
UINT	ThreadHostScanStart(LPVOID pParam);
BOOL	g_bRunning;
BOOL	g_bReceiving;
int		g_iItemCount;
CHostScan *pDlgHostScan;
BOOL	bHostScan;

CCmdDlg *cmdDlg;
/////////////////////////////////////////////////////////////////////////////
// CHostScan dialog


CHostScan::CHostScan(CWnd* pParent /*=NULL*/)
	: CDialog(CHostScan::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHostScan)
	//m_strStartIP = _T("");
	//}}AFX_DATA_INIT
}


void CHostScan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHostScan)
	DDX_Control(pDX, IDC_LISTResult, m_ctlListResult);
	DDX_Control(pDX, IDC_IPADDRESSEnd, m_ctlEndIP);
	DDX_Control(pDX, IDC_IPADDRESSBegin, m_ctlBeginIP);
	//DDX_Text(pDX, IDC_EDITEndIP, m_strStartIP);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHostScan, CDialog)
	//{{AFX_MSG_MAP(CHostScan)
	ON_BN_CLICKED(IDC_BUTTONStartScan, OnBUTTONStartScan)
	ON_BN_CLICKED(IDC_BUTTONStopScan, OnBUTTONStopScan)
	ON_BN_CLICKED(IDC_BUTTONCmd, OnBUTTONCmd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHostScan message handlers

BOOL CHostScan::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	bHostScan=false;
	WSADATA	wsaData;
	if(WSAStartup(MAKEWORD(2,1),&wsaData)!=0)
	{
		CString	strTemp;
		strTemp.Format("初始化失败，请重新运行。错误码：%d",GetLastError());
		MessageBox(strTemp,"出错提示");
		ExitProcess(0);
	}
	char	sLocalName[64]={0};
	gethostname((char *)sLocalName,sizeof(sLocalName)-1);
	hostent	*pHost = gethostbyname(sLocalName);
	m_strLocalIP.Format("%s",inet_ntoa(*(struct in_addr *)pHost->h_addr_list[0]));

	m_ctlListResult.InsertColumn(LIST_RESULT_INDEX,"序号",LVCFMT_LEFT,50);
	m_ctlListResult.InsertColumn(LIST_RESULT_IP,"IP",LVCFMT_LEFT,150);
	m_ctlListResult.InsertColumn(LIST_RESULT_STATE,"状态",LVCFMT_LEFT,50);
	m_ctlListResult.InsertColumn(LIST_RESULT_OS,"操作系统",LVCFMT_LEFT,100);
	m_ctlListResult.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	char	buff[MAX_PATH];
	GetPrivateProfileString("Init","BeginIP","192.168.0.101",buff,MAX_PATH,INIFILENAME);
	m_ctlBeginIP.SetWindowText(buff);
	GetPrivateProfileString("Init","EndIP","192.168.0.103",buff,MAX_PATH,INIFILENAME);
	m_ctlEndIP.SetWindowText(buff);
	ThreadParam.ptr = this;
	g_bRunning=TRUE;
	g_bReceiving=FALSE;
	AfxBeginThread(ThreadRawReceive,&ThreadParam,THREAD_PRIORITY_IDLE);
	Sleep(500);

	UpdateData(FALSE);
	pDlgHostScan=this;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

 UINT ThreadRawReceive(LPVOID pParam)
 {
	 //AfxMessageBox("hh",MB_OK);
 	HSTHREADPARAM *threadparam = (HSTHREADPARAM *)pParam;
	CHostScan *ptr = threadparam->ptr;
	CListCtrl *pList = (CListCtrl *)&ptr->m_ctlListResult;

	SOCKET sock;
	SOCKADDR_IN addr_local,addr_remote;
	int buflen = sizeof(addr_remote);
	if((sock=WSASocket(AF_INET,SOCK_RAW,IPPROTO_IP,NULL,0,WSA_FLAG_OVERLAPPED))==INVALID_SOCKET)
	{
		AfxMessageBox("原始套接字设出错！\n",MB_OK | MB_ICONINFORMATION);
		return 1;
	}
	BOOL flag = true;
	if(setsockopt(sock,IPPROTO_IP,IP_HDRINCL,(char *)&flag,sizeof(flag)) == SOCKET_ERROR)
	{
		AfxMessageBox("套接字选项IP_HDRINCL设置出错！\n",MB_OK | MB_ICONINFORMATION);
		return 2;
	}
	int nTimeOver = 500;
	if(setsockopt(sock,SOL_SOCKET,SO_RCVTIMEO,(char *)&nTimeOver,sizeof(nTimeOver))== SOCKET_ERROR)
	{
		AfxMessageBox("超时时间设置出错！\n",MB_OK | MB_ICONINFORMATION);
		return 3;
	}
	int localPort = GetPrivateProfileInt("Init","LocalPort",5000,INIFILENAME);
	addr_local.sin_family = AF_INET;
	addr_local.sin_port = htons(localPort);
	addr_local.sin_addr.S_un.S_addr = inet_addr(ptr->m_strLocalIP);
	if(bind(sock,(PSOCKADDR)&addr_local,sizeof(addr_local))==SOCKET_ERROR)
	{
		AfxMessageBox("绑定口出错！\n",MB_OK | MB_ICONINFORMATION);
		return 4;
	}
	DWORD dwBufferLen[10];
	DWORD dwBufferInLen = 1;
	DWORD dwByteReturned = 0;

	if(WSAIoctl(sock,SIO_RCVALL,&dwBufferInLen,sizeof(dwBufferInLen),
		&dwBufferLen,sizeof(dwBufferLen),&dwByteReturned,NULL,NULL)==SOCKET_ERROR)
	{
		AfxMessageBox("混杂模式设置出错！\n",MB_OK|MB_ICONINFORMATION);
		return 5;
	}
	
	UCHAR RecvBuf[65000];
	PIPHEADER ipPtr = (PIPHEADER)RecvBuf;
	CString strTemp;
	while(g_bRunning){
		int ret = recvfrom(sock,(char *)RecvBuf,sizeof(RecvBuf),0,
			(LPSOCKADDR)&addr_remote,&buflen);
		if(ret == SOCKET_ERROR)
			continue;
		
		if(!g_bReceiving)
		{
			Sleep(10);
			continue;
		}
		
		UNIONIP ip;
		ip.uInt = ipPtr->sourceIP;
		for(int i=0;i<g_iItemCount;i++){
			//AfxMessageBox("通",MB_OK);
			if(pList->GetItemData(i)!=(DWORD)ip.uInt)
				continue;
		
			//AfxMessageBox("通",MB_OK);
			pList->SetItemText(i,LIST_RESULT_STATE,"通");
			UCHAR ucTTL=ipPtr->ttl;
			CString strTemp="无法判断";
			if(ucTTL<=32){
				strTemp="Windows 95/98/Me";
			}
			else if(ucTTL<=64){
				strTemp = "Linux";
			}
			else if(ucTTL<=128){
				strTemp = "Windows NT";
			}
			else{
				strTemp = "UNIX";
			}
			//AfxMessageBox("hh",MB_OK);
			pList->SetItemText(i,LIST_RESULT_OS,strTemp);
			break;
		}
	}
	shutdown(sock,2);
	closesocket(sock);
	return 0;
 }

void CHostScan::OnBUTTONStartScan() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	AfxBeginThread(ThreadHostScanStart,&ThreadParam,THREAD_PRIORITY_IDLE);
	//AfxBeginThread(ThreadRawReceive,&ThreadParam,THREAD_PRIORITY_IDLE);
}

UINT ThreadHostScanStart(LPVOID pParam){
	HSTHREADPARAM *threadparam = (HSTHREADPARAM *)pParam;
	CHostScan *ptr = threadparam->ptr;
	CListCtrl *pList = (CListCtrl *)&ptr->m_ctlListResult;

	//ptr->UpdateData(true);
	ptr->GetDlgItem(IDC_BUTTONStartScan)->EnableWindow(FALSE);
	//AfxBeginThread(ThreadRawReceive,&ThreadParam,THREAD_PRIORITY_IDLE);
	//Sleep(500);
	SOCKET sockSend=WSASocket(AF_INET,SOCK_RAW,IPPROTO_ICMP,NULL,0,WSA_FLAG_OVERLAPPED);
	if(sockSend==INVALID_SOCKET){
		AfxMessageBox("RAW SOCKET 创建失败");
		return 1;
	}

	CString strIP,strTemp;
	int iCount = 0;
	UNIONIP uBeginIP,uEndIP;
	ptr->m_ctlBeginIP.GetAddress(uBeginIP.dwDword);
	ptr->m_ctlEndIP.GetAddress(uEndIP.dwDword);
	while(uBeginIP.dwDword<=uEndIP.dwDword && iCount<1000){
		strTemp.Format("%d",iCount+1);
		ptr->m_ctlListResult.InsertItem(iCount,strTemp);
		strIP.Format("%d.%d.%d.%d",uBeginIP.ucByte[3],uBeginIP.ucByte[2],uBeginIP.ucByte[1],uBeginIP.ucByte[0]);
		ptr->m_ctlListResult.SetItemText(iCount,LIST_RESULT_IP,strIP);
		ptr->m_ctlListResult.SetItemText(iCount,LIST_RESULT_STATE,"");
		ptr->m_ctlListResult.SetItemData(iCount,IPStrToInt(strIP));
		uBeginIP.dwDword++;
		iCount++;
	}
	g_iItemCount = iCount;

	int timeout = 1000;
	setsockopt(sockSend,SOL_SOCKET,SO_RCVTIMEO,(char *)&timeout,sizeof(timeout));
	setsockopt(sockSend,SOL_SOCKET,SO_SNDTIMEO,(char *)&timeout,sizeof(timeout));

	sockaddr_in addr_inr,addr_in1;
	addr_in1.sin_family = AF_INET;
	addr_in1.sin_port = htons(54321);
	addr_in1.sin_addr.S_un.S_addr = inet_addr(ptr->m_strLocalIP);

	addr_inr.sin_family = AF_INET;
	addr_inr.sin_port = htons(12345);
	int flag = 1;
	setsockopt(sockSend,IPPROTO_IP,IP_HDRINCL,(char *)&flag,sizeof(flag));
	if(bind(sockSend,(PSOCKADDR)&addr_in1,sizeof(addr_in1))==SOCKET_ERROR)
		return 2;

	//CString strTemp;
	g_bReceiving = TRUE;
	char sendBuf[1024]={0};
	PIPHEADER ipHeader = (PIPHEADER)sendBuf;
	PICMPHEADER icmpHeader = (PICMPHEADER)&sendBuf[IPHEADLEN];
	char *dataHeader = (char *)icmpHeader->buff;
	CString strData = "abcdefghijklmnopqrstuvwabcdefghi";
	strcpy(dataHeader,strData);

	ipHeader->ver_pack = 0x45;
	ipHeader->tos = 0;
	ipHeader->total_len = htons(IPICMPHEADLEN);
	ipHeader->ident = 0;
	ipHeader->ttl = 128;
	ipHeader->proto = IPPROTO_ICMP;
	ipHeader->sourceIP = addr_in1.sin_addr.S_un.S_addr;
	icmpHeader->i_type = ICMP_ECHO;
	icmpHeader->i_code = 0;
	icmpHeader->i_id = 0x0;
	icmpHeader->i_seq = 0x0;
	icmpHeader->i_cksum = 0;
	icmpHeader->i_cksum = ptr->Checksum((USHORT *)icmpHeader,60-IPHEADLEN);
	//int ICount = m_ctlListResult.GetItemCount();
	for(int times=0;times<1;times++){
		for(int i=0;i<iCount;i++){
			if(!g_bReceiving)
				break;

			strTemp = ptr->m_ctlListResult.GetItemText(i,LIST_RESULT_IP);
			addr_inr.sin_addr.S_un.S_addr=inet_addr(strTemp);
			ipHeader->checksum = ptr->Checksum((USHORT *)sendBuf,IPHEADLEN);

			CString ss,tt="";
			for(int s=0;s<200;s++){
				ss.Format("%02X",(UCHAR)sendBuf[s]);
				tt+=ss;
				if(s%10==9)
					tt+="\r\n";
			}
			sendto(sockSend,(char *)sendBuf,ICMPHEADLEN,0,(struct sockaddr *)&addr_inr,
				sizeof(addr_inr));
			//MessageBox(strTemp);
			Sleep(100);
			//DoEvent(strTemp);
		}
	}
	ptr->GetDlgItem(IDC_BUTTONStartScan)->EnableWindow(TRUE);
	return 0;
}

USHORT CHostScan::Checksum(USHORT *buffer, int size)
{
	unsigned long cksum = 0;
	while(size>1){
		cksum+=*buffer++;
		size -= sizeof(USHORT);
	}
	if(size){
		cksum += *(UCHAR *)buffer;
	}

	cksum = (cksum >> 16) + (cksum & 0xffff);
	cksum += (cksum >>16);
	return (USHORT)(~cksum);
}

//DEL void CHostScan::DoEvent(CString tempPass)
//DEL {
//DEL 	MSG msg;
//DEL 	CWnd *pEdit = this->GetDlgItem(IDC_);
//DEL }

//DEL UINT CHostScan::IPStrToInt(CString IPStr)
//DEL {
//DEL 	UNIONIP IP;
//DEL 	
//DEL 	int i,j=0;
//DEL 	IPStr.TrimLeft(" ");
//DEL 	IPStr.TrimRight(" ");
//DEL 	for (i=0;i<IPStr.GetLength();i++)
//DEL 	{
//DEL 		if (IPStr.GetAt(i) <'0' || IPStr.GetAt(i)>'9')
//DEL 			if (IPStr.GetAt(i) == '.')
//DEL 				j++;
//DEL 			else
//DEL 				return 0;		
//DEL 	}
//DEL 	if (j!=3)
//DEL 		return 0;
//DEL 	i=0;
//DEL 	IPStr+=".";
//DEL 	CString temp;
//DEL 	for (int m=0;m<4;m++)
//DEL 	{		
//DEL 		temp="";
//DEL 		while (IPStr.GetAt(i) != '.')
//DEL 		{
//DEL 			temp+=IPStr.GetAt(i);
//DEL 			i++;
//DEL 		}
//DEL 		i++;
//DEL 		if (temp=="" || atoi(temp) > 0xFF)
//DEL 			return 0;
//DEL 		else
//DEL 			IP.ucByte[m]=atoi(temp);
//DEL 	}
//DEL 	return IP.uInt;
//DEL }

void CHostScan::OnBUTTONStopScan() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BUTTONStartScan)->EnableWindow(true);
	g_bReceiving=false;
}

void CHostScan::OnBUTTONCmd() 
{
	// TODO: Add your control notification handler code here
	cmdDlg =new CCmdDlg();
	cmdDlg->Create(IDD_DIALOGCMD,this);
	cmdDlg->ShowWindow(true);
}
