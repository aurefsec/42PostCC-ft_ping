#ifndef FT_PING_H
#define FT_PING_H

#include <stdio.h>
#include <string.h>

typedef struct s_ping
{
  char* domain;
  int   verbose;
  int   query;
} t_ping;

int setup_data(int argc, char** argv, t_ping* data);

#endif
