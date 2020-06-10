#if !defined(AFX_NETBIOSSCAN_H__219A28C1_7285_4EDC_BFCF_8C8F774F0472__INCLUDED_)
#define AFX_NETBIOSSCAN_H__219A28C1_7285_4EDC_BFCF_8C8F774F0472__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma comment(lib,"netapi32.lib")
#include "IPHlpApi.h"
#pragma comment(lib,"IPHlpApi.lib")
#include <lm.h>
#include <Winnetwk.h>
#pragma comment(lib,"Mpr.lib")
#define SV_TYPE_TERMINALSERVER 0x2000000
#define LIST_IP_INDEX		0
#define LIST_IP_IP			1
#define LIST_IP_HOSTNAME	2
#define LIST_IP_ALIASES		3


// NetBIOSScan.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetBIOSScan dialog

class CNetBIOSScan : public CDialog
{
// Construction
public:
	BOOL ReadTransport(USHORT *strIP,HTREEITEM rtItem);
	BOOL ReadSession(USHORT *strIP,HTREEITEM rtItem);
	BOOL ReadUser(USHORT *strIP,HTREEITEM rtItem);
	BOOL ReadProtocol(USHORT *strIP,HTREEITEM rtItem);
	BOOL ReadOS(USHORT *strIP,HTREEITEM rtItem);
	BOOL ReadLocalGroup(USHORT *strIP,HTREEITEM rtItem);
	BOOL ReadGroup(USHORT *strIP,HTREEITEM rtItem);
	BOOL ReadShareDirectory(USHORT *strIP,HTREEITEM rtItem);
	BOOL ReadTime(USHORT *strIP,HTREEITEM rtItem);
	BOOL ReadMAC(CString strIP,HTREEITEM rtItem);
	BOOL ReadHostName(CString strIP,HTREEITEM rtItem);
	BOOL ConnectServer(CString strIP,BOOL bConnect,HTREEITEM rtItem);
	CNetBIOSScan(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNetBIOSScan)
	enum { IDD = IDD_DIALOGNETBIOSSCAN };
	CTreeCtrl	m_ctlTreeResult;
	CIPAddressCtrl	m_ctlIP;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetBIOSScan)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetBIOSScan)
	virtual BOOL OnInitDialog();
	afx_msg void OnBUTTONStart();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETBIOSSCAN_H__219A28C1_7285_4EDC_BFCF_8C8F774F0472__INCLUDED_)
