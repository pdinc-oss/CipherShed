#include "process.h"

#include "../Tcdefs.h"
#include "../Language.h"
#include "../Dlgcode.h"

#ifdef CS_UNITTESTING
#include "../../unit-tests/faux/windows/MessageBeep.h"
#include "../../unit-tests/faux/windows/MessageBox.h"
#include <stdlib.h>
#endif

void AbortProcess (char *stringId)
{
	// Note that this function also causes localcleanup() to be called (see atexit())
	MessageBeep (MB_ICONEXCLAMATION);
	MessageBoxW (NULL, (LPCWSTR)GetString (stringId), (LPCWSTR)lpszTitle, ICON_HAND);
	exit (1);
}

void AbortProcessSilent (void)
{
	// Note that this function also causes localcleanup() to be called (see atexit())
	exit (1);
}
