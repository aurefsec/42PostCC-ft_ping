#include "ft_ping.h"

int set_socket(t_ping* data)
{
  // Socket init.
  data->fd_socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
  if (data->fd_socket == -1)
  {
    fprintf(stderr, "error socket : %s\n", strerror(errno)); // NEED TO CHECK THE REAL ERROR !
    return 0;
  }

  // Socket option setting.
  int  ttl = 64; // TTL : Router jumps, linux convention : 64.

  if (setsockopt(data->fd_socket, IPPROTO_IP, IP_TTL, &ttl, sizeof(int)) == -1) // Set TTL option
  {
    fprintf(stderr, "error setsockopt : %s\n", strerror(errno)); // NEED TO CHECK THE REAL ERROR !
    return 0;
  }
  return 1;
}
