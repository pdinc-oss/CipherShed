#include "_strupr.h"

#ifndef _MSC_VER
#include <ctype.h>
char *_strupr(char *str)
{
  while(*str)
  { 
    *str = toupper(*str); 
    str++; 
  } 
  return str; 
}
#else
#include <string.h>
#endif
