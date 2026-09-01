#include "ft_ping.h"

void  set_values(t_ping* data, char* buffer, fd_set* readfds, struct timeval* timeout)
{
  memset(buffer, 0, BUFFER_SIZE);
  FD_ZERO(readfds);
  FD_SET(data->fd_socket, readfds);
  timeout->tv_sec = 1;
  timeout->tv_usec = 0;
}

int icmp_loop(t_ping* data, t_icmp* packet, t_statistics* stats)
{
  int ret = 0;
  char buffer[1024];
  struct timeval timeout;
  struct sockaddr_in sender;
  socklen_t sender_len = sizeof(struct sockaddr_in);
  fd_set readfds;

  for (int i = 0; g_sigint; i++)
  {
    set_values(data, buffer, &readfds, &timeout);
    if (create_update_packet(packet, i) > 0)
      return ERROR_GETTIMEOFDAY;
    if (sendto(data->fd_socket, packet, sizeof(t_icmp), 0, (struct sockaddr*)&data->s_ipv4, sizeof(struct sockaddr_in)) == -1)
      return ERROR_SENDTO;
    stats->transmitted += 1;
    ret = select(data->fd_socket + 1, &readfds, NULL, NULL, &timeout);
    printf("ret = %d\n", ret);
    if (ret == -1)
      return ERROR_SELECT;
    else if (ret > 0)
    {
      if (recvfrom(data->fd_socket, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&sender, &sender_len) == -1)
        return ERROR_RECVFROM;
      check_sender_packet(data, stats, buffer, &sender);
    }
    sleep(1); 
  }
  
  return 0;
}
