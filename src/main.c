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
  t_option opt;
  t_ping* data = NULL;

  memset(&opt, 0, sizeof(opt));
  opt.count = -1;
  opt.ttl = DEFAULT_TTL_VALUE;

  signal(SIGINT, handler);
  if (parsing(argc, argv, &opt, &data) > 0)
    return data_clear_all(&data), 1;
  while (data)
  {
    t_icmp packet;
    t_statistics stats; 
  
    memset(&packet, 0, sizeof(packet));
    memset(&stats, 0, sizeof(stats));
        
    if ((ret = get_ipv4(data)) > 0)
      return data_clear_all(&data), print_error(ret);
    if ((ret = set_socket(&opt, data)) > 0)
      return data_clear_all(&data), print_error(ret);
    if ((ret = create_update_packet(&packet, CREATE_PACKET) > 0))
      return data_clear_all(&data), print_error(ret);
    print_before_loop(&opt, data, &packet);
    if ((ret = icmp_loop(&opt, data, &packet, &stats)) > 0)
      return data_clear_all(&data), print_error(ret);
    final_statistics(&stats);
    print_after_loop(data, &stats, ret);

    data = data_clear_node(&data);
  } 
    return 0;
}
