#include "ft_ping.h"

int print_error(int nb)
{
  switch (nb)
  {
    case ERROR_AI_ADDR;
      fprintf(stderr, "ft_ping: error result->ai_adrr = NULL\n");
      break ;
    case ERROR_INET_NTOA;
      fprintf(stderr, "ft_ping: error inet_ntoa = NULL\n");
      break ;
    case ERROR_SOCKET;
      fprintf (stderr, "ft_ping: Lacking privilege for icmp socket.\n");
      fprintf (stderr, "ft_ping: %s\n", strerror (errno));
      break ;
    case ERROR_SETSOCKOPT;
      fprintf(stderr, "ft_ping: setsockopt : %s\n", strerror(errno));
      break ;
    case ERROR_GETTIMEOFDAY;
      fprintf(stderr, "ft_ping: error gettimeofday : %s\n", strerror(errno));
      break ;
    case ERROR_SENDTO;
      fprintf(stderr, "ft_ping: error sentdo : %s\n", strerror(errno));
      break ;
    case ERROR_SELECT;
      fprintf(stderr, "ft_ping: error select : %s\n", strerror(errno));
      break ;
    case ERROR_RECVFROM;
      fprintf(stderr, "ft_ping: error recvfrom : %s\n", strerror(errno));
      break ;
  }
  return 1;
}
