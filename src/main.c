# include "ft_ping.h"

int main(int argc, char** argv)
{
  t_ping  data;
  memset(&data, 0, sizeof(data));

  if (!setup_data(argc, argv, &data))
    return 0;
  if (!get_ipv4(&data))
    return 0;
  printf("data :\ndomain = %s\nipv4 = %s\nverbose = %d\nquery = %d\nfd_socket = %d\n", data.domain, data.ipv4, data.verbose, data.query, data.fd_socket);
  // Create socket fd and setup socket options.
  // Build ICMP packet.
  // Loop send/recept.
  // Print results.
  return 1;
}
