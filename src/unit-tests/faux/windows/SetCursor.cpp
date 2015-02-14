#include "SetCursor.h"

#include "NULL.h"
#include "LoadCursorMock.h"



HCURSOR currentCursor=NULL;

HCURSOR SetCursor(HCURSOR hCursor)
{
	if (hCursor==currentCursor) return currentCursor;
	HCURSOR old=currentCursor;

	if (loadedCursors.count(hCursor)==0)
	{
		throw "cursor not loaded";
	}
	else
	{
		currentCursor=hCursor;
		return old;
	}

}
