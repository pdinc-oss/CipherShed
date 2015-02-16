#include "csstringutil.h"


#include "../../Platform/SystemException.h"
#include "../../Platform/Exception.h"
#include "../../Platform/ForEach.h"
#include "memory.h"
#include <string.h>

#ifdef CS_UNITTESTING
#include "../../unit-tests/faux/windows/CP_ACP.h"
#include "../../unit-tests/faux/windows/MultiByteToWideChar.h"
#include "../../unit-tests/faux/windows/WideCharToMultiByte.h"
#include "../../unit-tests/faux/windows/_strupr.h"
#include <string>
#include <stdlib.h>
#endif

using namespace CipherShed;

/**
Why is this being used in a crypto program?
*/
void UpperCaseCopy (char *lpszDest, const char *lpszSource)
{
	int i = strlen (lpszSource);

	lpszDest[i] = 0;
	while (--i >= 0)
	{
		lpszDest[i] = (char) toupper (lpszSource[i]);
	}
}

/**
 @TODO use the unicode library.
 @TODO check for buffer overflows
*/
std::wstring SingleStringToWide (const std::string &singleString)
{
	if (singleString.empty())
		return std::wstring();

	WCHAR wbuf[65536];
	int wideLen = MultiByteToWideChar (CP_ACP, 0, singleString.c_str(), -1, wbuf, array_capacity (wbuf) - 1);
	throw_sys_if (wideLen == 0);

	wbuf[wideLen] = 0;
	return (wchar_t*)wbuf;
}

/**
 @TODO use the unicode library.
 @TODO check for buffer overflows
*/
std::string WideToSingleString (const std::wstring &wideString)
{
	if (wideString.empty())
		return std::string();

	char buf[65536];
	int len = WideCharToMultiByte (CP_ACP, 0, (LPCWSTR)wideString.c_str(), -1, buf, array_capacity (buf) - 1, NULL, NULL);
	throw_sys_if (len == 0);

	buf[len] = 0;
	return buf;
}

/**
converts a SBCS string to a UNICODE string.
 @TODO use the unicode library.
 @TODO check for buffer overflows
*/
void ToUNICODE (char *lpszText)
{
	int j = strlen (lpszText);
	if (j == 0)
	{
		wcscpy ((wchar_t*) lpszText, (wchar_t*) WIDE (""));
		return;
	}
	else
	{
		LPWSTR lpszNewText = (LPWSTR) err_malloc ((j + 1) * 2);
		j = MultiByteToWideChar (CP_ACP, 0L, lpszText, -1, lpszNewText, j + 1);
		if (j > 0)
			wcscpy ((wchar_t*) lpszText, (wchar_t*)lpszNewText);
		else
			wcscpy ((wchar_t*) lpszText, (wchar_t*) WIDE (""));
		free (lpszNewText);
	}
}

/**
 @TODO use the unicode library.
 @TODO check for buffer overflows
*/
std::wstring Utf8StringToWide (const std::string &utf8String)
{
	if (utf8String.empty())
		return std::wstring();

	WCHAR wbuf[65536];
	int wideLen = MultiByteToWideChar (CP_UTF8, 0, utf8String.c_str(), -1, wbuf, array_capacity (wbuf) - 1);
	throw_sys_if (wideLen == 0);

	wbuf[wideLen] = 0;
	return (wchar_t*)wbuf;
}


/**
 @TODO use the unicode library.
 @TODO check for buffer overflows
*/
std::string WideToUtf8String (const std::wstring &wideString)
{
	if (wideString.empty())
		return std::string();

	char buf[65536];
	int len = WideCharToMultiByte (CP_UTF8, 0, (LPCWSTR)wideString.c_str(), -1, buf, array_capacity (buf) - 1, NULL, NULL);
	throw_sys_if (len == 0);

	buf[len] = 0;
	return buf;
}

/**
Why is this being used in a crypto program?
*/
std::string ToUpperCase (const std::string &str)
{
	string u;
	foreach (char c, str)
	{
		u += (char) toupper (c);
	}

	return u;
}

/**
Why is this being used in a crypto program?
*/
void LowerCaseCopy (char *lpszDest, const char *lpszSource)
{
	int i = strlen (lpszSource);

	lpszDest[i] = 0;
	while (--i >= 0)
	{
		lpszDest[i] = (char) tolower (lpszSource[i]);
	}

}
/**
Why is this being used in a crypto program?
_strupr does an inplace replace of each char, this is bad mojo.
*/
std::string StringToUpperCase (const std::string &str)
{
	string upperCase (str);
	_strupr ((char *) upperCase.c_str());
	return upperCase;
}

void LeftPadString (char *szTmp, int len, int targetLen, char filler)
{
	int i;

	if (targetLen <= len)
		return;

	for (i = targetLen-1; i >= (targetLen-len); i--)
		szTmp [i] = szTmp [i-(targetLen-len)];

	memset (szTmp, filler, targetLen-len);
	szTmp [targetLen] = 0;
}


/**
  converts a unicode string to Single Byte Character String (SBCS).
 @TODO use the unicode library.
 @TODO check for buffer overflows
*/

void ToSBCS (LPWSTR lpszText)
{
	int j = wcslen ((const wchar_t *)lpszText);
	if (j == 0)
	{
		strcpy ((char *) lpszText, "");
		return;
	}
	else
	{
		char *lpszNewText = (char *) err_malloc (j + 1);
		j = WideCharToMultiByte (CP_ACP, 0L, lpszText, -1, lpszNewText, j + 1, NULL, NULL);
		if (j > 0)
			strcpy ((char *) lpszText, lpszNewText);
		else
			strcpy ((char *) lpszText, "");
		free (lpszNewText);
	}
}

