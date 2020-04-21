#ifndef PLAIN_PLADEBUG_HPP
#define PLAIN_PLADEBUG_HPP

#include <cstdio>
#include <cstdlib>
#include <cstdarg>

namespace PLADebug
{
  void PrintStr(const char *aFormat, ...);
  void PrintLog(const char *aLevel, const char *aFormat, ...);
  void Assert(const char *aFormat, ...);
};

#endif // PLAIN_PLADEBUG_HPP
