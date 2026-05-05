#ifndef FT_PING_H
#define FT_PING_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <errno.h>

typedef struct s_ping
{
  char*               domain;
  char*               ipv4;
  struct sockadrr_in  s_ipv4;
  int                 verbose;
  int                 query;
  int                 fd_socket;
} t_ping;

// Represents an ICMP packet, size : 64 bytes.
typedef struct s_icmp_header
{
  uint8_t   type;
  uint8_t   code;
  uint16_t  checksum;
  uint16_t  identifier;
  uint16_t  sequence;
  uint8_t   data[56];
} s_icmp_header;

int parsing(int argc, char** argv, t_ping* data);
int get_ipv4(t_ping* data);
int set_socket(t_ping* data);
int create_packet(t_icmp_header* packet);
int icmp_loop(t_ping* data, t_icmp_header* packet);

#endif
