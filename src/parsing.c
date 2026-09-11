# include "ft_ping.h"

int count_arg(int argc, char** argv, t_option* opt, int* i, int* y)
{
  if (*y == -1)
  {
    *y = 7; 
    if (argv[*i][*y] == '=')
      (*y)++;
  }
  else if (argv[*i][*y] == 'c')
    (*y)++;
  if (argv[*i][*y] == 0 && ((*i) + 1) <= (argc - 1))
  {
    if (argv[*i][(*y) - 1] == 'c' || argv[*i][(*y) - 1] == 't')
    { 
      (*i)++;
      (*y) = 0;
    }
  }
  else if (argv[*i][*y] == 0 && ((*i) + 1) > (argc - 1))
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
  if (argv[*i][y] == 0 && ((*i) + 1) <= (argc - 1) && argv[*i][y - 1] == 'l') 
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
    if (opt->ttl < 1)
    {
      printf("./ft_ping: option value too small: %d\n", opt->ttl);
      return 1;
    }
    else if (opt->ttl > 255)
    {
      printf("./ft_ping: option value too big: %d\n", opt->ttl);
      return 1;
    }
    free(str1);
  }
  else
  {
    char* str2 = substr(str1, ret, strlen(str1));
    printf("./ft_ping: invalid value (`%s' near `%s')\n", str1, str2);
    free(str1);
    free(str2);
    return 1;
  }
  return 0;
}

int double_hyphen(int argc, char** argv, t_option* opt, int* i)
{
  if (strcmp(argv[*i], "--verbose") == 0)
    opt->verbose = 1;
  else if (strncmp(argv[*i], "--count", 7) == 0 && (argv[*i][7] == '=' || argv[*i][7] == 0))
  {
    int y = -1;
    if (count_arg(argc, argv, opt, i, &y) == 1)
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
    printf("Try 'ft_ping -?' for more information.\n");
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
    else
    {
      printf("ft_ping: invalid option -- '%c'\n", argv[*i][y]);
      printf("Try 'ft_ping -?' for more information.\n");
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
      *data = data_new(NULL);
      if (*data == NULL)
        return 1;
      memset(*data, 0, sizeof(t_ping));
      (*data)->domain = argv[i];
      tmp = *data;
    }
    else
    {
      tmp->next = data_new(argv[i]);
      tmp = tmp->next;
      if (tmp == NULL)
        return 1;
    }
    if (i == (argc - 1))
      break;
    i++;
  }
  if ((*data)->domain == NULL || argc == 1)
  {
    printf("ft_ping: missing host operand\n");
    printf("Try 'ft_ping -?' for more information.\n");
    return 1;
  }
  return 0;
}
