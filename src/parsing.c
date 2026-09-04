# include "ft_ping.h"

void verbose_arg(t_ping* data)
{
  data->verbose = 1;
}

void query_arg(t_ping* data)
{
  data->query = 1;
}

int count_arg(t_ping* data, char** argv, int argc, int* i)
{
  if (((*i) + 1) > (argc - 1))
  {
    printf("./ft_ping: option requires an argument -- 'c'\n");
    printf("Try 'ft_ping -?' for more information.\n");
    return 1;
  }
  (*i)++;
  data->count = atoi(argv[*i]);
  if (data->count == 0)
  {
    printf("./ping: invalid value (`%s' near `%s')\n", argv[*i], argv[*i]);
    return 1;
  }
  printf ("count = %d, i = %d\n", data->count, *i);
  return 0;

}

int parsing(int argc, char** argv, t_ping* data)
{
  int i = 1;

  // Parse arguments to get domain and options.
  while (i < argc)
  {
    if (argv[i][0] == '-' && strlen(argv[i]) > 1)
    {
      for (int y = 1; argv[i][y]; y++)
      {
        printf("coucou for\n");
        if (argv[i][y] == 'v')
          verbose_arg(data);
        else if (argv[i][y] == '?')
          query_arg(data);
        else if (argv[i][y] == 'c')
        {
          printf("coucou count\n");
          if (count_arg(data, argv, argc, &i) == 1)
            return 1;
          else
            break;
        }
        else
        {
          printf("ft_ping: invalid option -- '%c'\n", argv[i][y]);
          printf("Try 'ft_ping -?' for more information.\n");
          return 1;
        }
      }
    }
    else if (data->domain == NULL)
      data->domain = argv[i];
    printf("i = %d, argc = %d\n", i, argc);
    if (i == (argc - 1))
      break;
    i++;
  }
  if (data->domain == NULL || argc == 1)
  {
    printf("ft_ping: missing host operand\n");
    printf("Try 'ft_ping -?' for more information.\n");
    return 1;
  }
  return 0;
}
