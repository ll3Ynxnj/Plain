#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include "PLADebug.hpp"

void PLADebug::PrintLog(const char *aLevel, const char *format, ...)
{
  va_list argp;
  fprintf(stderr, "[%s]%s(%4d): ", aLevel, __FILE__, __LINE__);
  va_start(argp, format);
  vfprintf(stderr, format, argp);
  va_end(argp);
  fprintf(stderr, "\n");
}

void PLADebug::PrintStr(const char *aFormat, ...)
{
  va_list argp;
  va_start(argp, aFormat);
  vfprintf(stderr, aFormat, argp);
  va_end(argp);
}

void PLADebug::Assert(const char *aFormat, ...)
{
  PrintLog("ASSERT", aFormat);
  exit(1);
}
