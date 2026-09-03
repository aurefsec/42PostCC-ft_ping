#include "ft_ping.h"

void  print_before_loop(t_ping* data, t_icmp* packet)
{
  if (data->verbose == false)
    printf("PING %s (%s): 56 data bytes\n", data->domain, data->dst_ipv4);
  else
    printf("PING %s (%s): 56 data bytes, id 0x%04x = %d\n", data->domain, data->dst_ipv4, packet->identifier, packet->identifier);
}

void  print_in_loop(t_ping* data, t_icmp* packet, t_icmp* response, t_ip_header* ip_h)
{
  if (response->type == ICMP_TIME_EXCEEDED)
  {
    printf("36 bytes from _gateway (%s): Time to live exceeded\n", data->src_ipv4);
    if (data->verbose == true)
    {
      uint16_t word;
      char src[16];
      char dst[16];
      strcpy(src, inet_ntoa(*(struct in_addr*)&ip_h->src)); // Using strcpy because inet_ntoa uses static buffer
      strcpy(dst, inet_ntoa(*(struct in_addr*)&ip_h->dst));

      // IP Hdr Dunp : Read the 20 bytes of ip_h and write it 2 bytes by 2 bytes
      printf("IP Hdr Dump:\n");
      for (int i = 0; i < 10; i++)
      {
        word = ntohs(*((uint16_t*)ip_h + i)); // Using ntohs to swap from litle-endian to big-endian
        printf(" %04x", word);
      }
      printf("\n");
      printf("Vr HL TOS  Len   ID Flg  off TTL Pro  cks      Src      Dst     Data\n");
      printf(" %d  %d  %02x %04x %04x   %d %04x  %02x  %02x %04x %s  %s\n", 
             ip_h->vr_hl >> 4, ip_h->vr_hl & 0x0F, ip_h->tos, ip_h->len, ip_h->id,
             ip_h->flg_off >> 3, ip_h->flg_off & 0x1FFF, ip_h->ttl, ip_h->pro, ip_h->cks,
             src, dst);
      printf("ICMP: type %d, code %d, size 64, id 0x%04x, seq 0x%04x\n", packet->type, packet->code,
             packet->identifier, packet->sequence);
    }
  }
  else if (response->type != ICMP_ECHOREPLY)
  {
    printf("unknown response from (%s)\n", data->dst_ipv4);
  }
  else if (response->identifier != (uint16_t)getpid())
    return ;
  else
    printf("64 bytes from (%s): icmp_seq=%d ttl=%d time=%.3f ms\n", 
           data->dst_ipv4, response->sequence, data->ttl_remain, data->rtt);
}

void  print_after_loop(t_ping *data, t_statistics* stats, int ret)
{
  printf("--- %s ping statistics ---\n", data->domain);
  printf("%d packets transmitted, %d packets received, %d%% packet loss\n", stats->transmitted, stats->received, stats->percentage);
  if (ret == 0)
    printf("round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n", stats->min, stats->avg, stats->max, stats->stddev);
}
