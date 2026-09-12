#include "ft_ping.h"

t_ping* data_new(char* domain)
{
  t_ping* tmp = malloc(sizeof(t_ping));
  if (tmp == NULL)
  {
    fprintf(stderr, "tmp malloc error\n");
    return NULL;
  }  
  memset(tmp, 0, sizeof(t_ping));
  tmp->domain = domain;
  tmp->fd_socket = -1;
  return tmp;
}

int create_first_data(t_ping** data, t_ping** tmp, char* domain)
{
  *data = data_new(NULL);
  if (*data == NULL)
    return 1;
  memset(*data, 0, sizeof(t_ping));
  (*data)->domain = domain;
  (*data)->fd_socket = -1;
  *tmp = *data;
  return 0;
}

int create_node_data(t_ping** tmp, char* domain)
{
  (*tmp)->next = data_new(domain);
  *tmp = (*tmp)->next;
  if (*tmp == NULL)
    return 1;
  return 0;
}

t_ping* data_clear_node(t_ping** data)
{
  close((*data)->fd_socket);
  t_ping* tmp = (*data)->next;
  free(*data);
  *data = NULL;
  return tmp;
}

t_ping* data_clear_all(t_ping** data)
{
  while (*data)
  {
    if ((*data)->fd_socket != -1)
      close((*data)->fd_socket);
    t_ping* tmp = (*data)->next;
    free(*data);
    *data = tmp;
  }
  return *data;
}
