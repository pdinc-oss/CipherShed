#include "LoadCursorMock.h"

#include "MAKEINTRESOURCE.h"

#include "../../../Common/util/unicode/ConvertUTF.h"
#include "../../../Common/util/unicode/strlenw.h"
#include "NULL.h"
#include "IDC_x.h"

/**

See: https://msdn.microsoft.com/en-us/library/windows/desktop/ms648391(v=vs.85).aspx

*/


//std::map<std::string,FauxLoadCursorTableEntry> cursors;

#define NAME_IDC_WAIT "IDC_WAIT"
#define NAME_IDC_ARROW "IDC_ARROW"
#define NAME_IDC_APPSTARTING "IDC_APPSTARTING"
#define NAME_IDC_HAND "IDC_HAND"

std::map<int,std::string> IDCinit()
{
 std::map<int,std::string> m;
 m[(int)IDC_WAIT]=NAME_IDC_WAIT;
 m[(int)IDC_ARROW]=NAME_IDC_ARROW;
 m[(int)IDC_APPSTARTING]=NAME_IDC_APPSTARTING;
 m[(int)IDC_HAND]=NAME_IDC_HAND;
 return m;
}
std::map<int,std::string> IDCx=IDCinit();

FauxLoadCursorTableEntry FAUX_CURSOR_IDC_WAIT;

std::map<std::string,FauxLoadCursorTableEntry> NULLcursorInit()
{
	std::map<std::string,FauxLoadCursorTableEntry> m;
	m[NAME_IDC_WAIT]=FAUX_CURSOR_IDC_WAIT;
	return m;
}
std::map<std::string,FauxLoadCursorTableEntry> NULLcursors=NULLcursorInit();

std::map<HCURSOR,FauxLoadCursorTableEntry> loadedCursors;
std::map<std::string,HCURSOR> loadedCursorReference;
HCURSOR nextCursorSlot=(HCURSOR)1;

std::map<HINSTANCE,std::map<std::string,FauxLoadCursorTableEntry> > initCursorCatalogs()
{
	std::map<HINSTANCE,std::map<std::string,FauxLoadCursorTableEntry> > map;
	map[NULL]=NULLcursors;
	return map;
}


std::map<HINSTANCE,std::map<std::string,FauxLoadCursorTableEntry> > cursorcatalogs=initCursorCatalogs();

int APIFailMode=0;

int getAPIFailMode(){return APIFailMode;}
void setAPIFailMode(int mode){APIFailMode=mode;}

HCURSOR LoadCursorA(HINSTANCE hInstance, LPCSTR lpCursorName)
{
	std::string key;
	if (lpCursorName==NULL)
	{
		if (APIFailMode)
			throw "Null cursor name";
		else
			return NULL;
		return NULL;
	}
	else if (hInstance==NULL && IS_INTRESOURCE(lpCursorName))
	{
		if (IDCx.count((int)lpCursorName==0))
		{
			if (APIFailMode)
				throw "Cursor ID not found in lookup table";
			else
				return NULL;
		}
		key=IDCx[(int)lpCursorName];
	}
	else
	{
		key=lpCursorName;
	}

	if (cursorcatalogs.count(hInstance)==0)
	{
		if (APIFailMode)
			throw "unknown hInstance";
		else
			return NULL;
	}

	std::map<std::string,FauxLoadCursorTableEntry> catalog=cursorcatalogs[hInstance];

	/*
	if (catalog==NULL)
	{
		if (APIFailMode)
			throw "hInstance results in NULL catalog";
		else
			return NULL;
	}
	*/

	if (catalog.count(key)==0)
	{
		if (APIFailMode)
			throw "cursor name not found in catalog";
		else
			return NULL;
	}

	if (loadedCursorReference.count(key)==1)
	{
		return loadedCursorReference[key];
	}
	else
	{
		HCURSOR mySlot=nextCursorSlot++;
		loadedCursorReference[key]=mySlot;
		loadedCursors[mySlot]=catalog[key];
		return mySlot;
	}
}

HCURSOR LoadCursorW(HINSTANCE hInstance, LPCWSTR lpCursorName)
{
	//special case
	if (hInstance == NULL && IS_INTRESOURCE(lpCursorName)) return LoadCursorA(hInstance,(LPCSTR)lpCursorName);

	char buf[2048];
	const UTF16* src=lpCursorName;
	int srclen=strlenw((WCHAR*)lpCursorName);
	UTF8* dst=(UTF8*)buf;
	int dstlen=sizeof(buf)/sizeof(buf[0]);
	ConversionFlags flags=strictConversion;
	ConversionResult res=ConvertUTF16toUTF8s(src,srclen,dst,dstlen,flags);
	return LoadCursorA(hInstance,buf);
}




