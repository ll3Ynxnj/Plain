#ifndef PLAIN_PLADEBUG_HPP
#define PLAIN_PLADEBUG_HPP

#include <stdio.h>
#include <stdarg.h>
#include <string>
#include <vector>

namespace PLADebug
{
  static const char *kLogFormat = "[%s]%s(%d) : %s\n";
  static const int kLogBuffer = 1024;

  static void Print(const char *format, ...)
  {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
  }

  static void Assert(const char *file, const int line, const char *format, ...)
  {
    char log[kLogBuffer];
    snprintf(log, kLogBuffer, kLogFormat, "ASSERT", file, line, format);
    va_list args;
    va_start(args, format);
    vfprintf(stderr, log, args);
    va_end(args);
    exit(1);
  }
}

#endif // PLAIN_PLADEBUG_HPP
