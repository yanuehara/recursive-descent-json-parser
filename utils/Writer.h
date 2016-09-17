#ifndef __Writer_h
#define __Writer_h

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
//  OVERVIEW: Writer.h
//  ========
//  Class definition for print writer.

#include <stdarg.h>
#include <stdio.h>
#ifndef WIN32
#include <wchar.h>
#endif


//////////////////////////////////////////////////////////
//
// Writer: print writer class
// ======
class Writer
{
public:
  // Constructors
  Writer()
  {
    out = stdout;
    level = 0;
  }

  Writer(const char* fileName)
  {
    out = fopen(fileName, "w");
    level = 0;
  }

  // Destructor
  ~Writer()
  {
    fclose(out);
  }

  void write(int c)
  {
    fputc(c, out);
  }

  void write(const wchar_t*, ...);

  void beginBlock()
  {
    writeTabs();
    fprintf(out, "{\n");
    level++;
  }

  void endBlock()
  {
    level--;
    writeTabs();
    fprintf(out, "}\n");
  }

  void backspace()
  {
    level--;
  }

  void tab()
  {
    level++;
  }

  void beginLine()
  {
    writeTabs();
  }

  void endLine()
  {
    fputc('\n', out);
  }

private:
  void writeTabs()
  {
    if (level == 0)
      return;
    for (int i = 0; i < level; i++)
      fprintf(out, "  ");
  }

  FILE* out;
  int level;

}; // Writer

#endif // __Writer_h
