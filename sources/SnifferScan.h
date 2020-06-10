#if !defined(AFX_SNIFFERSCAN_H__3387FED3_B80D_452E_9194_4E80D493004E__INCLUDED_)
#define AFX_SNIFFERSCAN_H__3387FED3_B80D_452E_9194_4E80D493004E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SnifferScan.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSnifferScan dialog

class CSnifferScan : public CDialog
{
// Construction
public:
	CSnifferScan(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSnifferScan)
	enum { IDD = IDD_DIALOGSNIFFERSCAN };
	CListBox	m_ctlListKeyword;
	CListCtrl	m_ctlListReceive;
	CString	m_strComment;
	CString	m_strKeyword;
	CString	m_strContent;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSnifferScan)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSnifferScan)
	virtual BOOL OnInitDialog();
	afx_msg void OnBUTTONStart();
	afx_msg void OnBUTTONStop();
	afx_msg void OnClickLISTReceive(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkLISTReceive(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBUTTONClear();
	afx_msg void OnBUTTONAddKW();
	afx_msg void OnBUTTONDeleteKW();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SNIFFERSCAN_H__3387FED3_B80D_452E_9194_4E80D493004E__INCLUDED_)
