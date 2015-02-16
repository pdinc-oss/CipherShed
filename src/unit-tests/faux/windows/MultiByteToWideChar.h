#ifndef _CS_unit_tests_faux_windows_MultiByteToWideChar_h_
#define _CS_unit_tests_faux_windows_MultiByteToWideChar_h_

#include "UINT.h"
#include "DWORD.h"
#include "LPCSTR.h"
#include "LPWSTR.h"

#ifdef __cplusplus
extern "C" {
#endif

int MultiByteToWideChar(UINT CodePage, DWORD dwFlags, LPCSTR lpMultiByteStr, int cbMultiByte, LPWSTR lpWideCharStr, int cchWideChar);

#ifdef __cplusplus
}
#endif

#endif
