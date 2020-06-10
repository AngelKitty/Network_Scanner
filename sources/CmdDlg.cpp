// CmdDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Scanner.h"
#include "CmdDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CCmdDlg *cmdDlg;
/////////////////////////////////////////////////////////////////////////////
// CCmdDlg dialog


CCmdDlg::CCmdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCmdDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCmdDlg)
	m_strCommand = _T("");
	m_strResult = _T("");
	//}}AFX_DATA_INIT
}

CCmdDlg::~CCmdDlg(){
	if(cmdDlg!=NULL){
		delete cmdDlg;
	}
}

void CCmdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCmdDlg)
	DDX_Text(pDX, IDC_EDITCommand, m_strCommand);
	DDX_Text(pDX, IDC_EDITResult, m_strResult);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCmdDlg, CDialog)
	//{{AFX_MSG_MAP(CCmdDlg)
	ON_BN_CLICKED(IDC_BUTTONExecute, OnBUTTONExecute)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCmdDlg message handlers

void CCmdDlg::OnBUTTONExecute() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);

	SECURITY_ATTRIBUTES sa;
	ZeroMemory(&sa,sizeof(sa));
	sa.nLength=sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor=NULL;
	sa.bInheritHandle=true;
	HANDLE hRead,hWrite;
	if(!CreatePipe(&hRead,&hWrite,&sa,0)){
		MessageBox("管道创建出错");
		return;
	}

	STARTUPINFO si;
	ZeroMemory(&si,sizeof(si));
	si.cb=sizeof(STARTUPINFO);
	GetStartupInfo(&si);
	si.hStdError=hWrite;
	si.hStdOutput=hWrite;
	si.wShowWindow=SW_HIDE;
	si.dwFlags=STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

	PROCESS_INFORMATION pi;
	CString strCommand;
	strCommand.Format("cmd.exe /c %s",m_strCommand);
	BOOL res=CreateProcess(NULL,strCommand.GetBuffer(0),NULL,NULL,TRUE,NULL,NULL,NULL,&si,&pi);
	if(!res){
		MessageBox("线程创建出错");
		return;
	}
	CloseHandle(hWrite);

	CString strTemp;
	char cBuff[4096]={0};
	DWORD dwRead=0;
	m_strResult="";
	while(true){
		if(!ReadFile(hRead,cBuff,4095,&dwRead,NULL))
			break;
		cBuff[dwRead]='\0';
		strTemp.Format("%s",cBuff);
		m_strResult+=strTemp;
	}
	UpdateData(false);
}
