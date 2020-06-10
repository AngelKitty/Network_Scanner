#if !defined(AFX_DOSSCAN_H__A971E49A_AEE7_446B_B5D5_AF415EED0359__INCLUDED_)
#define AFX_DOSSCAN_H__A971E49A_AEE7_446B_B5D5_AF415EED0359__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DosScan.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDosScan dialog

class CDosScan : public CDialog
{
// Construction
public:
	CDosScan(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDosScan)
	enum { IDD = IDD_DIALOGDOSSCAN };
	CIPAddressCtrl	m_ctlTargetIP;
	UINT	m_uTargetPort;
	UINT	m_uThreadCount;
	CString	m_strComment;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDosScan)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDosScan)
	virtual BOOL OnInitDialog();
	afx_msg void OnBUTTONStart();
	afx_msg void OnBUTTONStop();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOSSCAN_H__A971E49A_AEE7_446B_B5D5_AF415EED0359__INCLUDED_)
