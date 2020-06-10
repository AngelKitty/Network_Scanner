#if !defined(AFX_ALLSCAN_H__A9D89B2D_AA2C_4126_B461_50D331B02EE0__INCLUDED_)
#define AFX_ALLSCAN_H__A9D89B2D_AA2C_4126_B461_50D331B02EE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AllScan.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CAllScan dialog

class CAllScan : public CDialog
{
// Construction
public:
	CString strReportContent;
	CAllScan(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAllScan)
	enum { IDD = IDD_DIALOGALLSCAN };
	CIPAddressCtrl	m_ctlTargetIP;
	int		m_iRadioReportType;
	BOOL	m_bCheckDDOSScan;
	BOOL	m_bCheckHostScan;
	BOOL	m_bCheckNetBIOSScan;
	BOOL	m_bCheckPortScan;
	BOOL	m_bCheckSnifferScan;
	BOOL	m_bCheckSNMPScan;
	BOOL	m_bCheckWeakKeyScan;
	BOOL	m_bCheckSQLScan;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAllScan)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAllScan)
	afx_msg void OnBUTTONStart();
	virtual BOOL OnInitDialog();
	afx_msg void OnRADIOHtml();
	afx_msg void OnRADIOTxt();
	afx_msg void OnRADIOXml();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALLSCAN_H__A9D89B2D_AA2C_4126_B461_50D331B02EE0__INCLUDED_)
