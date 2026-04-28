# include "ft_ping.h"

int main(int argc, char** argv)
{
  t_ping  data;
  memset(&data, 0, sizeof(t_ping));

  if (!setup_data(argc, argv, &data))
    return 0;
  printf("lets go !\ndata :\ndomain = %s\nverbose = %d\nquery = %d\n", data.domain, data.verbose, data.query);
  return 1;
}
