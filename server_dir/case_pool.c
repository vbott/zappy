/*
** main.c for zappy in /home/shotgun/projets/c/zappy/server_dir
**
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
**
** Started on  Fri Jun 17 17:59:50 CEST 2011 cerisier mickael
** Last update Fri Jun 17 17:59:50 CEST 2011 cerisier mickael
*/

#include <string.h>
#include "server.h"

static t_pool	gl_pool;

t_case		*get_case(void)
{
  t_list	*list;

  list = get_elem_pool(&gl_pool, 0);
  if (list->value == NULL)
    list->value = xmalloc(sizeof(t_case));
  memset(list->value, 0, sizeof(t_case));
  return (t_case*)list->value;
}

void		release_case(t_case *block)
{
  release_elem_pool(&gl_pool, block, 0);
}
