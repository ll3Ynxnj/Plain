#ifndef PLAIN_PLADEBUG_HPP
#define PLAIN_PLADEBUG_HPP

#include <stdio.h>
#include <stdarg.h>
#include <string>
#include <vector>

namespace PLADebug
{
  template <typename ... Args>
  std::string Format(const std::string& fmt, Args ... args )
  {
    size_t len = std::snprintf( nullptr, 0, fmt.c_str(), args ... );
    std::vector<char> buf(len + 1);
    std::snprintf(&buf[0], len + 1, fmt.c_str(), args ... );
    return std::string(&buf[0], &buf[0] + len);
  }

  static void Print(const char *format, ...)
  {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
  }

  static void Assert(const char *file, const int line, const char *format, ...)
  {
    std::string log = Format("[%s]%s(%d) : %s\n", "ASSERT", file, line, format);
    va_list args;
    va_start(args, format);
    fprintf(stderr, log.c_str(), args);
    va_end(args);
    exit(1);
  }
}

#endif // PLAIN_PLADEBUG_HPP
