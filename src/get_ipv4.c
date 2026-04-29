#include "ft_ping.h"

int get_ipv4(t_ping* data)
{
  struct addrinfo   hints;
  struct addrinfo*  result;
  memset(&hints, 0, sizeof(hints));
  memset(&result, 0, sizeof(result));

  // Setup hints and call getaddrinfo() to get domain informations.
  hints.ai_family = AF_INET;  // AF_INET to retrieve IPv4.
  hints.ai_socktype = SOCK_RAW; // SOCK_RAW to filter and retrieve only info needed.
  int nb = getaddrinfo(data->domain, NULL, &hints, &result);
  if (nb != 0)
  {
    fprintf(stderr, "error getaddrinfo: %s\n", gai_strerror(nb));
    return 0;
  }

  // Cast ai_addr to retrieve specifically IPv4 informations.
  struct sockaddr_in*  addr = (struct sockaddr_in*)result->ai_addr;
  if (!addr)
  {
    fprintf(stderr, "error sockadrr_in = NULL\n");
    freeaddrinfo(result);
    return 0;
  }

  // Call inet_ntoa() to retrieve the IPv4 address in char* format.
  data->ipv4 = inet_ntoa(addr->sin_addr);
  if (!data->ipv4)
  {
    fprintf(stderr, "error inet_ntoa = NULL\n");
    freeaddrinfo(result);
    return 0;
  }
  freeaddrinfo(result);
  return 1;
}
