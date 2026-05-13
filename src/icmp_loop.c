#include "ft_ping.h"

int icmp_loop(t_ping* data, t_icmp_header* packet)
{
  int   i = 0;
  int   ret = 0;
  char  buffer[1024];
  struct sockaddr_in  sender;
  socklen_t sender_len = sizeof(struct sockaddr_in);
  fd_set readfds;
  struct timeval  timeout;

  print_before_loop(data, packet);
  while (1)
  {
    memset(buffer, 0, sizeof(buffer));
    FD_ZERO(&readfds);
    FD_SET(data->fd_socket, &readfds);
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    if (sentdo(data->fd_socket, packet, sizeof(t_icmp_header), 0, (struct sockaddr*)&data->s_ipv4, sizeof(struct sockaddr_in)) == -1)
      return ERROR_SENDTO;

    ret = select(data->fd_socket + 1, &readfds, NULL, NULL, &timeout);
    if (ret == -1)
      return ERROR_SELECT;
    else if (ret > 0)
    {
      if (recvfrom(data->fd_socket, buffer, sizeof(buffer), 0, &sender, &sender_len) == -1)
        return ERROR_RECVFROM;
      if (check_sender_packet(data, buffer, &sender) == -1)
        continue; // Restart loop if incorrect pid.
    }
    if (!update_packet(&packet, i))
      return ERROR_GETTIMEOFDAY;
  }

  return 0;
}
