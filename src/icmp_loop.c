#include "ft_ping.h"

int  icmp_loop(t_ping* data);
{
  // Create ICMP packet.
  t_icmp_header   packet;
  struct timeval  time;
  memset(&packet, 0, sizeof(packet));
  memset(&time, 0, sizeof(time));

  if (gettimeofday(&time, NULL) == -1)
  {
    fprintf(stderr, "error gettimeofday : %s\n", strerror(errno)); // NEED TO CHECK THE REAL ERROR !
    return 0;
  }

  packet.type = ICMP_ECHO; // Send value : 8, send return : 0 (ICMP_ECHOREPLY).
  packet.code = 0;
  packet.identifier = (uint16_t)getpid();
  packet.sequencer = 1; // Index for router jumps.
  // packet.data = ?
  // packet.checksum = ?

  return 1;
}
