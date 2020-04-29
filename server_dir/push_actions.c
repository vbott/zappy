/*
** push_actions for zappy in /home/snap/projects/zappy/server_dir
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Thu 16 Jun 2011 06:55:36 PM CEST botton vivien
** Last update Thu 16 Jun 2011 06:55:36 PM CEST botton vivien
*/

#include "server.h"

int			cmp_action(void *value1, void *value2)
{
return (((t_action*)value1)->cycle <= ((t_action*)value2)->cycle);
}

void			push_system_action_2(t_zappy *zappy, int cycle,
		void (*func)(t_list *), char *arg)
{
  t_action	*action;
  t_list	*list;

  list = xmalloc(sizeof(*list));
  action = xmalloc(sizeof(*action));
  action->client = zappy;
  action->system = 1;
  action->func = func;
  action->buffer = arg;
  action->cycle = zappy->cycle + cycle;
  list->value = action;
  sorted_insert(&zappy->actions, list, cmp_action);
}

void			push_system_action(t_client *client, int cycle,
		void (*func)(t_list *), char *arg)
{
  t_action	*action;
  t_list	*list;

  list = xmalloc(sizeof(*list));
  action = xmalloc(sizeof(*action));
  action->client = client;
  action->system = 1;
  action->func = func;
  action->buffer = arg;
  action->cycle = client->network->zappy->cycle + cycle;
  list->value = action;
  sorted_insert(&client->network->zappy->actions, list, cmp_action);
}

void			push_action(t_client *client, int cycle,
		void (*func)(t_list *), char *arg)
{
  t_action	*action;
  t_list	*list;

  if (!client->actions)
    return ;
  action = (t_action*)client->actions->value;
  action->func = func;
  action->buffer = arg;
  if (client->network->zappy->cycle > client->cycle)
    client->cycle = client->network->zappy->cycle;
  client->cycle += cycle;
  action->cycle = client->cycle;
  list = client->actions;
  client->actions = client->actions->next;
  sorted_insert(&client->network->zappy->actions, list, cmp_action);
}
