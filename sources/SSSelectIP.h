#if !defined(AFX_SSSELECTIP_H__D4F17F5C_B082_488D_8506_EB785A12D767__INCLUDED_)
#define AFX_SSSELECTIP_H__D4F17F5C_B082_488D_8506_EB785A12D767__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SSSelectIP.h : header file
//

#define MAXIP 20

/////////////////////////////////////////////////////////////////////////////
// CSSSelectIP dialog

class CSSSelectIP : public CDialog
{
// Construction
public:
	int iTotalIP;
	int iCurSel;
	CString strIP[MAXIP];
	CSSSelectIP(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSSSelectIP)
	enum { IDD = IDD_DIALOGSSSelectIP };
	CListBox	m_ctlListIP;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSSSelectIP)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSSSelectIP)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SSSELECTIP_H__D4F17F5C_B082_488D_8506_EB785A12D767__INCLUDED_)
