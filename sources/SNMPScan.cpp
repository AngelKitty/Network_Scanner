// SNMPScan.cpp : implementation file
//

#include "stdafx.h"
#include "Scanner.h"
#include "SNMPScan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	MAXNUMIP 10000
#define MAXNUMLIST 200
#include <snmp.h>
#include <mgmtapi.h>
#pragma comment(lib,"snmpapi")
#pragma comment(lib,"mgmtapi")
CSNMPScan *pDlgSNMPScan;

/////////////////////////////////////////////////////////////////////////////
// CSNMPScan dialog


CSNMPScan::CSNMPScan(CWnd* pParent /*=NULL*/)
	: CDialog(CSNMPScan::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSNMPScan)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSNMPScan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSNMPScan)
	DDX_Control(pDX, IDC_IPADDRESSTarget, m_ctlIP);
	DDX_Control(pDX, IDC_TREEResult, m_ctlTreeResult);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSNMPScan, CDialog)
	//{{AFX_MSG_MAP(CSNMPScan)
	ON_BN_CLICKED(IDC_BUTTONStart, OnBUTTONStart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSNMPScan message handlers

BOOL CSNMPScan::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char buffer[MAX_PATH];
	GetPrivateProfileString("SNMPScan","TargetIP","192.168.0.101",buffer,MAX_PATH,INIFILENAME);
	m_ctlIP.SetWindowText(buffer);
	UpdateData(false);
	pDlgSNMPScan=this;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSNMPScan::OnBUTTONStart() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	UCHAR a,b,c,d;
	CString strIP,strTemp,strOid;
	int iTemp;
	m_ctlIP.GetAddress(a,b,c,d);
	strIP.Format("%d.%d.%d.%d",a,b,c,d);
	strTemp.Format("SNMP扫描[%s]",strIP);
	HTREEITEM root=m_ctlTreeResult.InsertItem(strTemp,0,1);

	strOid=".1.3.6.1.2.1.25.1.1.0";
	iTemp=atoi(GetValue(strIP,strOid,0))/1000;
	strTemp.Format("系统启动时间：%d时%02d分%02d秒",iTemp/3600,(iTemp%3600)/60,iTemp%60);
	m_ctlTreeResult.InsertItem(strTemp,4,5,root);

	strOid=".1.3.6.1.2.1.1.1.0";
	strTemp.Format("系统信息：%s",GetValue(strIP,strOid,0));
	m_ctlTreeResult.InsertItem(strTemp,4,5,root);

	strOid=".1.3.6.1.4.1.77.1.4.1.0";
	strTemp.Format("主机名称：%s",GetValue(strIP,strOid,0));
	m_ctlTreeResult.InsertItem(strTemp,4,5,root);

	HTREEITEM curr=m_ctlTreeResult.InsertItem("当前进程：",2,3,root);
	strOid=".1.3.6.1.2.1.25.4.2.1.2";
	BOOL bContinue=true;
	while(bContinue){
		strTemp=GetValue(strIP,strOid,1);
		if((strOid.Find("hrSWEunName")<0)||strTemp=="")
			bContinue=false;
		else
			m_ctlTreeResult.InsertItem(strTemp,4,5,curr);
	}

	curr=m_ctlTreeResult.InsertItem("用户列表：",2,3,root);
	strOid=".1.3.6.1.4.1.77.1.2.25.1.1";
	bContinue=true;
	while(bContinue){
		strTemp=GetValue(strIP,strOid,1);
		if((strOid.Find("svUserName")<0)||strTemp=="")
			bContinue=false;
		else
			m_ctlTreeResult.InsertItem(strTemp,4,5,curr);
	}

	curr=m_ctlTreeResult.InsertItem("安装软件：",2,3,root);
	strOid=".1.3.6.1.2.1.25.6.3.1.2";
	bContinue=true;
	while(bContinue){
		strTemp=GetValue(strIP,strOid,1);
		if((strOid.Find("hrSWInstalledName")<0)||strTemp=="")
			bContinue=false;
		else
			m_ctlTreeResult.InsertItem(strTemp,4,5,curr);
	}

	curr=m_ctlTreeResult.InsertItem("网卡数：",2,3,root);
	strOid=".1.3.6.1.2.1.2.2.1.2";
	bContinue=true;
	while(bContinue){
		strTemp=GetValue(strIP,strOid,1);
		if((strOid.Find("ifDescr")<0)||strTemp=="")
			bContinue=false;
		else
			m_ctlTreeResult.InsertItem(strTemp,4,5,curr);
	}

	CStringArray sa[4];
	curr=m_ctlTreeResult.InsertItem("IP表：",2,3,root);
	strOid=".1.3.6.1.2.1.4.20.1.1";
	bContinue=true;
	while(bContinue){
		strTemp=GetValue(strIP,strOid,1);
		if((strOid.Find("ipAdEntAddr")<0)||strTemp=="")
			bContinue=false;
		else
			sa[0].Add(strTemp);
	}

	strOid=".1.3.6.1.2.1.4.20.1.3";
	bContinue=true;
	while(bContinue){
		strTemp=GetValue(strIP,strOid,1);
		if((strOid.Find("ipAdEntNetMask")<0)||strTemp=="")
			bContinue=false;
		else
			sa[1].Add(strTemp);
	}

	for(int i=0;i<sa[0].GetSize();i++){
		strTemp.Format("%s/%s",sa[0].GetAt(i),sa[1].GetAt(i));
		m_ctlTreeResult.InsertItem(strTemp,4,5,curr);
	}
	sa[0].RemoveAll();
	sa[1].RemoveAll();
	sa[2].RemoveAll();
	sa[3].RemoveAll();

	curr=m_ctlTreeResult.InsertItem("TCP连接[本地IP/Port->远端IP/Port]",2,3,root);
	strOid=".1.3.6.1.2.1.6.13.1.2";
	bContinue=true;
	while(bContinue){
		strTemp=GetValue(strIP,strOid,1);
		if((strOid.Find("tcpConnLocalAddress")<0)||strTemp=="")
			bContinue=false;
		else
			sa[0].Add(strTemp);
	}

	strOid=".1.3.6.1.2.1.6.13.1.3";
	bContinue=true;
	while(bContinue){
		strTemp=GetValue(strIP,strOid,1);
		if((strOid.Find("tcpConnLocalPort")<0)||strTemp=="")
			bContinue=false;
		else
			sa[1].Add(strTemp);
	}

	strOid=".1.3.6.1.2.1.6.13.1.4";
	bContinue=true;
	while(bContinue){
		strTemp=GetValue(strIP,strOid,1);
		if((strOid.Find("tcpConnRemAddress")<0)||strTemp=="")
			bContinue=false;
		else
			sa[2].Add(strTemp);
	}

	strOid=".1.3.6.1.2.1.6.13.1.5";
	bContinue=true;
	while(bContinue){
		strTemp=GetValue(strIP,strOid,1);
		if((strOid.Find("tcpConnRemPort")<0)||strTemp=="")
			bContinue=false;
		else
			sa[3].Add(strTemp);
	}

	for(i=0;i<sa[0].GetSize();i++){
		strTemp.Format("%s/%s->%s/%s",sa[0].GetAt(i),sa[1].GetAt(i),sa[2].GetAt(i),sa[3].GetAt(i));
		m_ctlTreeResult.InsertItem(strTemp,4,5,curr);
	}
	sa[0].RemoveAll();
	sa[1].RemoveAll();
	sa[2].RemoveAll();
	sa[3].RemoveAll();

	curr=m_ctlTreeResult.InsertItem("UDP连接[本地IP/Port]:",2,3,root);
	strOid=".1.3.6.1.2.1.7.5.1.1";
	bContinue=true;
	while(bContinue){
		strTemp=GetValue(strIP,strOid,1);
		if((strOid.Find("udpLocalAddress")<0)||strTemp=="")
			bContinue=false;
		else
			sa[0].Add(strTemp);
	}

	strOid=".1.3.6.1.2.1.7.5.1.2";
	bContinue=true;
	while(bContinue){
		strTemp=GetValue(strIP,strOid,1);
		if((strOid.Find("udpLocalPort")<0)||strTemp=="")
			bContinue=false;
		else
			sa[1].Add(strTemp);
	}

	for(i=0;i<sa[0].GetSize();i++){
		strTemp.Format("%s/%s",sa[0].GetAt(i),sa[1].GetAt(i));
		m_ctlTreeResult.InsertItem(strTemp,4,5,curr);
	}
	sa[0].RemoveAll();
	sa[1].RemoveAll();
	sa[2].RemoveAll();
	sa[3].RemoveAll();

	UpdateData(false);
}

CString CSNMPScan::GetValue(CString strIP, CString &strOid, UCHAR ucType)
{
	CString strRet,strTemp;
	RFC1157VarBindList variableBindings;
	variableBindings.list=NULL;
	variableBindings.len=1;
	if((variableBindings.list=(RFC1157VarBind *)SNMP_realloc(variableBindings.list,sizeof(RFC1157VarBind)*1))==NULL)
		return strRet;
	AsnObjectIdentifier reqObject;
	if(!SnmpMgrStrToOid(strOid.GetBuffer(0),&reqObject))
		return strRet;
	variableBindings.list[0].name=reqObject;
	variableBindings.list[0].value.asnType=ASN_NULL;
	LPSNMP_MGR_SESSION session;
	int iTimeout=1000;
	int iTryTimes=1;
	if((session=SnmpMgrOpen(strIP.GetBuffer(0),"public",iTimeout,iTryTimes))==NULL){
		SnmpUtilVarBindListFree(&variableBindings);
		return strRet;
	}
	AsnInteger errorStatus;
	AsnInteger errorIndex;
	BYTE requestType;
	if(ucType==0){
		requestType=ASN_RFC1157_GETREQUEST;
	}else{
		requestType=ASN_RFC1157_GETNEXTREQUEST;
	}
	SNMPAPI bRet=SnmpMgrRequest(session,requestType,&variableBindings,&errorStatus,&errorIndex);
	if(errorStatus!=SNMP_ERRORSTATUS_NOERROR){
		SnmpUtilVarBindListFree(&variableBindings);
		SnmpMgrClose(session);
		return strRet;
	}

	char *string=NULL;
	UINT i,j;
	CString strValueValue;
	for(i=0;i<(int)variableBindings.len;i++){
		SnmpMgrOidToStr(&variableBindings.list[i].name,&string);
		strOid.Format("%s",string);
		if(string)
			SNMP_free(string);
		switch(variableBindings.list[i].value.asnType){
		case ASN_INTEGER:
			strValueValue.Format("%d",variableBindings.list[i].value.asnValue.number);
			break;
		case ASN_UNSIGNED32:
			strValueValue.Format("%u",variableBindings.list[i].value.asnValue.unsigned32);
			break;
		case ASN_COUNTER64:
			strValueValue.Format("%d",variableBindings.list[i].value.asnValue.counter64);
			break;
		case ASN_OCTETSTRING:
			strValueValue.Format("%s",variableBindings.list[i].value.asnValue.string.stream);
			strValueValue=strValueValue.Left(variableBindings.list[i].value.asnValue.string.length);
			/*strValueValue.Format("%d",variableBindings.list[i].value.asnValue.string.stream);
			strValueValue=strValueValue.Left(variableBindings.list[i].value.asnValue.string.length);
			strValueValue="";
			for(j=0;j<variableBindings.list[i].value.asnValue.string.length;j++){
				strTemp.Format("%c",variableBindings.list[i].value.asnValue.string.stream[j+1]);
				strValueValue+=strTemp;
			}*/
			//m_strValueValue.Format("%s",&variableBindings.list[i].value.asnValue.string.stream[0]);
			//m_strValueType="ASN_OCTETSTRING";
			break;
		case ASN_BITS:
			strValueValue="";
			for(j=0;j<variableBindings.list[i].value.asnValue.bits.length;j++){
				 strTemp.Format("%c",variableBindings.list[i].value.asnValue.bits.stream[j]);
				 strValueValue+=strTemp;
			}
			break;
		case ASN_OBJECTIDENTIFIER:
			strValueValue="";
			for(j=0;j<variableBindings.list[i].value.asnValue.object.idLength;j++){
				 strTemp.Format(".%d",variableBindings.list[i].value.asnValue.object.ids[j]);
				 strValueValue+=strTemp;
			}
			break;
		case ASN_SEQUENCE:
			strValueValue="";
			for(j=0;j<variableBindings.list[i].value.asnValue.sequence.length;j++){
				 strTemp.Format("%c",variableBindings.list[i].value.asnValue.sequence.stream[j]);
				 strValueValue+=strTemp;
			}
			break;
		case ASN_IPADDRESS:
			strValueValue="";
			for(j=0;j<variableBindings.list[i].value.asnValue.address.length;j++){
				 strTemp.Format("%d.",variableBindings.list[i].value.asnValue.address.stream[j]);
				 strValueValue+=strTemp;
			}
			strValueValue.TrimRight(".");
			break;
		case ASN_COUNTER32:
			strValueValue.Format("%d",variableBindings.list[i].value.asnValue.counter);
			break;
		case ASN_GAUGE32:
			strValueValue.Format("%d",variableBindings.list[i].value.asnValue.gauge);
			break;
		case ASN_TIMETICKS:
			strValueValue.Format("%d",variableBindings.list[i].value.asnValue.ticks);
			break;
		case ASN_OPAQUE:
			strValueValue="";
			for(j=0;j<variableBindings.list[i].value.asnValue.address.length;j++){
				 strTemp.Format("%d",variableBindings.list[i].value.asnValue.arbitrary.stream[j]);
				 strValueValue+=strTemp;
			}
			break;
		default:
			strValueValue="Undefined.";
			break;
		}
	}

	strRet=strValueValue;
	SnmpUtilVarBindListFree(&variableBindings);
	SnmpMgrClose(session);
	return strRet;
}
