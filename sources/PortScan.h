#if !defined(AFX_PORTSCAN_H__FE155BE3_D1B2_4A89_A8E1_D0D661C4ED0F__INCLUDED_)
#define AFX_PORTSCAN_H__FE155BE3_D1B2_4A89_A8E1_D0D661C4ED0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PortScan.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPortScan dialog

class CPortScan : public CDialog
{
// Construction
public:
	CString GetPortName(UINT uPort);
	CPortScan(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPortScan)
	enum { IDD = IDD_DIALOGPORTSCAN };
	CTreeCtrl	m_ctlTreeResult;
	CIPAddressCtrl	m_ctlEndIP;
	CIPAddressCtrl	m_ctlBeginIP;
	UINT	m_uBeginPort;
	UINT	m_uEndPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPortScan)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPortScan)
	virtual BOOL OnInitDialog();
	afx_msg void OnBUTTONStart();
	afx_msg void OnBUTTONStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PORTSCAN_H__FE155BE3_D1B2_4A89_A8E1_D0D661C4ED0F__INCLUDED_)
