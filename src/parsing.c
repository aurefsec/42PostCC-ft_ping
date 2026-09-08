# include "ft_ping.h"

void query_arg(t_option* opt)
{
  (void)opt;
}

void verbose_arg(t_option* opt)
{
  opt->verbose = 1;
}

int count_arg(int argc, char** argv, t_option* opt, int* i, int* y)
{
  if (argv[*i][(*y) + 1])
    (*y)++;
  else if (((*i) + 1) <= (argc - 1))
  {
    (*i)++;
    (*y) = 0;
  }
  else
  {
    printf("./ft_ping: option requires an argument -- 'c'\n");
    printf("Try 'ft_ping -?' for more information.\n");
    return 1;
  }
  char* str1 = substr(argv[*i], *y, strlen(argv[*i]));
  if (str1 == NULL)
  {
    fprintf(stderr, "./ft_ping: substr malloc error\n");
    return 1;
  }
  size_t ret = is_valid_number(str1);
  if (ret == strlen(str1))
  {
    opt->count = atoi(str1);
    free(str1);
  }
  else
  {
    char* str2 = substr(str1, ret, strlen(str1));
    printf("./ping: invalid value (`%s' near `%s')\n", str1, str2);
    free(str1);
    free(str2);
    return 1;
  }
  return 0;
}

int ttl_arg(int argc, char** argv, t_option* opt, int *i)
{
  int y = 5;

  if (argv[*i][y] == '=')
    y++;
  else if (argv[*i][y] == 0 && ((*i) + 1) <= (argc - 1)) 
  {
    (*i)++;
    y = 0;
  }
  else if (argv[*i][y] == 0 && ((*i) + 1) > (argc - 1))
  {
    printf("./ft_ping: option requires an argument -- 'c'\n");
    printf("Try 'ft_ping -?' for more information.\n");
    return 1;
  }
  else
  {
    printf("./ft_ping: unrecognized option '%s'\n", argv[*i]);
    printf("Try 'ft_ping -?' for more information.\n");
    return 1;
  }
  char* str1 = substr(argv[*i], y, strlen(argv[*i]));
  if (str1 == NULL)
  {
    fprintf(stderr, "./ft_ping: substr malloc error\n");
    return 1;
  }
  size_t ret = is_valid_number(str1);
  if (ret == strlen(str1))
  {
    opt->ttl = atoi(str1);
    free(str1);
  }
  else
  {
    char* str2 = substr(str1, ret, strlen(str1));
    printf("./ping: invalid value (`%s' near `%s')\n", str1, str2);
    free(str1);
    free(str2);
    return 1;
  }
  return 0;
}

int double_hyphen(int argc, char** argv, t_option* opt, int* i)
{
  size_t len = strlen(argv[*i]);

  if (len >= 5 && argv[*i][2] == 't' && argv[*i][3] == 't' && argv[*i][4] =='l')
  {
    if (ttl_arg(argc, argv, opt, i) == 1)
      return 1;
  }
  return 0;
}

int one_hyphen(int argc, char** argv, t_option* opt, int* i)
{
  for (int y = 1; argv[*i][y]; y++)
  {
    if (argv[*i][y] == '?')
      query_arg(opt);
    else if (argv[*i][y] == 'v')
      verbose_arg(opt);
    else if (argv[*i][y] == 'c')
    {
      if (count_arg(argc, argv, opt, i, &y) == 1)
        return 1;
      else
        break;
    }
    else
    {
      printf("ft_ping: invalid option -- '%c'\n", argv[*i][y]);
      printf("Try 'ft_ping -?' for more information.\n");
      return 1;
    }
  }
  return 0;
}

int parsing(int argc, char** argv, t_option* opt, t_ping* data)
{
  int i = 1;

  // Parse arguments to get domain and options.
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
    else if (data->domain == NULL)
      data->domain = argv[i];
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
