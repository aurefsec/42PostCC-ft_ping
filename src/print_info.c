#include "ft_ping.h"

void  print_before_loop(t_ping* data, t_icmp* packet)
{
  if (data->verbose == false)
    printf("PING %s (%s): 56 data bytes\n", data->domain, data->ipv4);
  else
    printf("PING %s (%s): 56 data bytes, id 0x%04x = %d\n", data->domain, data->ipv4, packet->identifier, packet->identifier);
}

void  print_in_loop(t_ping* data, t_icmp* response, t_ip_header* ip_h, uint8_t ttl, double rtt)
{
  if (response->type == ICMP_TIME_EXCEEDED)
  {
    printf("36 bytes from _gateway (%s): Time to live exceeded\n", data->ipv4);
    if (data->verbose == true)
    {
      uint16_t words;

      printf("IP Hdr Dump:\n");
      for (int i = 0; i < 10; i++)
      {
        words = *((uint16_t*)ip_h + (i * 2));
        printf("%04x ", words);
      }
      printf("\n");
      printf("VR HL TOS  Len   ID Flg  off TTL Pro  cks      Src      Dst     Data\n");
      printf(" %d  %d  %02x %04x %04x   %d %02x  %d  %d %04x %s  %s\n", 
             ip_h->vr_hl >> 4, ip_h->vr_hl & 0x0F, ip_h->tos, ip_h->len, ip_h->id,
             ip_h->flg_off >> 3, ip_h->flg_off & 0x1FFF, ip_h->ttl, ip_h->pro, ip_h->cks,
             inet_ntoa(*(struct in_addr*)&ip_h->src), inet_ntoa(*(struct in_addr*)&ip_h->dst));
      printf("ICMP: type %d, code %d, size 64, id %04x, seq %04x\n", response->type, response->code,
             response->identifier, response->sequence);
    }
  }
  else if (response->type != ICMP_ECHOREPLY)
  {
    printf("unknown response from (%s)\n", data->ipv4);
  }
  else if (response->identifier != (uint16_t)getpid())
    return ;
  else
    printf("64 bytes from (%s): icmp_seq=%d ttl=%d time=%.3f ms\n", data->ipv4, response->sequence, ttl, rtt);
}

void  print_after_loop(t_ping *data, t_statistics* stats, int ret)
{
  printf("--- %s ping statistics ---\n", data->domain);
  printf("%d packet transmitted, %d packet received, %d%% packet loss\n", stats->transmitted, stats->received, stats->percentage);
  if (ret == 0)
    printf("round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n", stats->min, stats->avg, stats->max, stats->stddev);
}
