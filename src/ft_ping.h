#ifndef FT_PING_H
#define FT_PING_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <math.h>
#include <errno.h>

extern int g_sigint;

#define TTL_VALUE 1
#define BUFFER_SIZE 1024

#define ERROR_ADDRINFO 1
#define ERROR_AI_ADDR 2
#define ERROR_INET_NTOA 3
#define ERROR_SOCKET 4
#define ERROR_SETSOCKOPT 5
#define ERROR_GETTIMEOFDAY 6
#define ERROR_SENDTO 7
#define ERROR_SELECT 8
#define ERROR_RECVFROM 9

typedef struct s_ping
{
  char* domain;
  char* ipv4;
  struct sockaddr_in s_ipv4;
  int verbose;
  int query;
  int fd_socket;
} t_ping;

// Represents an ICMP packet, size : 64 bytes
typedef struct s_icmp
{
  uint8_t type;
  uint8_t code;
  uint16_t checksum;
  uint16_t identifier;
  uint16_t sequence;
  uint8_t data[56];
} t_icmp;

typedef struct s_statistics
{
  int transmitted;
  int received;
  int percentage;
  double min;
  double max;
  double sum;
  double sum_sq;
  double avg;
  double stddev;
} t_statistics;

int parsing(int argc, char** argv, t_ping* data);
int get_ipv4(t_ping* data);
int set_socket(t_ping* data);
int create_update_packet(t_icmp* packet, int action);
int check_sender_packet(t_ping* data, t_statistics* stats, char* buffer, struct sockaddr_in* sender);
int icmp_loop(t_ping* data, t_icmp* packet, t_statistics* stats);
void update_statistics(t_statistics* stats, double rtt);
void final_statistics(t_statistics* stats);
void print_before_loop(t_ping* data, t_icmp* packet);
void print_in_loop(t_ping* data, t_icmp* response, uint8_t ttl, double rtt);
void print_after_loop(t_ping* data, t_statistics* stats);
int print_error(int nb);

#endif
