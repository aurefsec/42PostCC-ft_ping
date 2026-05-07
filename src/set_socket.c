#include "ft_ping.h"

int set_socket(t_ping* data)
{
  // Socket init.
  data->fd_socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
  if (data->fd_socket == -1)
    return ERROR_SOCKET;

  // Socket option setting.
  int  ttl = 64; // TTL : Router jumps, linux convention : 64.

  if (setsockopt(data->fd_socket, IPPROTO_IP, IP_TTL, &ttl, sizeof(int)) == -1) // Set TTL option
    return ERROR_SETSOCKOPT;
  return 1;
}
