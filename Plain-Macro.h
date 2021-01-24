#ifndef PLAIN_ENGINE_PLAIN_MACRO_H
#define PLAIN_ENGINE_PLAIN_MACRO_H

#include <cstdlib>
#include <stdio.h>
#include <stdarg.h>
//#include <string>
//#include <vector>

namespace PLADebug
{
  static const char *kLogFormat = "[%s]%s/%s(%3d) : %s\n";
  static const int kLogBuffer = 1024;

  static void Print(const char *format, ...)
  {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
  }

  static void Trace(const char *file, const char *func, const int line,
                    const char *format, ...)
  {
    char log[kLogBuffer];
    snprintf(log, kLogBuffer, kLogFormat, "TRACE", file, func, line, format);
    va_list args;
    va_start(args, format);
    vfprintf(stderr, log, args);
    va_end(args);
  }

  static void Assert(const char *file, const char *func, const int line,
                     const char *format, ...)
  {
    char log[kLogBuffer];
    snprintf(log, kLogBuffer, kLogFormat, "ASSERT", file, func, line, format);
    va_list args;
    va_start(args, format);
    vfprintf(stderr, log, args);
    va_end(args);
    exit(1);
  }
}

#define PLA_DELETE(aPtr)\
{\
    delete (aPtr); (aPtr) = 0;\
}\

#define PLA_DELETE_ARRAY(aPtr)\
{\
    delete[] (aPtr); (aPtr) = 0;\
}\

#define PLA_PRINT(...)\
PLADebug::Print(__VA_ARGS__)\

#define PLA_TRACE(...)\
PLADebug::Trace(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

#define PLA_ASSERT(...)\
PLADebug::Assert(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)\

#define PLA_DISALLOW_COPY_AND_ASSIGN(aTypeName)\
aTypeName(const aTypeName&);\
void operator=(const aTypeName&)\

#endif // PLAIN_ENGINE_PLAIN_MACRO_H
