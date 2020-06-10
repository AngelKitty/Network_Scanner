// SQLScan.cpp : implementation file
//

#include "stdafx.h"
#include "Scanner.h"
#include "SQLScan.h"
#include <afxinet.h>

#include <winsock2.h>
#pragma comment(lib,"ws2_32")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAXRECEIVENUM (60*1000)

typedef struct SQLThreadParamStruct{
	CString		strIP;
	UINT		uPort;
	CString		strURL;
	CString		strObject;
	CSQLScan	*ptr;
	CString		strURLParam;
	CString		strSQLSign;
}SQLTHREADPARAM;
SQLTHREADPARAM SqlThreadParam;

UINT SqlThreadInjectScan(LPVOID pParam);
/////////////////////////////////////////////////////////////////////////////
// CSQLScan dialog


CSQLScan::CSQLScan(CWnd* pParent /*=NULL*/)
	: CDialog(CSQLScan::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSQLScan)
	m_strReceivePack = _T("");
	m_strSendPack = _T("");
	m_strSQLSign = _T("");
	m_strURL = _T("");
	m_strURLParam = _T("");
	m_strResult = _T("");
	//}}AFX_DATA_INIT
}


void CSQLScan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSQLScan)
	DDX_Text(pDX, IDC_EDITReveivePack, m_strReceivePack);
	DDX_Text(pDX, IDC_EDITSendPack, m_strSendPack);
	DDX_Text(pDX, IDC_EDITSQLSign, m_strSQLSign);
	DDX_Text(pDX, IDC_EDITURL, m_strURL);
	DDX_Text(pDX, IDC_EDITURLParam, m_strURLParam);
	DDX_Text(pDX, IDC_EDITResult, m_strResult);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSQLScan, CDialog)
	//{{AFX_MSG_MAP(CSQLScan)
	ON_BN_CLICKED(IDC_BUTTONStart, OnBUTTONStart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSQLScan message handlers

BOOL CSQLScan::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	WSAData	wsaData;
	WSAStartup(WINSOCK_VERSION,&wsaData);

	UpdateData(true);
	char buff[MAX_PATH];
	GetPrivateProfileString("SQLScan","URL","",buff,MAX_PATH,INIFILENAME);
	m_strURL.Format("%s",buff);
	GetPrivateProfileString("SQLScan","URLParam","",buff,MAX_PATH,INIFILENAME);
	m_strURLParam.Format("%s",buff);
	GetPrivateProfileString("SQLScan","SQLSign","",buff,MAX_PATH,INIFILENAME);
	m_strSQLSign.Format("%s",buff);
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSQLScan::OnBUTTONStart() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	DWORD			dwServiceType;
	INTERNET_PORT	nPort=8080;
	CString			strServer;
	CString			strObject;
	CString			strUsername;
	CString			strPassword;
	DWORD			dwFlags=0;
	CString			strURLParam;

	if(!AfxParseURLEx(m_strURL,dwServiceType,strServer,strObject,nPort,strUsername,strPassword,dwFlags)){
		MessageBox("URL格式不正确");
		return;
	}
	strURLParam=m_strURLParam;
	strURLParam.Replace("'","%27");
	strURLParam.Replace(" ","%20");

	CString strTemp;
	SqlThreadParam.strIP=strServer;
	SqlThreadParam.ptr=this;
	SqlThreadParam.uPort=nPort;
	SqlThreadParam.strURL=m_strURL;
	SqlThreadParam.strObject=strObject;
	SqlThreadParam.strURLParam=strURLParam;
	SqlThreadParam.strSQLSign=m_strSQLSign;
	AfxBeginThread(SqlThreadInjectScan,&SqlThreadParam,THREAD_PRIORITY_IDLE);
	UpdateData(false);
}

UINT SqlThreadInjectScan(LPVOID pParam){
	SQLTHREADPARAM *threadParam=(SQLTHREADPARAM *)pParam;
	CString		strIP=threadParam->strIP;
	UINT		uPort=threadParam->uPort;
	CSQLScan	*ptr=threadParam->ptr;
	CString		strURL=threadParam->strURL;
	CString		strObject=threadParam->strObject;
	CString		strURLParam=threadParam->strURLParam;
	CString		strSQLSign=threadParam->strSQLSign;

	SOCKET	sock=-1;
	sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock == SOCKET_ERROR){
		AfxMessageBox("创建sock出错");
		return 1;
	}
	int iTimeOut=1000;
	if(setsockopt(sock,SOL_SOCKET,SO_SNDTIMEO,(char *)&iTimeOut,sizeof(iTimeOut))==SOCKET_ERROR){
		AfxMessageBox("发送超时时间设置错误");
		return 2;
	}
	iTimeOut=1000;
	if(setsockopt(sock,SOL_SOCKET,SO_RCVTIMEO,(char *)&iTimeOut,sizeof(iTimeOut))==SOCKET_ERROR){
		AfxMessageBox("接收超时时间设置出错");
		return 3;
	}

	SOCKADDR_IN addr_remote;
	addr_remote.sin_family=AF_INET;
	addr_remote.sin_addr.S_un.S_addr=inet_addr(strIP);
	addr_remote.sin_port=htons(uPort);
	if(connect(sock,(PSOCKADDR)&addr_remote,sizeof(addr_remote))!=0){
		AfxMessageBox("Connect出错，对方未提供WWW服务");
		closesocket(sock);
		return 4;
	}

	CString strTemp;
	CString strSend="",strReceive="",strResult="";
	strSend.Format("POST %s?%s HTTP/1.0\r\n",strURL,strURLParam);
	strSend+=strTemp;
	strSend+="Accept: image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/vnd.ms-excel, application/msword, application/vnd.ms-powerpoint, */*\r\n";
	strSend+="Accept-Language: zh-cn\r\n";
	strSend+="Accept-Encoding: gzip, deflate\r\n";
	strSend+="User-Agent:Mozilla/4.0\r\n";
	strTemp.Format("Content-Length: %d\r\n",strURLParam.GetLength());
	strSend+=strTemp;
	strTemp.Format("Host: %s\r\n",strIP);
	strSend+=strTemp;
	strSend+="Content-Type: application/x-www-form-urlencoded\r\n";
	strSend+="\r\n";
	strSend+=strURLParam;
	send(sock,strSend.GetBuffer(0),strSend.GetLength(),0);

	UCHAR RecvBuf[MAXRECEIVENUM];
	int iLenRet=recv(sock,(char *)RecvBuf,MAXRECEIVENUM,0);
	if(iLenRet>0){
		RecvBuf[iLenRet]='\0';
		strReceive.Format("%s",RecvBuf);
		if(strReceive.Find(strSQLSign)>=0)
			strResult="存在注入漏洞";
		else
			strResult="不存在注入漏洞";
	}else{
		strResult="网络不通";
	}

	ptr->ShowSendAndReceive(strSend,strReceive,strResult);
	shutdown(sock,2);
	closesocket(sock);
	ptr->UpdateData(false);
	return 0;
}

void CSQLScan::ShowSendAndReceive(CString strSend, CString strReceive, CString strResult)
{
	//UpdateData(true);
	m_strSendPack.Format(strSend);
	m_strReceivePack.Format(strReceive);
	m_strResult.Format(strResult);
	//UpdateData(false);
}
