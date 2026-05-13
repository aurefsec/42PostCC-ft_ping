#include "ft_ping.h"

int create_packet(t_icmp_header* packet)
{
  packet.type = ICMP_ECHO; // Type value : 8, type return : 0 (ICMP_ECHOREPLY).
  packet.code = 0;
  packet.identifier = (uint16_t)getpid();
  packet.sequencer = 1; // Index for router jumps.

  // Copy actual time in data of icmp packet.
  struct timeval  time;
  memset(&time, 0, sizeof(time));
  if (gettimeofday(&time, NULL) == -1)
    return ERROR_GETTIMEOFDAY;
  memcpy(packet.data, &time, sizeof(time));

  // Checksum calcul.
  uint32_t  sum = 0; // uint32_t to add each word of packet + carry.
  uint16_t* word = (uint16_t*)packet; // Each word = 2 bytes.
  for (int i = 0; i < 32; i++)
    sum += word[i];
  packet.checksum = (sum >> 16) + (uint16_t)sum; // Get last 16 bytes and add to first 16 bytes (Carry).
  packet.checksum = ~packet.checksum; // ~ to reverse all bits.

  return 0;
}

int check_sender_packet(t_ping* data, char* buffer, struct sockadrr_in* sender)
{
  int ttl_exceeded = 0;
  t_icmp_header*  response = (t_icmp_header*)(buffer + 20) // Jump 20 first bytes header.

  if (response->identifier != (uint16_t)getpid())
    return -1;
  if (response->type == ICMP_ECHOREPLY)
  {
    //Calcul RTT.
  }
  else if (response->type == ICMP_TIME_EXCEEDED)
    ttl_exceeded = 1;

  char* ipv4 = inet_ntoa(sender->sin_addr);
  if (!ipv4)
    ipv4 = "Error struct sockadrr_in* sender";

  // Call print_in_loop() with good parameters.
}
