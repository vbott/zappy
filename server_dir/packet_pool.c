/*
** main.c for zappy in /home/shotgun/projets/c/zappy/server_dir
**
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
**
** Started on  Thu Jun 16 17:01:51 CEST 2011 cerisier mickael
** Last update Thu Jun 16 17:01:51 CEST 2011 cerisier mickael
*/

#include <stdlib.h>
#include "server.h"

static t_pool	gl_pool;

t_list		*get_packet(void)
{
  t_list	*list;

  list = get_elem_pool(&gl_pool, 1);
  if (list->value == NULL)
    list->value = xmalloc(sizeof(t_packet));
  return (list);
}

inline void	release_packet(t_list *packet)
{
  release_elem_pool(&gl_pool, packet, 1);
}
