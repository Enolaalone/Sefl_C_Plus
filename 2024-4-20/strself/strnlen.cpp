#include <cstdio>
#include <cstring>


size_t strnlen(const char *str, size_t maxlen)
{
  void *found = memchr(str,(int)'\0',maxlen);
  return found ? (const char*)found - str : maxlen;
}
