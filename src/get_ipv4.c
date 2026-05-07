#include "ft_ping.h"

int get_ipv4(t_ping* data)
{
  struct addrinfo   hints;
  struct addrinfo*  result;
  memset(&hints, 0, sizeof(hints));

  // Setup hints and call getaddrinfo() to get domain informations.
  hints.ai_family = AF_INET;  // AF_INET to retrieve IPv4.
  hints.ai_socktype = SOCK_RAW; // SOCK_RAW to filter and retrieve only info needed.
  int nb = getaddrinfo(data->domain, NULL, &hints, &result);
  if (nb != 0)
  {
    fprintf(stderr, "ft_ping: error getaddrinfo: %s\n", gai_strerror(nb));
    return -1;
  }
  if (!result->ai_addr)
  {
    freeaddrinfo(result);
    return ERROR_AI_ADDR;
  }

  // Cast ai_addr to retrieve specifically IPv4 informations and copy it in data struct.
  memcpy(&data->s_ipv4, (struct sockaddr_in*)result->ai_addr, sizeof(struct sockaddr_in));

  // Call inet_ntoa() to retrieve the IPv4 address in char* format.
  data->ipv4 = inet_ntoa(data->s_ipv4.sin_addr);
  if (!data->ipv4)
  {
    freeaddrinfo(result);
    return ERROR_INET_NTOA;
  }
  freeaddrinfo(result);

  return 0;
}
