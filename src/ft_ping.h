#ifndef FT_PING_H
#define FT_PING_H

#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct s_ping
{
  char* domain;
  char* ipv4;
  int   verbose;
  int   query;
  int   fd_socket;
} t_ping;

int setup_data(int argc, char** argv, t_ping* data);
int get_ipv4(t_ping* data);

#endif
