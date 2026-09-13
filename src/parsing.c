# include "ft_ping.h"

int double_hyphen(int argc, char** argv, t_option* opt, int* i)
{
  if (strcmp(argv[*i], "--help") == 0)
  {
    print_query();
    return 1;
  }
  else if (strcmp(argv[*i], "--verbose") == 0)
    opt->verbose = 1;
  else if (strncmp(argv[*i], "--count", 7) == 0 && (argv[*i][7] == '=' || argv[*i][7] == 0))
  {
    int y = -1;
    if (count_arg(argc, argv, opt, i, &y) == 1)
      return 1;
  }
  else if (strncmp(argv[*i], "--interval", 10) == 0 && (argv[*i][10] == '=' || argv[*i][10] == 0))
  {
    int y = -1;
    if (interval_arg(argc, argv, opt, i, &y) == 1)
      return 1;
  }
  else if (strncmp(argv[*i], "--ttl", 5) == 0 && (argv[*i][5] == '=' || argv[*i][5] == 0))
  {
    if (ttl_arg(argc, argv, opt, i) == 1)
      return 1;
  }
  else
  {
    printf("./ft_ping: unrecognized option '%s'\n", argv[*i]);
    printf("Try 'ft_ping --help' for more information.\n");
    return 1;
  }
  return 0;
}

int one_hyphen(int argc, char** argv, t_option* opt, int* i)
{
  for (int y = 1; argv[*i][y]; y++)
  {
    if (argv[*i][y] == '?')
    {
      print_query();
      return 1;
    }
    else if (argv[*i][y] == 'v')
      opt->verbose = 1;
    else if (argv[*i][y] == 'c')
    {
      if (count_arg(argc, argv, opt, i, &y) == 1)
        return 1;
      else
        break;
    }
    else if (argv[*i][y] == 'i')
    {
      if (interval_arg(argc, argv, opt, i, &y) == 1)
        return 1;
      else
        break;
    }
    else
    {
      printf("ft_ping: invalid option -- '%c'\n", argv[*i][y]);
      printf("Try 'ft_ping --help' for more information.\n");
      return 1;
    }
  }
  return 0;
}

int parsing(int argc, char** argv, t_option* opt, t_ping** data)
{
  int i = 1;
  t_ping* tmp = NULL;

  // Parse arguments to get domains and options.
  while (i < argc)
  {
    if (strlen(argv[i]) > 2 && argv[i][0] == '-' && argv[i][1] == '-')
    {
      if (double_hyphen(argc, argv, opt, &i) == 1)
        return 1;
    }
    else if (strlen(argv[i]) > 1 && argv[i][0] == '-')
    {
      if (one_hyphen(argc, argv, opt, &i) == 1)
        return 1;
    }
    else if (*data == NULL)
    {
      if (create_first_data(data, &tmp, argv[i]) == 1)
        return 1;
    }
    else
    {
      if (create_node_data(&tmp, argv[i]) == 1)
        return 1;
    }
    if (i == (argc - 1))
      break;
    i++;
  }
  if (*data == NULL || argc == 1)
  {
    printf("ft_ping: missing host operand\n");
    printf("Try 'ft_ping --help' for more information.\n");
    return 1;
  }
  return 0;
}
