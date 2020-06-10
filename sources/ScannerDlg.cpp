// ScannerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Scanner.h"
#include "ScannerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CScannerDlg *pDlg;
extern BOOL g_bRunning;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScannerDlg dialog

CScannerDlg::CScannerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScannerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScannerDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CScannerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScannerDlg)
	DDX_Control(pDX, IDC_TABMAIN, m_TabMain);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CScannerDlg, CDialog)
	//{{AFX_MSG_MAP(CScannerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABMAIN, OnSelchangeTabmain)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScannerDlg message handlers

BOOL CScannerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_TabMain.InsertItem(0,"Ö÷»úÉ¨Ãè");
	m_TabMain.InsertItem(1,"¶Ë¿ÚÉ¨Ãè");
	m_TabMain.InsertItem(2,"NetBIOSÉ¨Ãè");
	m_TabMain.InsertItem(3,"SNMPÉ¨Ãè");
	m_TabMain.InsertItem(4,"ÈõÃÜÂëÉ¨Ãè");
	m_TabMain.InsertItem(5,"ÐáÌ½Æ÷");
	m_TabMain.InsertItem(6,"DOS¹¥»÷");
	m_TabMain.InsertItem(7,"×¢Èë¼ì²â");
	m_TabMain.InsertItem(8,"±¨¸æ");

	m_HostScanTab.Create(IDD_DIALOGHOSTSCAN,&m_TabMain);
	m_PortScanTab.Create(IDD_DIALOGPORTSCAN,&m_TabMain);
	m_WeakKeyScanTab.Create(IDD_DIALOGWEAKKEYSCAN,&m_TabMain);
	m_DosScanTab.Create(IDD_DIALOGDOSSCAN,&m_TabMain);
	m_SnifferScanTab.Create(IDD_DIALOGSNIFFERSCAN,&m_TabMain);
	m_SQLScanTab.Create(IDD_DIALOGSQLSCAN,&m_TabMain);
	m_NetBIOSScanTab.Create(IDD_DIALOGNETBIOSSCAN,&m_TabMain);
	m_SNMPScanTap.Create(IDD_DIALOGSNMPSCAN,&m_TabMain);
	m_AllScanTab.Create(IDD_DIALOGALLSCAN,&m_TabMain);

	CRect rs;
	m_TabMain.GetClientRect(&rs);
	rs.top+=20;
	//CString strRs;
	//strRs.Format("%d.%d.%d.%d",rs.Width,rs.Height,rs.top,rs.bottom);
	//MessageBox(strRs);
	m_HostScanTab.MoveWindow(&rs);
	m_PortScanTab.MoveWindow(&rs);
	m_WeakKeyScanTab.MoveWindow(&rs);
	m_DosScanTab.MoveWindow(&rs);
	m_SnifferScanTab.MoveWindow(&rs);
	m_SQLScanTab.MoveWindow(&rs);
	m_NetBIOSScanTab.MoveWindow(&rs);
	m_SNMPScanTap.MoveWindow(&rs);
	m_AllScanTab.MoveWindow(&rs);

	m_HostScanTab.ShowWindow(true);
	m_PortScanTab.ShowWindow(false);
	m_WeakKeyScanTab.ShowWindow(false);
	m_DosScanTab.ShowWindow(false);
	m_SnifferScanTab.ShowWindow(false);
	m_SQLScanTab.ShowWindow(false);
	m_NetBIOSScanTab.ShowWindow(false);
	m_SNMPScanTap.ShowWindow(false);
	m_AllScanTab.ShowWindow(false);
	m_TabMain.SetCurSel(0);

	pDlg=this;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CScannerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CScannerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CScannerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//DEL void CScannerDlg::OnSelchangingTabmain(NMHDR* pNMHDR, LRESULT* pResult) 
//DEL {
//DEL 	// TODO: Add your control notification handler code here
//DEL 	int curSel = m_TabMain.GetCurSel();
//DEL 	switch(curSel){
//DEL 	case 0:
//DEL 		m_HostScanTab.ShowWindow(true);
//DEL 		m_PortScanTab.ShowWindow(false);
//DEL 		break;
//DEL 	case 1:
//DEL 		m_HostScanTab.ShowWindow(false);
//DEL 		m_PortScanTab.ShowWindow(true);
//DEL 		break;
//DEL 	}
//DEL 
//DEL 	*pResult = 0;
//DEL }

void CScannerDlg::OnSelchangeTabmain(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int curSel = m_TabMain.GetCurSel();
	switch(curSel){
	case 0:
		m_HostScanTab.ShowWindow(true);
		m_PortScanTab.ShowWindow(false);
		m_WeakKeyScanTab.ShowWindow(false);
		m_DosScanTab.ShowWindow(false);
		m_SnifferScanTab.ShowWindow(false);
		m_SQLScanTab.ShowWindow(false);
		m_NetBIOSScanTab.ShowWindow(false);
		m_SNMPScanTap.ShowWindow(false);
		m_AllScanTab.ShowWindow(false);
		break;
	case 1:
		m_HostScanTab.ShowWindow(false);
		m_PortScanTab.ShowWindow(true);
		m_WeakKeyScanTab.ShowWindow(false);
		m_DosScanTab.ShowWindow(false);
		m_SnifferScanTab.ShowWindow(false);
		m_SQLScanTab.ShowWindow(false);
		m_NetBIOSScanTab.ShowWindow(false);
		m_SNMPScanTap.ShowWindow(false);
		m_AllScanTab.ShowWindow(false);
		break;
	case 2:
		m_HostScanTab.ShowWindow(false);
		m_PortScanTab.ShowWindow(false);
		m_WeakKeyScanTab.ShowWindow(false);
		m_DosScanTab.ShowWindow(false);
		m_SnifferScanTab.ShowWindow(false);
		m_SQLScanTab.ShowWindow(false);
		m_NetBIOSScanTab.ShowWindow(true);
		m_SNMPScanTap.ShowWindow(false);
		m_AllScanTab.ShowWindow(false);
		break;
	case 3:
		m_HostScanTab.ShowWindow(false);
		m_PortScanTab.ShowWindow(false);
		m_WeakKeyScanTab.ShowWindow(false);
		m_DosScanTab.ShowWindow(false);
		m_SnifferScanTab.ShowWindow(false);
		m_SQLScanTab.ShowWindow(false);
		m_NetBIOSScanTab.ShowWindow(false);
		m_SNMPScanTap.ShowWindow(true);
		m_AllScanTab.ShowWindow(false);
		break;
	case 4:
		m_HostScanTab.ShowWindow(false);
		m_PortScanTab.ShowWindow(false);
		m_WeakKeyScanTab.ShowWindow(true);
		m_DosScanTab.ShowWindow(false);
		m_SnifferScanTab.ShowWindow(false);
		m_SQLScanTab.ShowWindow(false);
		m_NetBIOSScanTab.ShowWindow(false);
		m_SNMPScanTap.ShowWindow(false);
		m_AllScanTab.ShowWindow(false);
		break;
	case 5:
		m_HostScanTab.ShowWindow(false);
		m_PortScanTab.ShowWindow(false);
		m_WeakKeyScanTab.ShowWindow(false);
		m_DosScanTab.ShowWindow(false);
		m_SnifferScanTab.ShowWindow(true);
		m_SQLScanTab.ShowWindow(false);
		m_NetBIOSScanTab.ShowWindow(false);
		m_SNMPScanTap.ShowWindow(false);
		m_AllScanTab.ShowWindow(false);
		break;
	case 6:
		m_HostScanTab.ShowWindow(false);
		m_PortScanTab.ShowWindow(false);
		m_WeakKeyScanTab.ShowWindow(false);
		m_DosScanTab.ShowWindow(true);
		m_SnifferScanTab.ShowWindow(false);
		m_SQLScanTab.ShowWindow(false);
		m_NetBIOSScanTab.ShowWindow(false);
		m_SNMPScanTap.ShowWindow(false);
		m_AllScanTab.ShowWindow(false);
		break;
	case 7:
		m_HostScanTab.ShowWindow(false);
		m_PortScanTab.ShowWindow(false);
		m_WeakKeyScanTab.ShowWindow(false);
		m_DosScanTab.ShowWindow(false);
		m_SnifferScanTab.ShowWindow(false);
		m_SQLScanTab.ShowWindow(true);
		m_NetBIOSScanTab.ShowWindow(false);
		m_SNMPScanTap.ShowWindow(false);
		m_AllScanTab.ShowWindow(false);
		break;
	case 8:
		m_HostScanTab.ShowWindow(false);
		m_PortScanTab.ShowWindow(false);
		m_WeakKeyScanTab.ShowWindow(false);
		m_DosScanTab.ShowWindow(false);
		m_SnifferScanTab.ShowWindow(false);
		m_SQLScanTab.ShowWindow(false);
		m_NetBIOSScanTab.ShowWindow(false);
		m_SNMPScanTap.ShowWindow(false);
		m_AllScanTab.ShowWindow(true);
		//m_HostScanTab.ShowWindow(true);
		break;
	default:break;
	}

	*pResult = 0;
}


//DEL void CScannerDlg::OnBUTTONTest() 
//DEL {
//DEL 	// TODO: Add your control notification handler code here
//DEL 	this->PostMessage(WM_COMMAND,MAKEWPARAM(IDC_BUTTON2,BN_CLICKED),NULL);
//DEL 	m_TabMain.SetCurSel(5);
//DEL 	NMHDR nmhdr;
//DEL 	nmhdr.code=TCN_SELCHANGE;
//DEL 	nmhdr.hwndFrom=m_TabMain.GetSafeHwnd();
//DEL 	nmhdr.idFrom=IDC_TABMAIN;
//DEL 	//this->PostMessage(WM_COMMAND,MAKEWPARAM(IDC_TABMAIN,TCN_SELCHANGE),NULL);
//DEL 	::SendMessage(m_TabMain.GetSafeHwnd(),WM_NOTIFY,MAKELONG(TCN_SELCHANGE,0),(LPARAM)(&nmhdr));
//DEL }

//DEL void CScannerDlg::OnButton2() 
//DEL {
//DEL 	// TODO: Add your control notification handler code here
//DEL 	MessageBox("ok");
//DEL }

//DEL void CScannerDlg::OnCancelMode() 
//DEL {
//DEL 	CDialog::OnCancelMode();
//DEL 	
//DEL 	// TODO: Add your message handler code here
//DEL 	g_bRunning=false;
//DEL 	MessageBox("goodbye");
//DEL }

void CScannerDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default	
	//MessageBox("È·¶¨ÒªÍË³ö³ÌÐòÂð£¿");
	if(MessageBox("È·¶¨ÒªÍË³ö³ÌÐòÂð£¿","",MB_OKCANCEL)==IDOK){
		g_bRunning=false;
		CDialog::OnClose();
	}
}
