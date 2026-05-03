# include "ft_ping.h"

int main(int argc, char** argv)
{
  t_ping  data;
  memset(&data, 0, sizeof(data));

  if (!parsing(argc, argv, &data))
    return 0;
  if (!get_ipv4(&data))
    return 0;
  if (!set_socket(&data))
    return 0;
  printf("data :\ndomain = %s\nipv4 = %s\nverbose = %d\nquery = %d\nfd_socket = %d\n", data.domain, data.ipv4, data.verbose, data.query, data.fd_socket);
  if (!icmp_loop(&data))
    return 0;
  return 1;
}
