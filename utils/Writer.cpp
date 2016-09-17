//[]------------------------------------------------------------------------[]
//|                                                                          |
//|                        GVSG Foundation Classes                           |
//|                               Version 1.0                                |
//|                                                                          |
//|              Copyright® 2010-2013, Paulo Aristarco Pagliosa              |
//|              All Rights Reserved.                                        |
//|                                                                          |
//[]------------------------------------------------------------------------[]
//
//  OVERVIEW: Writer.cpp
//  ========
//  Source file for print writer.

#include <stdlib.h>

#ifndef __Writer_h
#include "Writer.h"
#endif

#define MB_LENGTH 1024


//////////////////////////////////////////////////////////
//
// Writer implementation
// ======
void
Writer::write(const wchar_t* fmt, ...)
//[]----------------------------------------------------[]
//|  Write                                               |
//[]----------------------------------------------------[]
{
  va_list args;
  char mbfmt[MB_LENGTH];

  wcstombs(mbfmt, fmt, MB_LENGTH - 1);
  va_start(args, fmt);
  vfprintf(out, mbfmt, args);
}
