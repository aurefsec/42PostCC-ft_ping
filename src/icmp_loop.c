#include "ft_ping.h"

int icmp_loop(t_ping* data, t_icmp* packet, t_statistics* stats)
{
  int ret = 0;
  char buffer[1024];
  struct timeval timeout;
  struct sockaddr_in sender;
  socklen_t sender_len = sizeof(struct sockaddr_in);
  fd_set readfds;

  print_before_loop(data, packet);
  while (g_sigint)
  {
    memset(buffer, 0, sizeof(buffer));
    FD_ZERO(&readfds);
    FD_SET(data->fd_socket, &readfds);
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    if (sendto(data->fd_socket, packet, sizeof(t_icmp), 0, (struct sockaddr*)&data->s_ipv4, sizeof(struct sockaddr_in)) == -1)
      return ERROR_SENDTO;

    ret = select(data->fd_socket + 1, &readfds, NULL, NULL, &timeout);
    if (ret == -1)
      return ERROR_SELECT;
    else if (ret > 0)
    {
      stats->transmitted += 1;
      if (recvfrom(data->fd_socket, buffer, sizeof(buffer), 0, (struct sockaddr*)&sender, &sender_len) == -1)
        return ERROR_RECVFROM;
      if (check_sender_packet(data, packet, stats, buffer, &sender) == -1)
        continue; // Restart loop if incorrect pid.
    }
    if (create_update_packet(packet, UPDATE_PACKET) > 0)
      return ERROR_GETTIMEOFDAY;
  }
  final_statistics(stats);
  print_after_loop(data, stats);
  
  return 0;
}
