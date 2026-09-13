#include "ft_ping.h"

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
    char* endptr;
    opt->count = strtol(str1, &endptr, 10);
    free(str1);
    if (errno == ERANGE || opt->interval < 1)
    {
      perror("./ft_ping");
      return 1;
    }
  }
  else
  {
    char* str2 = substr(str1, ret, strlen(str1));
    if (str2 == NULL)
    {
      free(str1);
      return 1;
    }
    printf("./ping: invalid value (`%s' near `%s')\n", str1, str2);
    free(str1);
    free(str2);
    return 1;
  }
  return 0;
}

int interval_arg(int argc, char** argv, t_option* opt, int* i, int* y)
{
  if (*y == -1)
  {
    *y = 10; 
    if (argv[*i][*y] == '=')
      (*y)++;
  }
  else if (argv[*i][*y] == 'i')
    (*y)++;
  if (argv[*i][*y] == 0 && ((*i) + 1) <= (argc - 1))
  {
    if (argv[*i][(*y) - 1] == 'i' || argv[*i][(*y) - 1] == 'l')
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
    char* endptr;
    opt->interval = strtol(str1, &endptr, 10);
    free(str1);
    if (errno == ERANGE || opt->interval < 1)
    {
      printf("./ft_ping: sending packet: No buffer space available\n");
      return 1;
    }
  }
  else
  {
    char* str2 = substr(str1, ret, strlen(str1));
    if (str2 == NULL)
    {
      free(str1);
      return 1;
    }
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
    printf("Try 'ft_ping --help' for more information.\n");
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
    char* endptr;
    opt->ttl = strtol(str1, &endptr, 10);
    free(str1);
    if (errno == ERANGE)
    {
      perror("./ft_ping");
      return 1;
    }
    if (opt->ttl < 1)
    {
      printf("./ft_ping: option value too small: %ld\n", opt->ttl);
      return 1;
    }
    else if (opt->ttl > 255)
    {
      printf("./ft_ping: option value too big: %ld\n", opt->ttl);
      return 1;
    }
  }
  else
  {
    char* str2 = substr(str1, ret, strlen(str1));
    if (str2 == NULL)
    {
      free(str1);
      return 1;
    }
    printf("./ft_ping: invalid value (`%s' near `%s')\n", str1, str2);
    free(str1);
    free(str2);
    return 1;
  }
  return 0;
}

