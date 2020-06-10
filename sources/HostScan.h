#if !defined(AFX_HOSTSCAN_H__A1CDF239_64D6_4ADB_A082_4716DB2FC2DB__INCLUDED_)
#define AFX_HOSTSCAN_H__A1CDF239_64D6_4ADB_A082_4716DB2FC2DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HostScan.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHostScan dialog

class CHostScan : public CDialog
{
// Construction
public:
	USHORT Checksum(USHORT *buffer,int size);
	CString m_strLocalIP;
	CHostScan(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHostScan)
	enum { IDD = IDD_DIALOGHOSTSCAN };
	CListCtrl	m_ctlListResult;
	CIPAddressCtrl	m_ctlEndIP;
	CIPAddressCtrl	m_ctlBeginIP;
	//CString	m_strStartIP;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHostScan)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHostScan)
	virtual BOOL OnInitDialog();
	afx_msg void OnBUTTONStartScan();
	afx_msg void OnBUTTONStopScan();
	afx_msg void OnBUTTONCmd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOSTSCAN_H__A1CDF239_64D6_4ADB_A082_4716DB2FC2DB__INCLUDED_)
