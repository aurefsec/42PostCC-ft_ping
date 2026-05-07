# include "ft_ping.h"

int main(int argc, char** argv)
{
  t_ping          data;
  t_icmp_header   packet;

  memset(&data, 0, sizeof(data));
  memset(&packet, 0, sizeof(packet));

  int ret = 0;

  if (parsing(argc, argv, &data) > 0)
    return 1;
  if ((ret = get_ipv4(&data)) > 0)
    return print_error(ret);
  if ((ret = set_socket(&data)) > 0)
    return print_error(ret);
  printf("data :\ndomain = %s\nipv4 = %s\nverbose = %d\nquery = %d\nfd_socket = %d\n", data.domain, data.ipv4, data.verbose, data.query, data.fd_socket);
  if ((ret = create_packet(&packet)) > 0)
    return print_error(ret);
  if ((ret = icmp_loop(&data, &packet)) > 0)
    return print_error(ret);

  return 0;
}
