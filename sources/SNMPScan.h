#if !defined(AFX_SNMPSCAN_H__19DC7824_C561_4798_B952_01EF4A5AC24F__INCLUDED_)
#define AFX_SNMPSCAN_H__19DC7824_C561_4798_B952_01EF4A5AC24F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SNMPScan.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSNMPScan dialog

class CSNMPScan : public CDialog
{
// Construction
public:
	CString GetValue(CString strIP,CString &strOid,UCHAR ucType);
	CSNMPScan(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSNMPScan)
	enum { IDD = IDD_DIALOGSNMPSCAN };
	CIPAddressCtrl	m_ctlIP;
	CTreeCtrl	m_ctlTreeResult;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSNMPScan)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSNMPScan)
	virtual BOOL OnInitDialog();
	afx_msg void OnBUTTONStart();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SNMPSCAN_H__19DC7824_C561_4798_B952_01EF4A5AC24F__INCLUDED_)
