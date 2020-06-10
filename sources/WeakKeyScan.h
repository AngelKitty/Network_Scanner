#if !defined(AFX_WEAKKEYSCAN_H__0DA228BA_8050_4876_B23F_214F60010029__INCLUDED_)
#define AFX_WEAKKEYSCAN_H__0DA228BA_8050_4876_B23F_214F60010029__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WeakKeyScan.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWeakKeyScan dialog

class CWeakKeyScan : public CDialog
{
// Construction
public:
	void BruteForceScan(CString strUsername);
	BOOL ConnectServer(CString strPass,CString strUser);
	CWeakKeyScan(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWeakKeyScan)
	enum { IDD = IDD_DIALOGWEAKKEYSCAN };
	CComboBox	m_ctlUsername;
	CComboBox	m_ctlPwType;
	CComboBox	m_ctlPWLength;
	CIPAddressCtrl	m_ctlIP;
	CString	m_strResult;
	BOOL	m_bCharCapital;
	BOOL	m_bCharLower;
	BOOL	m_bCharNumber;
	BOOL	m_bCharSpecial;
	CString	m_strUsername;
	CString	m_strSelfDefine;
	BOOL	m_bCharSelfDefine;
	CString	m_strPrefix;
	CString	m_strPostfix;
	CString	m_strPassword;
	//}}AFX_DATA
	int l1,l2,l3,l4,l5,l6,l7,l8;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWeakKeyScan)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWeakKeyScan)
	virtual BOOL OnInitDialog();
	afx_msg void OnCHECKSelfDefine();
	afx_msg void OnBUTTONStart();
	afx_msg void OnBUTTONStop();
	afx_msg void OnSelchangeCOMBOPwType();
	afx_msg void OnSelchangeCOMBOUsername();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WEAKKEYSCAN_H__0DA228BA_8050_4876_B23F_214F60010029__INCLUDED_)
