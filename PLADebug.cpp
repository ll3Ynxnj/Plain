#include "PLADebug.hpp"
void PLADebug::PrintStr(const char *aFormat, ...)
{
  va_list argp;
  va_start(argp, aFormat);
  vfprintf(stderr, aFormat, argp);
  va_end(argp);
}

void PLADebug::PrintLog(const char *aLevel, const char *aFormat, ...)
{
  fprintf(stderr, "[%s]%s(%4d): ", aLevel, __FILE__, __LINE__);
  va_list argp;
  va_start(argp, aFormat);
  vfprintf(stderr, aFormat, argp);
  va_end(argp);
  fprintf(stderr, "\n");
}

void PLADebug::Assert(const char *aFormat, ...)
{
  PrintLog("ASSERT", aFormat);
  exit(1);
}
