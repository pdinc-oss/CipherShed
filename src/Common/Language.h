/*
 Copyright (c) 2008 TrueCrypt Developers Association. All rights reserved.

 Governed by the TrueCrypt License 3.0 the full text of which is contained in
 the file License.txt included in TrueCrypt binary and source code distribution
 packages.
*/

#ifndef CS_UNITTESTING
#include <windows.h>
#else
#include "../unit-tests/faux/windows/HWND.h"
#include "../unit-tests/faux/windows/UINT.h"
#include "../unit-tests/faux/windows/WPARAM.h"
#include "../unit-tests/faux/windows/LPARAM.h"
#include "../unit-tests/faux/windows/BOOL.h"
#include "../unit-tests/faux/windows/CALLBACK.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define UNKNOWN_STRING_ID L"[?]"

extern BOOL LocalizationActive;
extern int LocalizationSerialNo;
extern wchar_t UnknownString[1024];

typedef struct
{
	wchar_t *FaceName;
	int Size;
} Font;

BOOL CALLBACK LanguageDlgProc (HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam);
wchar_t *GetString (const char *stringId);
Font *GetFont (char *fontType);
BOOL LoadLanguageFile ();
char *GetPreferredLangId ();
void SetPreferredLangId (char *langId);
char *GetActiveLangPackVersion ();

#ifdef __cplusplus
}
#endif
