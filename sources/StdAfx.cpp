// stdafx.cpp : source file that includes just the standard includes
//	Scanner.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

CString IPIntToStr(UINT IPInt)
{
	UNIONIP IP;
	CString IPStr;
	
	IP.uInt=IPInt;
	IPStr.Format("%d.%d.%d.%d",IP.ucByte[0],IP.ucByte[1],IP.ucByte[2],IP.ucByte[3]);
	return IPStr;
}

UINT IPStrToInt(CString IPStr)
{
	UNIONIP IP;
	
	int i,j=0;
	IPStr.TrimLeft(" ");
	IPStr.TrimRight(" ");
	for (i=0;i<IPStr.GetLength();i++)
	{
		if (IPStr.GetAt(i) <'0' || IPStr.GetAt(i)>'9')
			if (IPStr.GetAt(i) == '.')
				j++;
			else
				return 0;		
	}
	if (j!=3)
		return 0;
	i=0;
	IPStr+=".";
	CString temp;
	for (int m=0;m<4;m++)
	{		
		temp="";
		while (IPStr.GetAt(i) != '.')
		{
			temp+=IPStr.GetAt(i);
			i++;
		}
		i++;
		if (temp=="" || atoi(temp) > 0xFF)
			return 0;
		else
			IP.ucByte[m]=atoi(temp);
	}
	return IP.uInt;
}


