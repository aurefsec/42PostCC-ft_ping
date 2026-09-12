#include "ft_ping.h"

void  set_values(t_ping* data, char* buffer, fd_set* readfds, struct timeval* timeout)
{
  memset(buffer, 0, BUFFER_SIZE);
  FD_ZERO(readfds);
  FD_SET(data->fd_socket, readfds);
  timeout->tv_sec = 1;
  timeout->tv_usec = 0;
}

int icmp_loop(t_option* opt, t_ping* data, t_icmp* packet, t_statistics* stats)
{
  int ret = -1;
  char buffer[1024];
  struct timeval timeout;
  struct sockaddr_in sender;
  socklen_t sender_len = sizeof(struct sockaddr_in);
  fd_set readfds;
  stats->transmitted += 1;

  for (int i = 0; 1; i++)
  {
    set_values(data, buffer, &readfds, &timeout);
    if (sendto(data->fd_socket, packet, sizeof(t_icmp), 0, (struct sockaddr*)&data->s_dst_ipv4, sizeof(struct sockaddr_in)) == -1)
      return ERROR_SENDTO;
    if (!g_sigint)
      break;
    if (i > 0)
      stats->transmitted += 1;
    ret = select(data->fd_socket + 1, &readfds, NULL, NULL, &timeout);
    if (ret == -1)
    {
      if (errno == EINTR) // Check sigint
        break;
      return ERROR_SELECT;
    }
    else if (ret > 0)
    {
      data->recvfrom_ret = recvfrom(data->fd_socket, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&sender, &sender_len);
      if (data->recvfrom_ret == -1)
        return ERROR_RECVFROM;
      else
        data->recvfrom_ret -= 20;
      data->src_ipv4 = inet_ntoa(sender.sin_addr);
      ret = check_sender_packet(opt, data, packet, stats, buffer);
    } 
    if ((i + 1) == opt->count)
      break;
    else
      sleep(1);
    if (create_update_packet(packet, UPDATE_PACKET) > 0)
      return ERROR_GETTIMEOFDAY;
  }
  printf("coucou ret = %d\n", ret);
  return ret;
}
