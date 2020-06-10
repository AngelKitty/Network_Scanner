// PortScan.cpp : implementation file
//

#include "stdafx.h"
#include "Scanner.h"
#include "PortScan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

typedef struct PSThreadParamStruct{
	CString	strIP;
	UINT	uPort;
	BOOL	bNoOrder;
	CPortScan	*ptr;
	HTREEITEM	TreeItem;
}PSTHREADPARAM;

PSTHREADPARAM	PSThreadParam;
UINT	TCPThreadScan(LPVOID pParam);
BOOL	g_bPSRunning;
int		g_iTotalThreadCount;
CPortScan *pDlgPortScan;
/////////////////////////////////////////////////////////////////////////////
// CPortScan dialog


CPortScan::CPortScan(CWnd* pParent /*=NULL*/)
	: CDialog(CPortScan::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPortScan)
	m_uBeginPort = 0;
	m_uEndPort = 0;
	//}}AFX_DATA_INIT
}


void CPortScan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPortScan)
	DDX_Control(pDX, IDC_TREEResult, m_ctlTreeResult);
	DDX_Control(pDX, IDC_IPADDRESSEndIP, m_ctlEndIP);
	DDX_Control(pDX, IDC_IPADDRESSBgeinIP, m_ctlBeginIP);
	DDX_Text(pDX, IDC_EDITBeginPort, m_uBeginPort);
	DDX_Text(pDX, IDC_EDITEndPort, m_uEndPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPortScan, CDialog)
	//{{AFX_MSG_MAP(CPortScan)
	ON_BN_CLICKED(IDC_BUTTONStart, OnBUTTONStart)
	ON_BN_CLICKED(IDC_BUTTONStop, OnBUTTONStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPortScan message handlers

BOOL CPortScan::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if(!AfxSocketInit()){
		MessageBox("Socket初始化失败，请重新运行。");
		return FALSE;
	}

	WSAData wsaData;
	WSAStartup(WINSOCK_VERSION,&wsaData);
	g_iTotalThreadCount = 0;
	srand((unsigned)time(NULL));
	CString	strTemp;
	char	buff[MAX_PATH];
	GetPrivateProfileString("PortScan","BeginIP","192.168.0.101",buff,MAX_PATH,INIFILENAME);
	m_ctlBeginIP.SetWindowText(buff);
	GetPrivateProfileString("PortScan","EndIP","192.168.0.102",buff,MAX_PATH,INIFILENAME);
	m_ctlEndIP.SetWindowText(buff);
	m_uBeginPort=GetPrivateProfileInt("PortScan","BeginPort",1,INIFILENAME);
	m_uEndPort = GetPrivateProfileInt("PortScan","EndPort",1024,INIFILENAME);
	g_iTotalThreadCount = 0;
	UpdateData(false);
	pDlgPortScan=this;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPortScan::OnBUTTONStart() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	UNIONIP unBeginIP,unEndIP;
	m_ctlBeginIP.GetAddress(unBeginIP.dwDword);
	m_ctlEndIP.GetAddress(unEndIP.dwDword);
	if(unBeginIP.dwDword>unEndIP.dwDword){
		AfxMessageBox("开始IP大于结束IP！");
		return;
	}

	if(m_uBeginPort<1 || m_uBeginPort >65535 || m_uEndPort <1 || m_uEndPort > 65535)
	{
		AfxMessageBox("端口值应在1~65535范围");
		return;
	}else if(m_uBeginPort>m_uEndPort){
		if(IDOK==AfxMessageBox("开始端口大于结束端口，为您交换？",MB_OKCANCEL)){
			UINT uTempPort = m_uBeginPort;
			m_uBeginPort = m_uEndPort;
			m_uEndPort = uTempPort;
			UpdateData(FALSE);
		}else{
			return;
		}
	}

	m_ctlTreeResult.DeleteAllItems();
	CString strIP,strTemp;
	g_bPSRunning = TRUE;
	for(;unBeginIP.dwDword<=unEndIP.dwDword;unBeginIP.dwDword++){
		strIP.Format("%d.%d.%d.%d",unBeginIP.ucByte[3],unBeginIP.ucByte[2],unBeginIP.ucByte[1],unBeginIP.ucByte[0]);
		HTREEITEM curr = m_ctlTreeResult.InsertItem(strIP);

		PSThreadParam.strIP = strIP;
		PSThreadParam.ptr = this;
		PSThreadParam.TreeItem = curr;
		for(UINT port=m_uBeginPort;port<m_uEndPort;port++){
			PSThreadParam.uPort = port;
			AfxBeginThread(TCPThreadScan,&PSThreadParam,THREAD_PRIORITY_IDLE);
			Sleep(50);
		}
	}
	UpdateData(FALSE);
	return;
}

UINT TCPThreadScan(LPVOID pParam){
	PSTHREADPARAM *threadParam = (PSTHREADPARAM *)pParam;
	CString strIP = threadParam->strIP;
	UINT uPort = threadParam->uPort;
	CPortScan *ptr = threadParam->ptr;
	HTREEITEM treeItem = threadParam->TreeItem;

	g_iTotalThreadCount++;
	CSocket sock;
	CString strTemp;
	if(sock.Create()){
		if(sock.Connect(strIP,uPort)){
			if(uPort<1024){
				struct servent *se;
				se = getservbyport(htons(uPort),"tcp");
				if(se != NULL){
					strTemp.Format("%d %s",uPort,se->s_name);
				}else{
					strTemp.Format("%d",uPort);
				}
			}else{
				strTemp.Format("%d %s",uPort,ptr->GetPortName(uPort));
			}
			ptr->m_ctlTreeResult.InsertItem(strTemp,treeItem);
			sock.ShutDown(2);
		}
		sock.Close();
	}
	g_iTotalThreadCount--;
	return 0;
}

CString CPortScan::GetPortName(UINT uPort)
{
	CString strRet;
	switch(uPort){
	case 1026:strRet = "常用动态分配的TCP端口";break;
	case 1080:strRet = "WinGate,IRC等防火墙管道";break;
	case 1243:strRet = "Sub-7木马";break;
	case 1433:strRet = "MSSQL数据库服务端口";break;
	case 3128:strRet = "Squid HTTP代理服务器";break;
	case 3306:strRet = "MySql数据库服务端口";break;
	case 5632:strRet = "pcAnywhere所用端口";break;
	default:strRet   = "";break;
	}
	return strRet;
}


//DEL void CPortScan::OnButton1() 
//DEL {
//DEL 	// TODO: Add your control notification handler code here
//DEL 	g_bPSRunning=false;
//DEL }

void CPortScan::OnBUTTONStop() 
{
	// TODO: Add your control notification handler code here
	g_bPSRunning=false;
}
