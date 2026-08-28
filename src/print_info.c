#include "ft_ping.h"

void  print_before_loop(t_ping* data, t_icmp_header* packet)
{
  if (data->verbose == 0)
    printf("PING %s (%s): 56 data bytes\n", data->domain, data->ipv4);
  else
    printf("PING %s (%s): 56 data bytes, id 0x%04x = %d\n", data->domain, data->ipv4, packet->identifier, packet->identifier);
}

void  print_in_loop(t_icmp_header* response, uint8_t ttl, double rtt, int verbose)
{
  if (response-> type == ICMP_TIME_EXCEEDED)
  {
    // Print the good error
  }
  else if (response->type != ICMP_ECHOREPLY)
  {
    // Print the good error
  }
  else
    printf("64 bytes from %s: icmp_seq=%d ttl=%d time=%d ms", response->ipv4, response->sequence, ttl, rtt);
}

void  print_after_loop(t_ping *data)
{

}
