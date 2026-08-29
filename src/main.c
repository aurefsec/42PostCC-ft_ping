# include "ft_ping.h"

void  handler(void)
{
  g_sigint = 0;
}

int main(int argc, char** argv)
{
  int ret = 0;
  t_ping  data;
  t_icmp  packet;
  t_statistics  stats; 

  memset(&data, 0, sizeof(data));
  memset(&packet, 0, sizeof(packet));
  memset(&stats, 0, sizeof(stats));

  signal(SIGINT, handler);

  if (parsing(argc, argv, &data) > 0)
    return 1;
  if ((ret = get_ipv4(&data)) > 0)
    return print_error(ret);
  if ((ret = set_socket(&data)) > 0)
    return print_error(ret);
  printf("data :\ndomain = %s\nipv4 = %s\nverbose = %d\nquery = %d\nfd_socket = %d\n", data.domain, data.ipv4, data.verbose, data.query, data.fd_socket);
  if ((ret = create_update_packet(&packet, CREATE_PACKET)) > 0)
    return print_error(ret);
  if ((ret = icmp_loop(&data, &packet, &stats)) > 0)
    return print_error(ret);

  return 0;
}
