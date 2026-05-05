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
  {
    fprintf(stderr, "error gettimeofday : %s\n", strerror(errno)); // NEED TO CHECK THE REAL ERROR !
    return 0;
  }
  memcpy(packet.data, &time, sizeof(time));

  // Checksum calcul.
  uint32_t sum = 0; // uint32_t to add each word of packet + carry.
  uint16_t  *word = (uint16_t*)packet; // Each word = 2 bytes.
  for (int i = 0; i < 32; i++)
    sum += word[i];
  packet.checksum = (sum >> 16) + (uint16_t)sum; // Get last 16 bytes and add to first 16 bytes (Carry).
  packet.checksum = ~packet.checksum; // ~ to reverse all bits.

  return 1;
}
