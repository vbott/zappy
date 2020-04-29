/*
** main.c for zappy in /home/shotgun/projets/c/zappy/server_dir
**
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
**
** Started on  Tue Jun 14 15:17:11 CEST 2011 cerisier mickael
** Last update Tue Jun 14 15:17:11 CEST 2011 cerisier mickael
*/

#include "server.h"

void			push_front_node(t_list **list, t_list *node)
{
  node->next = *list;
  *list = node;
}

void			push_front(t_list **list, void *value)
{
  t_list		*tmp;

  tmp = xmalloc(sizeof(*tmp));
  tmp->value = value;
  tmp->next = *list;
  *list = tmp;
}

void			sorted_insert(t_list **list, t_list *node,
				      int (*func)(void*, void*))
{
  t_list		*tmp;
  t_list		*mem;

  tmp = NULL;
  for (mem = *list; mem; mem = mem->next)
  {
    if (!func(mem->value, node->value))
    {
      node->next = mem;
      if (!tmp)
	*list = node;
      else
	tmp->next = node;
      return ;
    }
    tmp = mem;
  }
  node->next = NULL;
  if (!tmp)
    *list = node;
  else
    tmp->next = node;
}

