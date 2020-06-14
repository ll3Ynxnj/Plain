#ifndef PLAIN_PLADEBUG_HPP
#define PLAIN_PLADEBUG_HPP

#include <stdio.h>
#include <stdarg.h>

namespace PLADebug
{
  static void PrintLog(const char *level, const char *file, const int line,
                       const char *format, ...)
  {
    va_list argp;
    fprintf(stderr, "[%s]%s(%4d): ", level, file, line);
    va_start(argp, format);
    vfprintf(stderr, format, argp);
    va_end(argp);
    fprintf(stderr, "\n");
  }

  static void PrintStr(const char *format, ...)
  {
    va_list argp;
    va_start(argp, format);
    vfprintf(stderr, format, argp);
    va_end(argp);
  }
}

#endif // PLAIN_PLADEBUG_HPP
