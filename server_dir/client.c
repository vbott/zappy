/*
** main.c for zappy in /home/shotgun/projets/c/zappy/server_dir
**
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
**
** Started on  Fri Jun 17 18:59:59 CEST 2011 cerisier mickael
** Last update Fri Jun 17 18:59:59 CEST 2011 cerisier mickael
*/

#include <stdlib.h>
#include <string.h>
#include "server.h"

static size_t		get_client_id(void)
{
  static size_t		id = 1;

  return (id++);
}

t_client		*create_client(t_team *team, t_zappy *zappy)
{
  int			i;
  t_client		*client;
  t_action		*action;

  client = xmalloc(sizeof(*client));
  memset(client, 0, sizeof(*client));
  for (i = 0; i < 10; i++)
  {
    action = xmalloc(sizeof(*action));
    action->system = 0;
    action->client = client;
    push_front(&client->actions, action);
  }
  client->network = xmalloc(sizeof(t_network));
  client->network->interface = NULL;
  client->network->zappy = zappy;
  client->id = get_client_id();
  client->level = 1;
  client->team = team;
  client->direction = (rand() % 4) + 1;
  client->node.value = client;
  client->inventory[0] = 10;
  insert_node2(client->id, client, &zappy->clients);
  return (client);
}

static t_client		*new_client(t_zappy *zappy, t_team *team)
{
  t_client		*client;

  client = create_client(team, zappy);
  change_position(client, rand() % zappy->x, rand() % zappy->y);
  push_system_action(client, EAT, &hungry, NULL);
  zappy->nbplayers++;
  return (client);
}

static t_client		*get_zombie_client(t_team *team)
{
 t_list                 *list;
 t_client		*tmp;

 if (team->client)
 {
   list = team->client;
   tmp = (t_client*)list->value;
   team->client = list->next;
   if (!team->client)
     team->lastclient = NULL;
   free(list);
   tmp->parent = 0;
   return (tmp);
 }
 for (list = team->egg; list; list = list->next)
 {
   tmp = (t_client*)list->value;
   if (!tmp->network->interface)
     return (tmp);
 }
 return (NULL);
}

void			add_client(t_zappy *zappy, t_team *team,
				   t_interface *interface)
{
  t_client		*client;
  static size_t		inventory[7] = {0, 14, 12, 15, 14, 10, 2};

  client = get_zombie_client(team);
  if (!client)
  {
    client = new_client(zappy, team);
    release_ressources(zappy, inventory);
  }
  client->network->interface = interface;
  interface->hangup = &close_client;
  interface->userdata = client;
  interface->arg = interface->userdata;
  interface->parsing = &client_parse;
  if (!client->parent)
    broadcast_monitor(zappy, client, &pnw);
  else
    release_ressources(zappy, inventory);
  client->team->nb_player++;
  connect_nbr(client);
  send_map_info(client);
}
