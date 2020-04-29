/*
** main.c for zappy in /home/shotgun/projets/c/zappy/server_dir
**
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
**
** Started on  Thu Jun 16 18:50:56 CEST 2011 cerisier mickael
** Last update Thu Jun 16 18:50:56 CEST 2011 cerisier mickael
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"

static void	remove_egg(t_client *egg)
{
  t_list	*tmp;
  t_list	*list;

  tmp = NULL;
  for (list = egg->team->egg; list; list = list->next)
  {
    if (list->value == egg)
    {
      if (tmp)
	tmp->next = list->next;
      else
	egg->team->egg = list->next;
      if (!list->next)
        egg->team->lastegg = tmp;
      free(list);
      return ;
    }
    tmp = list;
  }
}

static void	hatching_egg(t_list *list)
{
  t_client	*client;

  client = ((t_action*)list->value)->client;
  remove_egg(client);
  free(list->value);
  if (!client->network->interface)
  {
    list->value = client;
    list->next = NULL;
    if (client->team->lastclient)
      client->team->lastclient->next = list;
    else
      client->team->client = list;
    client->team->lastclient = list;
  }
  else
  {
    free(list);
    broadcast_monitor(client->network->zappy, client, &ebo);
    broadcast_monitor(client->network->zappy, client, &pnw);
    client->parent = 0;
  }
  client->network->zappy->nbplayers++;
  push_system_action(client, EAT, &hungry, NULL);
  broadcast_monitor(client->network->zappy, client, eht);
}

static t_client	*create_egg(t_client *src, long unsigned int cycle)
{
  t_client	*client;

  client = create_client(src->team, src->network->zappy);
  client->parent = src->id;
  client->cycle = cycle;
  client->block = src->block;
  client->node.next = src->block->players;
  src->block->players->prev = &client->node;
  src->block->players = &client->node;
  broadcast_monitor(client->network->zappy, src, pfk);
  return (client);
}

void		player_fork(t_list *list)
{
  t_client	*new;
  t_action	*action;
  t_client	*client;
  t_list	*tmp;

  action = (t_action*)list->value;
  client = (t_client*)action->client;
  new = create_egg(client, action->cycle + HATCHING);
  tmp = xmalloc(sizeof(*tmp));
  tmp->value = new;
  tmp->next = NULL;
  if (new->team->lastegg)
    new->team->lastegg->next = tmp;
  else
    new->team->egg = tmp;
  new->team->lastegg = tmp;
  client->team->nb_max++;
  push_system_action(new, (action->cycle + HATCHING) -
		     client->network->zappy->cycle, &hatching_egg, NULL);
  add_packet(client->network->interface, OK);
  broadcast_monitor(client->network->zappy, new, enw);
}
