// SSSelectIP.cpp : implementation file
//

#include "stdafx.h"
#include "Scanner.h"
#include "SSSelectIP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSSSelectIP dialog


CSSSelectIP::CSSSelectIP(CWnd* pParent /*=NULL*/)
	: CDialog(CSSSelectIP::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSSSelectIP)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSSSelectIP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSSSelectIP)
	DDX_Control(pDX, IDC_LISTIP, m_ctlListIP);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSSSelectIP, CDialog)
	//{{AFX_MSG_MAP(CSSSelectIP)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSSSelectIP message handlers

BOOL CSSSelectIP::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	for (int i=0;i<iTotalIP;i++)
	{
		m_ctlListIP.AddString(strIP[i]);
	}
	iCurSel=0;
	m_ctlListIP.SetCurSel(iCurSel);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSSSelectIP::OnOK() 
{
	// TODO: Add extra validation here
	iCurSel=m_ctlListIP.GetCurSel();
	if (iCurSel==LB_ERR)
	{
		MessageBox("没有选择要监听的IP地址。");
		return;
	}
	//CDialog::OnOK();
	CDialog::OnOK();
}
