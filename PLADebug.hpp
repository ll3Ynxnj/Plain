#ifndef PLADEBUG_HPP
#define PLADEBUG_HPP

class PLADebug
{
public:
  static void PrintLog(const char *aLevel, const char *aFormat, ...);
  static void PrintStr(const char *aFormat, ...);
  static void Assert(const char *aFormat, ...);
};

#endif
