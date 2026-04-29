# include "ft_ping.h"

int setup_data(int argc, char** argv, t_ping* data)
{
  // Parsing of argument to get domain and options.
  for (int i = 1; i < argc; i++)
  {
    if (argv[i][0] == '-' && strlen(argv[i]) > 1)
    {
      for (int y = 1; argv[i][y]; y++)
      {
        if (argv[i][y] == 'v')
          data->verbose = 1;
        else if (argv[i][y] == '?')
          data->query = 1;
        else
        {
          printf("ft_ping: invalid option -- '%c'\n", argv[i][y]);
          printf("Try 'ft_ping -?' for more information.\n");
          return 0;
        }
      }
    }
    else if (data->domain == NULL)
      data->domain = argv[i];
  }
  if (data->domain == NULL || argc == 1)
  {
    printf("ft_ping: missing host operand\n");
    printf("Try 'ft_ping -?' for more information.\n");
    return 0;
  }
  return 1;
}
