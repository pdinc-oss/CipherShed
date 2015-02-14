#ifndef _CS_Common_util_unicode_strlenw_h_
#define _CS_Common_util_unicode_strlenw_h_

#ifdef _MSC_VER
__inline
#else
inline
#endif
int strlenw(WCHAR* s)
{
	int len=0;
	if (!s) return 0;
	while (*s++) ++len;
	return len;
}


#endif
