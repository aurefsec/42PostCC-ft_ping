#include "ft_ping.h"

int icmp_loop(t_ping* data);
{
  int i = 0;
  int ret = 0;
  char  buffer[1024];
  struct sockaddr_in  sender;
  socklen_t sender_len = sizeof(struct sockaddr_in);
  struct timeval  timeout;
  timeout.tv_sec = 1;
  timeout.tv_usec = 0;
  fd_set readfds;
  FD_ZERO(&readfds);
  FD_SET(data->fd_socket, &readfds);

  printf("PING %s (%s): 56 data bytes", data->domain, data->ipv4);
  while (1)
  {
    if (sentdo(data->fd_socket, &packet, sizeof(t_icmp_header), 0, (struct sockaddr*)&data->s_ipv4, sizeof(struct sockaddr_in)) == -1)
    {
      fprintf(stderr, "error sentdo : %s\n", strerror(errno));
      return 0;
    }
    ret = select(data->fd_socket + 1, &readfds, NULL, NULL, &timeout);
    if (ret == -1)
    {
      fprintf(stderr, "error select : %s\n", strerror(errno));
      return 0;
    }
    if (ret > 0)
    {
      if (recvfrom(data->fd_socket, buffer, sizeof(buffer), 0, &sender, &sender_len) == -1)
      {
        fprintf(stderr, "error select : %s\n", strerror(errno));
        return 0;
      }
    }
    if (!update_packet(&packet, i))
      return 0;
  }

  return 1;
}
