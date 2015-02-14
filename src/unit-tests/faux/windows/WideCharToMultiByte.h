#ifndef _CS_unittesting_faux_windows_WideCharToMultiByte_h_
#define _CS_unittesting_faux_windows_WideCharToMultiByte_h_

#include "UINT.h"
#include "DWORD.h"
#include "LPCWSTR.h"
#include "LPSTR.h"
#include "LPCSTR.h"
#include "LPBOOL.h"

int WideCharToMultiByte(UINT CodePage, DWORD dwFlags, LPCWSTR lpWideCharStr, int cchWideChar, LPSTR lpMultiByteStr, int cbMultiByte, LPCSTR lpDefaultChar, LPBOOL lpUsedDefaultChar);

#endif