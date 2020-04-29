/*
** main.c for zappy in /home/shotgun/projets/c/zappy/server_dir
**
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
**
** Started on  Thu Jun 16 18:47:55 CEST 2011 cerisier mickael
** Last update Thu Jun 16 18:47:55 CEST 2011 cerisier mickael
*/

#include <stdio.h>
#include "server.h"

void		player_inventaire(t_list *list)
{
  int		i;
  char		*buffer;
  t_client	*client;

  buffer = get_buffer(150);
  client = (t_client*)((t_action*)list->value)->client;
  i = sprintf(buffer, "{nourriture %u, linemate %u, deraumere %u, sibur %u, \
 mendiane %u, phiras %u, thystame %u}\n", client->inventory[0],
 client->inventory[1], client->inventory[2],
 client->inventory[3], client->inventory[4],
 client->inventory[5], client->inventory[6]);
  if (i > 0)
    add_packet_buffer_size(client->network->interface, buffer, i);
  else
    perror("sprintf");
}

static void	expulse(t_client *client, int src, int pos[2])
{
  int		k;
  char		*buffer;

  k = src - client->direction;
  if (k == 2 || k == -2)
    k = 1;
  else if (k == 0)
    k = 5;
  else if (k == 1 || k == -3)
    k = 3;
  else
    k = 7;
  buffer = get_buffer(16);
  k = sprintf(buffer, "deplacement: %d\n", k);
  add_packet_buffer_size(client->network->interface, buffer, k);
  change_position(client, pos[0], pos[1]);
  broadcast_monitor(client->network->zappy, client, ppo2);
}

void		player_expulse(t_list *list)
{
  int		pos[2];
  t_client	*client;

  client = (t_client*)((t_action*)list->value)->client;
  pos[0] = client->block->x;
  pos[1] = client->block->y;
  if (client->direction == 1)
    pos[1]--;
  else if (client->direction == 2)
    pos[0]++;
  else if (client->direction == 3)
    pos[1]++;
  else
    pos[0]--;
  if (client->node.prev || client->node.next)
    {
      add_packet(client->network->interface, OK);
      broadcast_monitor(client->network->zappy, client, pex);
    }
  else
    add_packet(client->network->interface, KO);
  while (client->node.prev)
    expulse((t_client*)client->node.prev->value, client->direction, pos);
  while (client->node.next)
    expulse((t_client*)client->node.next->value, client->direction, pos);
}
