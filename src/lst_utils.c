#include "ft_ping.h"

t_ping* data_new(char* domain)
{
  t_ping* tmp = malloc(sizeof(t_ping));
  if (tmp == NULL)
  {
    fprintf(stderr, "tmp malloc error\n");
    return NULL;
  }  
  memset(tmp, 0, sizeof(t_ping));
  tmp->domain = domain;
  return tmp;
}
