# include "ft_ping.h"

int g_sigint = 1;

void  handler(int nb)
{
  (void)nb;
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
  print_before_loop(&data, &packet);
  if ((ret = icmp_loop(&data, &packet, &stats)) > 0)
    return print_error(ret);
  final_statistics(&stats);
  print_after_loop(&data, &stats);

  return 0;
}
