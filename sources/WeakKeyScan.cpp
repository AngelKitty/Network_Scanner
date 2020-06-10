// WeakKeyScan.cpp : implementation file
//

#include "stdafx.h"
#include "Scanner.h"
#include "WeakKeyScan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma comment(lib, "mpr.lib" )
CWeakKeyScan *pDlgWeakKeyScan;
BOOL g_bWKSRunning;
/////////////////////////////////////////////////////////////////////////////
// CWeakKeyScan dialog


CWeakKeyScan::CWeakKeyScan(CWnd* pParent /*=NULL*/)
	: CDialog(CWeakKeyScan::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWeakKeyScan)
	m_strResult = _T("");
	m_bCharCapital = FALSE;
	m_bCharLower = FALSE;
	m_bCharNumber = FALSE;
	m_bCharSpecial = FALSE;
	m_strUsername = _T("");
	m_strSelfDefine = _T("");
	m_bCharSelfDefine = FALSE;
	m_strPrefix = _T("");
	m_strPostfix = _T("");
	m_strPassword = _T("");
	//}}AFX_DATA_INIT
}


void CWeakKeyScan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWeakKeyScan)
	DDX_Control(pDX, IDC_COMBOUsername, m_ctlUsername);
	DDX_Control(pDX, IDC_COMBOPwType, m_ctlPwType);
	DDX_Control(pDX, IDC_COMBOLENGTH, m_ctlPWLength);
	DDX_Control(pDX, IDC_IPADDRESSIP, m_ctlIP);
	DDX_Text(pDX, IDC_EDITWEAKKEYRESULT, m_strResult);
	DDX_Check(pDX, IDC_CHECKCAPITAL, m_bCharCapital);
	DDX_Check(pDX, IDC_CHECKLOWER, m_bCharLower);
	DDX_Check(pDX, IDC_CHECKNUMBER, m_bCharNumber);
	DDX_Check(pDX, IDC_CHECKSPECIAL, m_bCharSpecial);
	DDX_Text(pDX, IDC_EDITUSERNAME, m_strUsername);
	DDX_Text(pDX, IDC_EDITSelfDefine, m_strSelfDefine);
	DDX_Check(pDX, IDC_CHECKSelfDefine, m_bCharSelfDefine);
	DDX_Text(pDX, IDC_EDITPrefix, m_strPrefix);
	DDX_Text(pDX, IDC_EDITPostfix, m_strPostfix);
	DDX_Text(pDX, IDC_EDITPwType, m_strPassword);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWeakKeyScan, CDialog)
	//{{AFX_MSG_MAP(CWeakKeyScan)
	ON_BN_CLICKED(IDC_CHECKSelfDefine, OnCHECKSelfDefine)
	ON_BN_CLICKED(IDC_BUTTONStart, OnBUTTONStart)
	ON_BN_CLICKED(IDC_BUTTONStop, OnBUTTONStop)
	ON_CBN_SELCHANGE(IDC_COMBOPwType, OnSelchangeCOMBOPwType)
	ON_CBN_SELCHANGE(IDC_COMBOUsername, OnSelchangeCOMBOUsername)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWeakKeyScan message handlers

BOOL CWeakKeyScan::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString strTemp;
	char buff[MAX_PATH];
	GetPrivateProfileString("WeakKeyScan","ScanIP","192.168.0.101",buff,MAX_PATH,INIFILENAME);
	m_ctlIP.SetWindowText(buff);
	GetPrivateProfileString("WeakKeyScan","Username","Administrator",buff,MAX_PATH,INIFILENAME);
	m_strUsername.Format("%s",buff);
	m_ctlPWLength.SetCurSel(3);
	m_bCharSelfDefine = false;
	UpdateData(false);
	OnCHECKSelfDefine();
	pDlgWeakKeyScan = this;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWeakKeyScan::OnCHECKSelfDefine() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if(m_bCharSelfDefine){
		GetDlgItem(IDC_CHECKCAPITAL)->EnableWindow(false);
		GetDlgItem(IDC_CHECKLOWER)->EnableWindow(false);
		GetDlgItem(IDC_CHECKNUMBER)->EnableWindow(false);
		GetDlgItem(IDC_CHECKSPECIAL)->EnableWindow(false);
		GetDlgItem(IDC_EDITSelfDefine)->EnableWindow(true);
	}else{
		GetDlgItem(IDC_CHECKCAPITAL)->EnableWindow(true);
		GetDlgItem(IDC_CHECKLOWER)->EnableWindow(true);
		GetDlgItem(IDC_CHECKNUMBER)->EnableWindow(true);
		GetDlgItem(IDC_CHECKSPECIAL)->EnableWindow(true);
		GetDlgItem(IDC_EDITSelfDefine)->EnableWindow(false);
	}
}

void CWeakKeyScan::OnBUTTONStart() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CString strUsername,strPassword;
	CStdioFile unFile;
	switch(m_ctlUsername.GetCurSel()){
	case 1:
		switch(m_ctlPwType.GetCurSel()){
		case 0:		
			BruteForceScan(m_strUsername);
			break;
		case 1:
			CStdioFile pwFile;
			pwFile.Open(m_strPassword,CFile::modeRead);
			pwFile.ReadString(strPassword);
			while(strPassword!=""){
				//MessageBox(strPassword);
				ConnectServer(strPassword,m_strUsername);
				pwFile.ReadString(strPassword);
			}
		}
		break;
	case 0:
		unFile.Open(m_strUsername,CFile::modeRead);
		unFile.ReadString(strUsername);
		while(strUsername!=""){
			switch(m_ctlPwType.GetCurSel()){
			case 0:		
				BruteForceScan(strUsername);
				break;
			case 1:
				CStdioFile pwFile;
				pwFile.Open(m_strPassword,CFile::modeRead);
				pwFile.ReadString(strPassword);
				while(strPassword!=""){
				//MessageBox(strPassword);
					ConnectServer(strPassword,strUsername);
					pwFile.ReadString(strPassword);
				}
				break;
			}
			unFile.ReadString(strUsername);
		}
		break;
	}
	UpdateData(false);
}

BOOL CWeakKeyScan::ConnectServer(CString strPass, CString strUser)
{
	UCHAR a,b,c,d;
	CString strIPC;
	m_ctlIP.GetAddress(a,b,c,d);
	strIPC.Format("\\\\%d.%d.%d.%d\\ipc$",a,b,c,d);

	NETRESOURCE NET;
	NET.lpLocalName=NULL;
	NET.lpProvider=NULL;
	NET.dwType=RESOURCETYPE_ANY;
	NET.lpRemoteName=strIPC.GetBuffer(0);
	BOOL ret=WNetAddConnection2(&NET,strPass,strUser.GetBuffer(0),0);
	if(ret == ERROR_SUCCESS){
		m_strResult.Format("密码：%s",strPass);
		WNetCancelConnection2(strIPC.GetBuffer(0),0,true);
		l1=l2=l3=l4=l5=l6=l7=l8=100;
	}
	if (!g_bWKSRunning)
		l1=l2=l3=l4=l5=l6=l7=l8=100;
	return true;
}

void CWeakKeyScan::OnBUTTONStop() 
{
	// TODO: Add your control notification handler code here
	g_bWKSRunning=false;
}

void CWeakKeyScan::BruteForceScan(CString strUsername)
{
	UpdateData(true);
	char chAll[100];
	char chCapital[27]="QWERTYUIOPASDFGHJKLZXCVBNM";
	char chLower[27]="qwertyuiopasdfghjklzxcvbnm";
	char chNumber[11]="0123456789";
	char chOther[31]="`~!@#$%^&*()_+|-={}[];':<>,./?";
	int i,iPassLen;
	g_bWKSRunning=true;

	if(m_bCharSelfDefine){
		iPassLen = 0;
		int len = m_strSelfDefine.GetLength();
		for(i=0;i<len;i++){
			BOOL bRepeat = false;
			char chTemp=m_strSelfDefine.GetAt(i);
			for(int j=0;j<iPassLen;j++){
				if(chTemp==chAll[j]){
					bRepeat = true;
					j=iPassLen+1;
					break;
				}
			}
			if(!bRepeat){
				chAll[iPassLen]=chTemp;
				iPassLen++;
			}
		}
		chAll[iPassLen]='\0';
		m_strSelfDefine.Format("%s",(char *)chAll);
	}else{
		iPassLen = 0;
		if(m_bCharCapital){
			for(i=0;i<26;i++){
				chAll[iPassLen+i]=chCapital[i];
			}
			iPassLen+=26;
		}
		if(m_bCharLower){
			for(i=0;i<26;i++){
				chAll[iPassLen+i]=chLower[i];
			}
			iPassLen+=26;
		}
		if(m_bCharNumber){
			for(i=0;i<26;i++){
				chAll[iPassLen+i]=chNumber[i];
			}
			iPassLen+=26;
		}
		if(m_bCharSpecial){
			for(i=0;i<30;i++){
				chAll[iPassLen+i]=chOther[i];
			}
			iPassLen+=30;
		}
	}

	CString strPass;
	switch(m_ctlPWLength.GetCurSel()){
	case 0:
		strPass=m_strPrefix+m_strPostfix;
		/*int ret = WNetAddConnection2(&NET,strPass,(char *)username,0);
		if(ret==ERROR_SUCCESS){
			WNetCancelConnection2((char *)&ipc,0,TRUE);
		}*/
		break;
	case 1:
		for(l1=0;l1<iPassLen;l1++){
			strPass.Format("%s%c%s",m_strPrefix,chAll[l1],m_strPostfix);
			MessageBox(strPass);
			ConnectServer(strPass,strUsername);
		}
		break;
	case 2:
		for (l1=0;l1<iPassLen;l1++)
		 for (l2=0;l2<iPassLen;l2++)
		 {
			 strPass.Format("%s%c%c%s",m_strPrefix,chAll[l1],chAll[l2],m_strPostfix);
			 ConnectServer(strPass,strUsername);
		 }break;
	case 3:
		for (l1=0;l1<iPassLen;l1++)
		 for (l2=0;l2<iPassLen;l2++)
		  for (l3=0;l3<iPassLen;l3++)
		  {
			  strPass.Format("%s%c%c%c%s",m_strPrefix,chAll[l1],chAll[l2],chAll[l3],m_strPostfix);
			  ConnectServer(strPass,strUsername);
		  }break;
	case 4:
		for (l1=0;l1<iPassLen;l1++)
		 for (l2=0;l2<iPassLen;l2++)
		  for (l3=0;l3<iPassLen;l3++)
		   for (l4=0;l4<iPassLen;l4++)
		   {
			  strPass.Format("%s%c%c%c%c%s",m_strPrefix,chAll[l1],chAll[l2],chAll[l3],chAll[l4],m_strPostfix);
			  ConnectServer(strPass,strUsername);
		   }break;
	case 5:
		for (l1=0;l1<iPassLen;l1++)
		 for (l2=0;l2<iPassLen;l2++)
		  for (l3=0;l3<iPassLen;l3++)
		   for (l4=0;l4<iPassLen;l4++)
			for (l5=0;l5<iPassLen;l5++)
			{
				strPass.Format("%s%c%c%c%c%c%s",m_strPrefix,chAll[l1],chAll[l2],chAll[l3],chAll[l4],chAll[l5],m_strPostfix);
				ConnectServer(strPass,strUsername);
			}break;
	case 6:
		for (l1=0;l1<iPassLen;l1++)
		 for (l2=0;l2<iPassLen;l2++)
		  for (l3=0;l3<iPassLen;l3++)
		   for (l4=0;l4<iPassLen;l4++)
			for (l5=0;l5<iPassLen;l5++)
			 for (l6=0;l6<iPassLen;l6++)
			{
				strPass.Format("%s%c%c%c%c%c%c%s",m_strPrefix,
					chAll[l1],chAll[l2],chAll[l3],chAll[l4],chAll[l5],chAll[l6],m_strPostfix);
				ConnectServer(strPass,strUsername);
			 }break;
	case 7:
		for (l1=0;l1<iPassLen;l1++)
		 for (l2=0;l2<iPassLen;l2++)
		  for (l3=0;l3<iPassLen;l3++)
		   for (l4=0;l4<iPassLen;l4++)
			for (l5=0;l5<iPassLen;l5++)
			 for (l6=0;l6<iPassLen;l6++)
			  for (l7=0;l7<iPassLen;l7++)
			{
				strPass.Format("%s%c%c%c%c%c%c%c%s",m_strPostfix,
					chAll[l1],chAll[l2],chAll[l3],chAll[l4],chAll[l5],chAll[l6],chAll[l7],m_strPostfix);
				ConnectServer(strPass,strUsername);
			 }break;
	case 8:
		for (l1=0;l1<iPassLen;l1++)
		 for (l2=0;l2<iPassLen;l2++)
		  for (l3=0;l3<iPassLen;l3++)
		   for (l4=0;l4<iPassLen;l4++)
			for (l5=0;l5<iPassLen;l5++)
			 for (l6=0;l6<iPassLen;l6++)
			  for (l7=0;l7<iPassLen;l7++)
			   for (l8=0;l8<iPassLen;l8++)
			{
				strPass.Format("%s%c%c%c%c%c%c%c%c%s",m_strPrefix,
					chAll[l1],chAll[l2],chAll[l3],chAll[l4],chAll[l5],chAll[l6],chAll[l7],chAll[l8],m_strPostfix);
				ConnectServer(strPass,strUsername);
			}break;
	default:m_strResult="当前版本无法测试";
		break;
	}
	UpdateData(FALSE);
}

//DEL void CWeakKeyScan::OnChangeEDITPwType() 
//DEL {
//DEL 	// TODO: If this is a RICHEDIT control, the control will not
//DEL 	// send this notification unless you override the CDialog::OnInitDialog()
//DEL 	// function and call CRichEditCtrl().SetEventMask()
//DEL 	// with the ENM_CHANGE flag ORed into the mask.
//DEL 	
//DEL 	// TODO: Add your control notification handler code here
//DEL 	MessageBox("ok");
//DEL }

//DEL void CWeakKeyScan::OnEditchangeCOMBOPwType() 
//DEL {
//DEL 	// TODO: Add your control notification handler code here
//DEL 	MessageBox("ok");
//DEL }

void CWeakKeyScan::OnSelchangeCOMBOPwType() 
{
	// TODO: Add your control notification handler code here
	//MessageBox("ok");
	UpdateData(true);
	switch(m_ctlPwType.GetCurSel()){
	case 0:
		GetDlgItem(IDC_EDITPwType)->EnableWindow(false);
		break;
	case 1:
		GetDlgItem(IDC_EDITPwType)->EnableWindow(true);
		CFileDialog pwFileDlg(true,".dic",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"安典文件(.dic)|*.dic|所有文件(*.*)|*.*||");
		if(pwFileDlg.DoModal()==IDOK){
			m_strPassword=pwFileDlg.GetPathName();
			
		}
		break;
	}
	UpdateData(false);
}

void CWeakKeyScan::OnSelchangeCOMBOUsername() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	switch(m_ctlUsername.GetCurSel()){
	case 1:
		//MessageBox("1");
		m_strUsername="Administrator";
		break;
	case 0:
		//MessageBox("0");
		m_strUsername="";
		CFileDialog unFileDlg(true,".dic",NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"字典文件(.dic)|*.dic|所有文件(*.*)|*.*||");
		if(unFileDlg.DoModal()==IDOK){
			m_strUsername=unFileDlg.GetPathName();
		}
		break;
	}
	UpdateData(false);
}
