#include "ft_ping.h"

int is_valid_count(char* arg, int i)
{
  while (arg[i])
  {
    if (arg[i] < '0' && arg[i] > '9')
      return 1;
    i++;
  } 
  return 0;
}

char* substr(char* src, unsigned int start, size_t len)
{
  size_t i = 0;
  size_t y;
  char *dst;

  if (!src)
    return NULL;
  if (start >= strlen(src))
    y = 0;
  else 
    y = strlen(&src[start]);
  if (y > len)
    y = len;
  dst = malloc(sizeof(char) * (y + 1));
  if (!dst)
    return NULL;
  while (i < y)
  {
    dst[i] = src[start + i];
    i++;
  }
  dst[i] = 0;
  return dst;
}
