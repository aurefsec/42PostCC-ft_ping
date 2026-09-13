#ifndef FT_PING_H
#define FT_PING_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

#define DEFAULT_TTL_VALUE 64
#define BUFFER_SIZE 1024
#define CREATE_PACKET 0
#define UPDATE_PACKET 1

#define ERROR_ADDRINFO 1
#define ERROR_AI_ADDR 2
#define ERROR_INET_NTOA 3
#define ERROR_SOCKET 4
#define ERROR_SETSOCKOPT 5
#define ERROR_GETTIMEOFDAY 6
#define ERROR_SENDTO 7
#define ERROR_SELECT 8
#define ERROR_RECVFROM 9

typedef struct s_option
{
  int verbose;
  long count;
  long ttl;
  long interval;
} t_option;

typedef struct s_ping
{
  char* domain;
  char* src_ipv4;
  char* dst_ipv4;
  struct sockaddr_in s_dst_ipv4;
  int fd_socket;
  int recvfrom_ret;
  double rtt;
  uint8_t ttl_remain;
  struct s_ping* next;
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

// Needs it if TTL Exceeded to retrieve ip header informations
typedef struct s_ip_header
{
  uint8_t vr_hl;    // Version + header length
  uint8_t tos;      // Type of service
  uint16_t len;     // Total length
  uint16_t id;      // identification
  uint16_t flg_off; // flag + fragment offset
  uint8_t ttl;      // Time to leave
  uint8_t pro;      // Protocol
  uint16_t cks;     // Cheksum
  uint32_t src;     // Source address
  uint32_t dst;     // Destination address
} t_ip_header;

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

// parsing.c
int parsing(int argc, char** argv, t_option* opt, t_ping** data);

// manage_arg.c
int count_arg(int argc, char** argv, t_option* opt, int* i, int* y);
int interval_arg(int argc, char** argv, t_option* opt, int* i, int* y);
int ttl_arg(int argc, char** argv, t_option* opt, int *i);

// utils.c
int is_valid_number(char* arg);
char* substr(char* src, unsigned int start, size_t len);

// lst_utils.c
t_ping* data_new(char* domain);
int create_first_data(t_ping** data, t_ping** tmp, char* domain);
int create_node_data(t_ping** tmp, char* domain);
t_ping* data_clear_node(t_ping** data);
t_ping* data_clear_all(t_ping** data);

// get_ipv4.c
int get_ipv4(t_ping* data);

// set_socket.c
int set_socket(t_option* opt, t_ping* data);

// manage_packet.c
int create_update_packet(t_icmp* packet, int action);
int check_sender_packet(t_option* opt, t_ping* data, t_icmp* packet, t_statistics* stats, char* buffer);

// icmp_loop.c
int icmp_loop(t_option* opt, t_ping* data, t_icmp* packet, t_statistics* stats);

// statistics.c
void update_statistics(t_statistics* stats, double rtt);
void final_statistics(t_statistics* stats);

// print_info.c
void print_query(void);
void print_before_loop(t_option* opt, t_ping* data, t_icmp* packet);
void print_in_loop(t_option* opt, t_ping* data, t_icmp* packet, t_icmp* response, t_ip_header* ip_h);
void print_after_loop(t_ping* data, t_statistics* stats, int ret);

// print_error.c
int print_error(int nb);

#endif
