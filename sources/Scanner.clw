; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSQLScan
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Scanner.h"

ClassCount=14
Class1=CScannerApp
Class2=CScannerDlg
Class3=CAboutDlg

ResourceCount=14
Resource1=IDD_DIALOGNETBIOSSCAN
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Resource4=IDD_DIALOGDOSSCAN
Class4=CHostScan
Class5=CPortScan
Resource5=IDD_DIALOGSQLSCAN
Class6=CWeakKeyScan
Resource6=IDD_DIALOGSSSelectIP
Class7=CDosScan
Resource7=IDD_DIALOGALLSCAN
Class8=CSnifferScan
Resource8=IDD_DIALOGHOSTSCAN
Class9=CSSSelectIP
Resource9=IDD_DIALOGSNIFFERSCAN
Class10=CSQLScan
Resource10=IDD_DIALOGWEAKKEYSCAN
Class11=CNetBIOSScan
Resource11=IDD_DIALOGSNMPSCAN
Class12=CSNMPScan
Resource12=IDD_DIALOGPORTSCAN
Class13=CAllScan
Resource13=IDD_SCANNER_DIALOG
Class14=CCmdDlg
Resource14=IDD_DIALOGCMD

[CLS:CScannerApp]
Type=0
HeaderFile=Scanner.h
ImplementationFile=Scanner.cpp
Filter=N

[CLS:CScannerDlg]
Type=0
HeaderFile=ScannerDlg.h
ImplementationFile=ScannerDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_EDITTest

[CLS:CAboutDlg]
Type=0
HeaderFile=ScannerDlg.h
ImplementationFile=ScannerDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_SCANNER_DIALOG]
Type=1
Class=CScannerDlg
ControlCount=1
Control1=IDC_TABMAIN,SysTabControl32,1342177280

[DLG:IDD_DIALOGHOSTSCAN]
Type=1
Class=CHostScan
ControlCount=8
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_BUTTONStartScan,button,1342242816
Control4=IDC_LISTResult,SysListView32,1350631429
Control5=IDC_IPADDRESSBegin,SysIPAddress32,1342242816
Control6=IDC_IPADDRESSEnd,SysIPAddress32,1342242816
Control7=IDC_BUTTONStopScan,button,1342242816
Control8=IDC_BUTTONCmd,button,1342242816

[DLG:IDD_DIALOGPORTSCAN]
Type=1
Class=CPortScan
ControlCount=11
Control1=IDC_STATIC,static,1342308352
Control2=IDC_IPADDRESSBgeinIP,SysIPAddress32,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_IPADDRESSEndIP,SysIPAddress32,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDITBeginPort,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDITEndPort,edit,1350631552
Control9=IDC_BUTTONStart,button,1342242816
Control10=IDC_TREEResult,SysTreeView32,1350631431
Control11=IDC_BUTTONStop,button,1342242816

[CLS:CHostScan]
Type=0
HeaderFile=HostScan.h
ImplementationFile=HostScan.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_BUTTONStartScan

[CLS:CPortScan]
Type=0
HeaderFile=PortScan.h
ImplementationFile=PortScan.cpp
BaseClass=CDialog
Filter=D
LastObject=CPortScan
VirtualFilter=dWC

[DLG:IDD_DIALOGWEAKKEYSCAN]
Type=1
Class=CWeakKeyScan
ControlCount=23
Control1=IDC_STATIC,static,1342308352
Control2=IDC_IPADDRESSIP,SysIPAddress32,1342242816
Control3=IDC_BUTTONStart,button,1342242816
Control4=IDC_EDITUSERNAME,edit,1350631552
Control5=IDC_STATIC,static,1342308353
Control6=IDC_EDITPrefix,edit,1350631552
Control7=IDC_STATIC,static,1342308353
Control8=IDC_EDITPostfix,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_COMBOLENGTH,combobox,1344340226
Control11=IDC_CHECKCAPITAL,button,1342373891
Control12=IDC_CHECKLOWER,button,1342242819
Control13=IDC_CHECKNUMBER,button,1342242819
Control14=IDC_CHECKSPECIAL,button,1342242819
Control15=IDC_EDITWEAKKEYRESULT,edit,1350631552
Control16=IDC_CHECKSelfDefine,button,1342242819
Control17=IDC_EDITSelfDefine,edit,1350631552
Control18=IDC_STATIC,button,1342177287
Control19=IDC_STATIC,button,1342177287
Control20=IDC_BUTTONStop,button,1342242816
Control21=IDC_COMBOPwType,combobox,1344340226
Control22=IDC_EDITPwType,edit,1350633600
Control23=IDC_COMBOUsername,combobox,1344340226

[CLS:CWeakKeyScan]
Type=0
HeaderFile=WeakKeyScan.h
ImplementationFile=WeakKeyScan.cpp
BaseClass=CDialog
Filter=D
LastObject=CWeakKeyScan
VirtualFilter=dWC

[DLG:IDD_DIALOGDOSSCAN]
Type=1
Class=CDosScan
ControlCount=9
Control1=IDC_STATIC,static,1342308352
Control2=IDC_IPADDRESSTARGETIP,SysIPAddress32,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDITTARGETPORT,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDITTHREADCOUNT,edit,1350631552
Control7=IDC_BUTTONStart,button,1342242816
Control8=IDC_BUTTONStop,button,1342242816
Control9=IDC_EDITComment,edit,1350631552

[CLS:CDosScan]
Type=0
HeaderFile=DosScan.h
ImplementationFile=DosScan.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT1
VirtualFilter=dWC

[DLG:IDD_DIALOGSNIFFERSCAN]
Type=1
Class=CSnifferScan
ControlCount=11
Control1=IDC_LISTReceive,SysListView32,1350631429
Control2=IDC_LISTKeyword,listbox,1352728835
Control3=IDC_BUTTONStart,button,1342242816
Control4=IDC_BUTTONStop,button,1342242816
Control5=IDC_EDITComment,edit,1350631552
Control6=IDC_BUTTONClear,button,1342242816
Control7=IDC_BUTTONAddKW,button,1342242816
Control8=IDC_EDITKeyword,edit,1350631552
Control9=IDC_BUTTONDeleteKW,button,1342242816
Control10=IDC_EDITContent,edit,1353777284
Control11=IDC_STATIC,button,1342177287

[CLS:CSnifferScan]
Type=0
HeaderFile=SnifferScan.h
ImplementationFile=SnifferScan.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_BUTTONClear

[DLG:IDD_DIALOGSSSelectIP]
Type=1
Class=CSSSelectIP
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LISTIP,listbox,1352728835

[CLS:CSSSelectIP]
Type=0
HeaderFile=SSSelectIP.h
ImplementationFile=SSSelectIP.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[DLG:IDD_DIALOGSQLSCAN]
Type=1
Class=CSQLScan
ControlCount=12
Control1=IDC_STATIC,static,1342308352
Control2=IDC_EDITURL,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDITURLParam,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDITSQLSign,edit,1350631552
Control7=IDC_STATIC,button,1342177287
Control8=IDC_EDITSendPack,edit,1352728708
Control9=IDC_STATIC,button,1342177287
Control10=IDC_EDITReveivePack,edit,1352728708
Control11=IDC_BUTTONStart,button,1342242816
Control12=IDC_EDITResult,edit,1350631552

[CLS:CSQLScan]
Type=0
HeaderFile=SQLScan.h
ImplementationFile=SQLScan.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CSQLScan

[DLG:IDD_DIALOGNETBIOSSCAN]
Type=1
Class=CNetBIOSScan
ControlCount=4
Control1=IDC_IPADDRESSIP,SysIPAddress32,1342242816
Control2=IDC_STATIC,static,1342308352
Control3=IDC_BUTTONStart,button,1342242816
Control4=IDC_TREEResult,SysTreeView32,1350631431

[CLS:CNetBIOSScan]
Type=0
HeaderFile=NetBIOSScan.h
ImplementationFile=NetBIOSScan.cpp
BaseClass=CDialog
Filter=D
LastObject=CNetBIOSScan
VirtualFilter=dWC

[DLG:IDD_DIALOGSNMPSCAN]
Type=1
Class=CSNMPScan
ControlCount=4
Control1=IDC_STATIC,static,1342308352
Control2=IDC_IPADDRESSTarget,SysIPAddress32,1342242816
Control3=IDC_BUTTONStart,button,1342242816
Control4=IDC_TREEResult,SysTreeView32,1350631431

[CLS:CSNMPScan]
Type=0
HeaderFile=SNMPScan.h
ImplementationFile=SNMPScan.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CSNMPScan

[DLG:IDD_DIALOGALLSCAN]
Type=1
Class=CAllScan
ControlCount=16
Control1=IDC_BUTTONStart,button,1342242816
Control2=IDC_STATIC,button,1342177287
Control3=IDC_CHECKHostScan,button,1342242819
Control4=IDC_CHECKPortScan,button,1342242819
Control5=IDC_CHECKWeakKeyScan,button,1342242819
Control6=IDC_CHECKDDOSScan,button,1342242819
Control7=IDC_CHECKSnifferScan,button,1342242819
Control8=IDC_CHECKSQLScan,button,1342242819
Control9=IDC_CHECKNetBIOSScan,button,1342242819
Control10=IDC_CHECKSNMPScan,button,1342242819
Control11=IDC_STATIC,button,1342177287
Control12=IDC_RADIOHtml,button,1342308361
Control13=IDC_RADIOTxt,button,1342177289
Control14=IDC_RADIOXml,button,1342177289
Control15=IDC_STATIC,static,1342308352
Control16=IDC_IPADDRESSTarget,SysIPAddress32,1342242816

[CLS:CAllScan]
Type=0
HeaderFile=AllScan.h
ImplementationFile=AllScan.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT1
VirtualFilter=dWC

[DLG:IDD_DIALOGCMD]
Type=1
Class=CCmdDlg
ControlCount=4
Control1=IDC_STATIC,static,1342308865
Control2=IDC_EDITCommand,edit,1350631552
Control3=IDC_BUTTONExecute,button,1342242816
Control4=IDC_EDITResult,edit,1352728708

[CLS:CCmdDlg]
Type=0
HeaderFile=CmdDlg.h
ImplementationFile=CmdDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CCmdDlg



