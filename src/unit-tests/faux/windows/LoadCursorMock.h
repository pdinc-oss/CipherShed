#ifndef _CS_unittesting_faux_windows_LoadCursor_mock_h_
#define _CS_unittesting_faux_windows_LoadCursor_mock_h_

#include "LoadCursor.h"

int getAPIFailMode();
void setAPIFailMode(int mode);

#include <string>
#include <map>

struct FauxLoadCursorTableEntry
{
	char utf8CursorName[512];
};

extern std::map<HCURSOR,FauxLoadCursorTableEntry> loadedCursors;
extern std::map<std::string,HCURSOR> loadedCursorReference;

#endif
