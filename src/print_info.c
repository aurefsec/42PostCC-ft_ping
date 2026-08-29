#include "ft_ping.h"

void  print_before_loop(t_ping* data, t_icmp* packet)
{
  if (data->verbose == false)
    printf("PING %s (%s): 56 data bytes\n", data->domain, data->ipv4);
  else
    printf("PING %s (%s): 56 data bytes, id 0x%04x = %d\n", data->domain, data->ipv4, packet->identifier, packet->identifier);
}

void  print_in_loop(t_icmp* response, uint8_t ttl, double rtt, int verbose)
{
  if (response-> type == ICMP_TIME_EXCEEDED)
  {
    if (data->verbose == false)
      printf("36 bytes from (%s): Time to live exceeded\n", response->ipv4);
    // Else print the correct error
  }
  else if (response->type != ICMP_ECHOREPLY)
  {
    if (data->verbose == true)
      printf("unknown response from (%s)\n", data->ipv4);
  }
  else
    printf("64 bytes from (%s): icmp_seq=%d ttl=%d time=%d ms\n", response->ipv4, response->sequence, ttl, rtt);
}

void  print_after_loop(t_ping *data, t_statistics* stats)
{
  printf("--- %s ping statistics ---\n", data->domain);
}
