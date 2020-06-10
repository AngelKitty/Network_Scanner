// AllScan.cpp : implementation file
//

#include "stdafx.h"
#include "Scanner.h"
#include "AllScan.h"
#include "ScannerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAllScan dialog
extern CScannerDlg *pDlg;
extern CHostScan *pDlgHostScan;
extern CPortScan *pDlgPortScan;
extern CWeakKeyScan *pDlgWeakKeyScan;
extern CNetBIOSScan *pDlgNetBIOSScan;
extern CSNMPScan *pDlgSNMPScan;

CAllScan::CAllScan(CWnd* pParent /*=NULL*/)
	: CDialog(CAllScan::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAllScan)
	m_iRadioReportType = -1;
	m_bCheckDDOSScan = FALSE;
	m_bCheckHostScan = FALSE;
	m_bCheckNetBIOSScan = FALSE;
	m_bCheckPortScan = FALSE;
	m_bCheckSnifferScan = FALSE;
	m_bCheckSNMPScan = FALSE;
	m_bCheckWeakKeyScan = FALSE;
	m_bCheckSQLScan = FALSE;
	//}}AFX_DATA_INIT
}


void CAllScan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAllScan)
	DDX_Control(pDX, IDC_IPADDRESSTarget, m_ctlTargetIP);
	DDX_Radio(pDX, IDC_RADIOHtml, m_iRadioReportType);
	DDX_Check(pDX, IDC_CHECKDDOSScan, m_bCheckDDOSScan);
	DDX_Check(pDX, IDC_CHECKHostScan, m_bCheckHostScan);
	DDX_Check(pDX, IDC_CHECKNetBIOSScan, m_bCheckNetBIOSScan);
	DDX_Check(pDX, IDC_CHECKPortScan, m_bCheckPortScan);
	DDX_Check(pDX, IDC_CHECKSnifferScan, m_bCheckSnifferScan);
	DDX_Check(pDX, IDC_CHECKSNMPScan, m_bCheckSNMPScan);
	DDX_Check(pDX, IDC_CHECKWeakKeyScan, m_bCheckWeakKeyScan);
	DDX_Check(pDX, IDC_CHECKSQLScan, m_bCheckSQLScan);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAllScan, CDialog)
	//{{AFX_MSG_MAP(CAllScan)
	ON_BN_CLICKED(IDC_BUTTONStart, OnBUTTONStart)
	ON_BN_CLICKED(IDC_RADIOHtml, OnRADIOHtml)
	ON_BN_CLICKED(IDC_RADIOTxt, OnRADIOTxt)
	ON_BN_CLICKED(IDC_RADIOXml, OnRADIOXml)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAllScan message handlers

void CAllScan::OnBUTTONStart() 
{
	// TODO: Add your control notification handler code here
	/*CFile rebortFile("rebort.html",CFile::modeCreate|CFile::modeWrite);
	CString strRebort;
	strRebort="";
	strRebort+="<!DOCTYPE html>\n<html>\n<body>\n";
	strRebort+="helloWord!";
	strRebort+="</body>\n</html>";
	rebortFile.Write(strRebort,strlen(strRebort));
	rebortFile.Close();*/

	//GetParent()->
	//PostMessage(WM_COMMAND,MAKEWPARAM(IDC_BUTTONStartScan,BN_CLICKED),NULL);
	//AfxGetMainWnd()->m_strTest="gg";

	//(((int)pDlg->m_TabMain)).SetCurSel(2);
	//pDlg->m_TabMain.SetCurSel(4);
	/*((CScannerDlg *)pDlg)->m_TabMain.SetCurSel(2);
	NMHDR nmhdr;
	nmhdr.code=TCN_SELCHANGE;
	nmhdr.hwndFrom=((CScannerDlg *)pDlg)->m_TabMain.GetSafeHwnd();
	nmhdr.idFrom=IDC_TABMAIN;
	//this->PostMessage(WM_COMMAND,MAKEWPARAM(IDC_TABMAIN,TCN_SELCHANGE),NULL);
	::SendMessage(((CScannerDlg *)pDlg)->m_TabMain.GetSafeHwnd(),WM_NOTIFY,MAKELONG(TCN_SELCHANGE,0),(LPARAM)(&nmhdr));*/
	//pDlgHostScan->SendMessage(WM_COMMAND,IDC_BUTTONStartScan,0);
	UpdateData(true);
	int i,iListItemCount=0,number=1;
	UCHAR a,b,c,d;
	HTREEITEM root,child,childTemp;
	CString strIP,strTemp;
	m_ctlTargetIP.GetAddress(a,b,c,d);
	strIP.Format("%d.%d.%d.%d",a,b,c,d);
	strReportContent="<!DPCTYPE html>\n<html>\n<head>\n";
	strReportContent+="<script type=\"text/javascript\">\n";
    strReportContent+="function initNodes(){\n";
    strReportContent+="var uls = document.getElementsByTagName(\"ul\");\n";
    strReportContent+="var i;\n";
    strReportContent+="for(i = 0; i < uls.length; i++);\n";
    strReportContent+="if(uls[i].id != \"root\");\n";
    strReportContent+="uls[i].style.display = \"none\";\n";
    strReportContent+="}\n";

    strReportContent+="function clickNode(id){\n";
    strReportContent+="var node = document.getElementById(id);\n";
    strReportContent+="if(node.style.display == \"none\")\n";
    strReportContent+="node.style.display = \"block\";\n";
    strReportContent+="else\n";
    strReportContent+="node.style.display = \"none\";\n";
    strReportContent+="return false;\n";
    strReportContent+="}</script></head>\n";
	strReportContent+="<body>\n";
	if(m_bCheckHostScan){
		pDlgHostScan->m_ctlBeginIP.SetWindowText(strIP);
		pDlgHostScan->m_ctlEndIP.SetWindowText(strIP);
		UpdateData(false);
		//pDlgHostScan->SendMessage(WM_COMMAND,IDC_BUTTONStartScan,0);
		Sleep(3000);
		UpdateData(true);
		//int iCount=pDlgHostScan->m_ctlListResult.GetItemCount();
		//strReportContent+="<h1>"+number;
		strTemp.Format("<h2>%d",number);
		strReportContent+=strTemp;
		strReportContent+=".主机扫描</h2>\n";
		number++;
		strReportContent+="<table border='1'cellspacing=\"0\" cellpadding=\"10\">\n";
		strReportContent+="<tr><th width=100px>IP</th><th width=100px>状态</th><th width=100px>操作系统</th></tr>\n";
		strReportContent+="<tr><td align=center>"+pDlgHostScan->m_ctlListResult.GetItemText(0,1)+"</td>";
		strReportContent+="<td align=center>"+pDlgHostScan->m_ctlListResult.GetItemText(0,2)+"</td>";
		strReportContent+="<td align=center>"+pDlgHostScan->m_ctlListResult.GetItemText(0,3)+"</td></tr>\n";
		strReportContent+="</table>";
		strTemp=pDlgHostScan->m_ctlListResult.GetItemText(0,3);
		//MessageBox(strTemp);
	}
	if(m_bCheckPortScan){
		strReportContent+="\n<br/>\n";
		pDlgPortScan->m_ctlBeginIP.SetWindowText(strIP);
		pDlgPortScan->m_ctlEndIP.SetWindowText(strIP);
		pDlgPortScan->m_uBeginPort=0;
		pDlgPortScan->m_uEndPort=1024;
		UpdateData(false);
		//pDlgPortScan->SendMessage(WM_COMMAND,IDC_BUTTONStart,0);
		strTemp.Format("<h2>%d",number);
		strReportContent+=strTemp;
		strReportContent+=".端口扫描</h2>\n";
		number++;
		root=pDlgPortScan->m_ctlTreeResult.GetRootItem();
		strTemp=pDlgPortScan->m_ctlTreeResult.GetItemText(root);
		strReportContent+="<ul id=\"root\">\n";
		strReportContent+="<li>"+strTemp+"\n";
		child=pDlgPortScan->m_ctlTreeResult.GetChildItem(root);
		if(child==NULL){
			strReportContent+="<p>无开放端口</p>";
		}else{
			strTemp=pDlgPortScan->m_ctlTreeResult.GetItemText(child);
			//strReportContent+="<ul id=\"r1n1\">";
			strReportContent+="<ul id=\"r1n1\">\n<li>"+strTemp+"</li>\n";
			while((child=pDlgPortScan->m_ctlTreeResult.GetNextSiblingItem(child))!=NULL)
				strReportContent+="<li>"+pDlgPortScan->m_ctlTreeResult.GetItemText(child)+"</li>";
			strReportContent+="\n</ul></li>";
		}
		strReportContent+="\n</ul>";
	}

	if(m_bCheckWeakKeyScan){
		strReportContent+="<br/>\n";
		pDlgWeakKeyScan->m_ctlIP.SetWindowText(strIP);
		UpdateData(false);
		pDlgWeakKeyScan->SendMessage(WM_COMMAND,IDC_BUTTONStart,0);

		strTemp.Format("<h2>%d",number);
		strReportContent+=strTemp;
		strReportContent+=".弱密码扫描</h2>\n";
		number++;

		strReportContent+="<span>用户名:</span><span>"+pDlgWeakKeyScan->m_strUsername+"</span><br/>";
		strReportContent+="<span>密码：</span><span>"+pDlgWeakKeyScan->m_strResult+"</span><br/>";
	}

	if(m_bCheckNetBIOSScan){
		strReportContent+="\n<br/>\n";
		pDlgNetBIOSScan->m_ctlIP.SetWindowText(strIP);
		UpdateData(false);
		pDlgNetBIOSScan->SendMessage(WM_COMMAND,0);

		strTemp.Format("<h2>%d",number);
		strReportContent+=strTemp;
		strReportContent+=".NetBIOS扫描</h2>\n";
		number++;

		root=pDlgNetBIOSScan->m_ctlTreeResult.GetRootItem();
		strTemp=pDlgNetBIOSScan->m_ctlTreeResult.GetItemText(root);
		strReportContent+="<ul id=\"root\">\n";
		strReportContent+="<li>"+strTemp+"\n";

		child=pDlgNetBIOSScan->m_ctlTreeResult.GetChildItem(root);
		strTemp=pDlgNetBIOSScan->m_ctlTreeResult.GetItemText(child);
		strReportContent=="<ul id=\"NetBIOSSub\"><li>"+strTemp+"</li>\n<ul>";

		child=pDlgNetBIOSScan->m_ctlTreeResult.GetNextSiblingItem(child);
		strTemp=pDlgNetBIOSScan->m_ctlTreeResult.GetItemText(child);
		strReportContent+="<li>"+strTemp+"</li>\n";//MAC

		childTemp=child=pDlgNetBIOSScan->m_ctlTreeResult.GetNextSiblingItem(child);
		strTemp=pDlgNetBIOSScan->m_ctlTreeResult.GetItemText(child);
		strReportContent+="<li>"+strTemp+"</li>\n";//时间

		CString strName[7]={"NetBIOSScanSubShareSub","NetBIOSScanSubGroupSup","NetBIOSScanSubOSSup","NetBIOSScanSubServiceSub",
							"NetBIOSScanSubUserSub","NetBIOSScanSubSessionSub","NetBIOSScanSubConnectSub"};
		i=0;
		while((childTemp=child=pDlgNetBIOSScan->m_ctlTreeResult.GetNextSiblingItem(childTemp))!=NULL){
			strTemp=pDlgNetBIOSScan->m_ctlTreeResult.GetItemText(child);
			strReportContent+="<li><span onclick=\"return clickNode('"+strName[i]+"')\">"+strTemp+"</span>\n";//共享文件夹
			child=pDlgNetBIOSScan->m_ctlTreeResult.GetChildItem(child);
			strTemp=pDlgNetBIOSScan->m_ctlTreeResult.GetItemText(child);
			strReportContent+="<ul id=\""+strName[i]+"\"><li>"+strTemp+"</li>";
			i++;
			while((child=pDlgNetBIOSScan->m_ctlTreeResult.GetChildItem(child))!=NULL){
				strTemp=pDlgNetBIOSScan->m_ctlTreeResult.GetItemText(child);
				strReportContent+="<li>"+strTemp+"</li>\n";
			}
			strReportContent+="</ul></li>\n";
		}

		strReportContent+="</ul></ul>";
	}

	if(m_bCheckSNMPScan){
		strReportContent+="\n\n";
		
	}

	strReportContent+="</body>\n</html>";
	CFile rebortFile("rebort.html",CFile::modeCreate|CFile::modeWrite);
	rebortFile.Write(strReportContent,strlen(strReportContent));
	rebortFile.Close();
}

BOOL CAllScan::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//GetParent()->GetParent()->
	m_iRadioReportType=0;
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAllScan::OnRADIOHtml() 
{
	// TODO: Add your control notification handler code here
	m_iRadioReportType=0;
}

void CAllScan::OnRADIOTxt() 
{
	// TODO: Add your control notification handler code here
	m_iRadioReportType=1;
}

void CAllScan::OnRADIOXml() 
{
	// TODO: Add your control notification handler code here
	m_iRadioReportType=2;
}
