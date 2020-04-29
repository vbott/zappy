/*
** main.c for zappy in /home/shotgun/projets/c/zappy/server_dir
**
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
**
** Started on  Thu Jun 16 15:28:51 CEST 2011 cerisier mickael
** Last update Thu Jun 16 15:28:51 CEST 2011 cerisier mickael
*/

#include <stdlib.h>
#include "server.h"

static void	up_pool(t_pool *pool)
{
  pool->current++;
  pool->cycle++;
  if (pool->max < pool->current)
    pool->max = pool->current;
}

static void	down_pool(t_pool *pool)
{
  t_list	*list;

  pool->current--;
  if (pool->cycle >= 500)
  {
    pool->cycle = 0;
    while (pool->list && pool->nb > pool->max)
    {
      list = pool->list;
      pool->list = list->next;
      free(list->value);
      free(list);
      pool->nb--;
    }
    pool->max = pool->current;
  }
}

t_list		*get_elem_pool(t_pool *pool, int used)
{
  t_list	*list;

  up_pool(pool);
  if (pool->list != NULL)
  {
    list = pool->list;
    pool->list = list->next;
  }
  else
  {
    list = xmalloc(sizeof(*list));
    list->value = NULL;
    pool->nb++;
  }
  if (!used)
  {
    list->next = pool->used;
    pool->used = list;
  }
  return list;
}

void		release_elem_pool(t_pool *pool, void *value, int used)
{
  t_list	*list;

  if (!value)
    return ;
  if (!used)
  {
    list = pool->used;
    if (!list)
      return ;
    pool->used = list->next;
    list->value = value;
  }
  else
    list = (t_list*)value;
  list->next = pool->list;
  pool->list = list;
  down_pool(pool);
}
