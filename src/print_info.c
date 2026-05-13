#include "ft_ping.h"

void  print_before_loop(t_ping* data, t_icmp_header* packet)
{
  if (data->verbose == 0)
    printf("PING %s (%s): 56 data bytes\n", data->domain, data->ipv4);
  else
    printf("PING %s (%s): 56 data bytes, id 0x%04x = %d\n", data->domain, data->ipv4, packet->identifier, packet->identifier);
}

void  print_in_loop(void)
{

}

void  print_after_loop(t_ping *data)
{

}
