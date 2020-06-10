#if !defined(AFX_CMDDLG_H__513D6AEC_4C33_4CE1_8BC0_AA3119F5DCE3__INCLUDED_)
#define AFX_CMDDLG_H__513D6AEC_4C33_4CE1_8BC0_AA3119F5DCE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CmdDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCmdDlg dialog

class CCmdDlg : public CDialog
{
// Construction
public:
	CCmdDlg(CWnd* pParent = NULL);   // standard constructor
	~CCmdDlg();
// Dialog Data
	//{{AFX_DATA(CCmdDlg)
	enum { IDD = IDD_DIALOGCMD };
	CString	m_strCommand;
	CString	m_strResult;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCmdDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCmdDlg)
	afx_msg void OnBUTTONExecute();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMDDLG_H__513D6AEC_4C33_4CE1_8BC0_AA3119F5DCE3__INCLUDED_)
