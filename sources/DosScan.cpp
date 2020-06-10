// DosScan.cpp : implementation file
//

#include "stdafx.h"
#include "Scanner.h"
#include "DosScan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

typedef struct DSThreadParamStruct{
	CString strIP;
	UINT uPort;
	CDosScan *ptr;
}DSTHREADPARAM;
DSTHREADPARAM DSThreadParam;

BOOL g_bDSRunning;
int g_iDSTotalThreadCount;
UINT DSThreadScan(LPVOID pParam);
/////////////////////////////////////////////////////////////////////////////
// CDosScan dialog


CDosScan::CDosScan(CWnd* pParent /*=NULL*/)
	: CDialog(CDosScan::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDosScan)
	m_uTargetPort = 0;
	m_uThreadCount = 0;
	m_strComment = _T("");
	//}}AFX_DATA_INIT
}


void CDosScan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDosScan)
	DDX_Control(pDX, IDC_IPADDRESSTARGETIP, m_ctlTargetIP);
	DDX_Text(pDX, IDC_EDITTARGETPORT, m_uTargetPort);
	DDX_Text(pDX, IDC_EDITTHREADCOUNT, m_uThreadCount);
	DDX_Text(pDX, IDC_EDITComment, m_strComment);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDosScan, CDialog)
	//{{AFX_MSG_MAP(CDosScan)
	ON_BN_CLICKED(IDC_BUTTONStart, OnBUTTONStart)
	ON_BN_CLICKED(IDC_BUTTONStop, OnBUTTONStop)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDosScan message handlers

BOOL CDosScan::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	WSAData wsaData;
	WSAStartup(WINSOCK_VERSION,&wsaData);
	srand((unsigned)time(NULL));

	CString strTemp;
	char buff[MAX_PATH];
	GetPrivateProfileString("DosScan","TargetIP","192.168.0.101",buff,MAX_PATH,INIFILENAME);
	m_ctlTargetIP.SetWindowText(buff);
	m_uTargetPort=GetPrivateProfileInt("DosScan","TargetPort",1024,INIFILENAME);
	g_iDSTotalThreadCount = 0;
	m_uThreadCount = 100;
	UpdateData(false);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDosScan::OnBUTTONStart() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if(m_uTargetPort <1 || m_uTargetPort >65535){
		MessageBox("端口应在1-65535范围");
		return ;
	}
	g_bDSRunning = true;
	SetTimer(1,1000,NULL);

	UCHAR a,b,c,d;
	CString strIP;
	m_ctlTargetIP.GetAddress(a,b,c,d);
	strIP.Format("%d.%d.%d.%d",a,b,c,d);
	DSThreadParam.strIP = strIP;
	DSThreadParam.uPort = m_uTargetPort;
	DSThreadParam.ptr = this;
	for(UINT i=0;i<m_uThreadCount;i++){
		AfxBeginThread(DSThreadScan,&DSThreadParam,THREAD_PRIORITY_IDLE);
		Sleep(10);
	}
	UpdateData(false);
}

UINT DSThreadScan(LPVOID pParam){
	DSTHREADPARAM *threadParam=(DSTHREADPARAM *)pParam;
	g_iDSTotalThreadCount++;
	SOCKET sock=-1;
	sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock == SOCKET_ERROR){
		AfxMessageBox("创建sock出错！");
		return 1;
	}

	CString strIP = threadParam->strIP;
	UINT uPort = threadParam->uPort;
	CDosScan *ptr = threadParam->ptr;
	SOCKADDR_IN addr_remote;
	addr_remote.sin_family = AF_INET;
	addr_remote.sin_addr.S_un.S_addr = inet_addr(strIP);
	addr_remote.sin_port = htons(uPort);

	while(g_bDSRunning){
		connect(sock,(PSOCKADDR)&addr_remote,sizeof(addr_remote));
		Sleep(100);
	}

	shutdown(sock,2);
	closesocket(sock);
	g_iDSTotalThreadCount--;
	return 0;
}

void CDosScan::OnBUTTONStop() 
{
	// TODO: Add your control notification handler code here
	g_bDSRunning = false;
}

void CDosScan::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent){
	case 1:
		if(g_iDSTotalThreadCount>0){
			m_strComment.Format("%d个线程扫描中...",g_iDSTotalThreadCount);
		}else{
			m_strComment.Format("扫描结束");
			KillTimer(1);
		}
		UpdateData(FALSE);
		break;
	default:break;
	}

	CDialog::OnTimer(nIDEvent);
}
