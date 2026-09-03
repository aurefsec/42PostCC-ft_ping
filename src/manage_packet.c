#include "ft_ping.h"

int create_update_packet(t_icmp* packet, int action)
{
  if (action == CREATE_PACKET)
  {
    packet->type = ICMP_ECHO; // Type value : 8, type return : 0 (ICMP_ECHOREPLY)
    packet->code = 0;
    packet->identifier = (uint16_t)getpid();
    packet->sequence = 0; // Index for router jumps
  }
  else if (action == UPDATE_PACKET)
  {
    packet->checksum = 0;
    memset(packet->data, 0, sizeof(packet->data));
    packet->sequence += 1;
  }

  // Copy actual time in data of icmp packet
  struct timeval  time;
  memset(&time, 0, sizeof(time));
  if (gettimeofday(&time, NULL) == -1)
    return ERROR_GETTIMEOFDAY;
  memcpy(packet->data, &time, sizeof(time));

  // Checksum calcul.
  uint32_t  sum = 0; // uint32_t to add each word of packet + carry
  uint16_t* word = (uint16_t*)packet; // Each word = 2 bytes
  for (int i = 0; i < 32; i++)
    sum += word[i];
  packet->checksum = (sum >> 16) + (uint16_t)sum; // Get last 16 bytes and add to first 16 bytes (Carry)
  packet->checksum = ~packet->checksum; // ~ to reverse all bits

  return 0;
}

int check_sender_packet(t_ping* data, t_icmp* packet, t_statistics* stats, char* buffer)
{
  int ret = 0;
  struct timeval sender_time;
  struct timeval now_time;
  memset(&sender_time, 0, sizeof(sender_time));
  memset(&now_time, 0, sizeof(now_time));
  gettimeofday(&now_time, NULL);
  t_icmp*  response = (t_icmp*)(buffer + 20); // Jump 20 first bytes header
  t_ip_header *ip_h = (t_ip_header*)(buffer + 28); // Jump 28 first bytes header
  data->ttl_remain = buffer[8];
  data->rtt = -1;

  if (response->type == ICMP_ECHOREPLY)
  {
    memcpy(&sender_time, response->data, sizeof(struct timeval));
    data->rtt = (now_time.tv_sec - sender_time.tv_sec) * 1000.0 + (now_time.tv_usec - sender_time.tv_usec) / 1000.0;
    update_statistics(stats, data->rtt);
  }
  else if (response->type == ICMP_TIME_EXCEEDED)
    ret = -1;

  print_in_loop(data, packet, response, ip_h);
  return ret;
}
