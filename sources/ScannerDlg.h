// ScannerDlg.h : header file
//

#if !defined(AFX_SCANNERDLG_H__89652A0B_2938_4B76_AD85_069C53C61EFC__INCLUDED_)
#define AFX_SCANNERDLG_H__89652A0B_2938_4B76_AD85_069C53C61EFC__INCLUDED_

#include "DosScan.h"	// Added by ClassView
#include "HostScan.h"	// Added by ClassView
#include "PortScan.h"
#include "WeakKeyScan.h"	// Added by ClassView
#include "SnifferScan.h"
#include "SQLScan.h"
#include "NetBIOSScan.h"
#include "SNMPScan.h"
#include "AllScan.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



/////////////////////////////////////////////////////////////////////////////
// CScannerDlg dialog

class CScannerDlg : public CDialog
{
// Construction
public:
	CAllScan m_AllScanTab;
	CSNMPScan m_SNMPScanTap;
	CNetBIOSScan m_NetBIOSScanTab;
	CSQLScan m_SQLScanTab;
	CSnifferScan m_SnifferScanTab;
	CDosScan m_DosScanTab;
	CWeakKeyScan m_WeakKeyScanTab;
	CPortScan m_PortScanTab;
	CHostScan m_HostScanTab;
	CScannerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CScannerDlg)
	enum { IDD = IDD_SCANNER_DIALOG };
	CTabCtrl	m_TabMain;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScannerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CScannerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeTabmain(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCANNERDLG_H__89652A0B_2938_4B76_AD85_069C53C61EFC__INCLUDED_)

