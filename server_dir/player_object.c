/*
** main.c for zappy in /home/shotgun/projets/c/zappy/server_dir
**
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
**
** Started on  Thu Jun 16 18:49:40 CEST 2011 cerisier mickael
** Last update Thu Jun 16 18:49:40 CEST 2011 cerisier mickael
*/

#include <string.h>
#include "server.h"

static const char	*gl_stock[] = {
	"nourriture",
	"linemate",
	"deraumere",
	"sibur",
	"mendiane",
	"phiras",
	"thystame"
};

static int	get_nb(char *buffer)
{
  int		i;

  for (i = 0; i < (int)(sizeof(gl_stock) / sizeof(char*)); i++)
  {
    if (!strcmp(buffer, gl_stock[i]))
      return (i);
  }
  return (-1);
}

void		player_prend(t_list *list)
{
  t_action	*action;
  t_client	*client;
  int		id;

  action = (t_action*)list->value;
  client = (t_client*)action->client;
  id = get_nb(action->buffer);
  if (id != -1 && client->block->stock[id] > 0)
  {
    client->block->stock[id]--;
    client->inventory[id]++;
    if (!id)
      client->network->zappy->bread--;
    add_packet(client->network->interface, OK);
    broadcast_monitor_value(client->network->zappy, client, (void*)id, pgt);
    broadcast_monitor(client->network->zappy, client, pin2);
    broadcast_monitor_value(client->network->zappy, client,
		    	    client->block, &bct2);
    return ;
  }
  add_packet(client->network->interface, KO);
}

void		player_pose(t_list *list)
{
  t_action	*action;
  t_client	*client;
  int		id;

  action = (t_action*)list->value;
  client = (t_client*)action->client;
  id = get_nb(action->buffer);
  if (id != -1 && client->inventory[id] > 0)
  {
    client->block->stock[id]++;
    client->inventory[id]--;
    if (!id)
      client->network->zappy->bread++;
    add_packet(client->network->interface, OK);
    broadcast_monitor_value(client->network->zappy, client, (void*)id, pdr);
    broadcast_monitor(client->network->zappy, client, pin2);
    broadcast_monitor_value(client->network->zappy, client,
		    	    client->block, &bct2);
    return ;
  }
  add_packet(client->network->interface, KO);
}
