/*
** main.c for zappy in /home/shotgun/projets/c/zappy/server_dir
**
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
**
** Started on  Tue Jun 21 02:21:15 CEST 2011 cerisier mickael
** Last update Tue Jun 21 02:21:15 CEST 2011 cerisier mickael
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

static int	up_client(t_dlist *list, char *buffer, int size)
{
  t_client	*client;

  for (; list; list = list->next)
  {
    client = (t_client*)list->value;
    client->level++;
    if (client->level == 8)
    {
      client->team->nbhl++;
      if (client->team->nbhl >= 6)
      {
	reset_zappy(client->team, client->network->zappy);
	return (1);
      }
    }
    get_same_buffer(buffer);
    add_packet_buffer_size(client->network->interface, buffer, size);
    broadcast_monitor(client->network->zappy, client, &plv2);
  }
  return (0);
}

static void	end_incantation(t_list *list)
{
  t_client	*client;
  t_case	*block;
  char		*buffer;
  int		size;
  int		pos[2];
  size_t	food;

  buffer = NULL;
  client = ((t_action*)list->value)->client;
  pos[0] = strtol(((t_action*)list->value)->buffer, NULL, 10);
  strtok_r(((t_action*)list->value)->buffer, ",", &buffer);
  pos[1] = strtol(buffer, NULL, 10);
  block = find_in_map(client->network->zappy->map, pos[0], pos[1]);
  if (!verif_incantation(client, block, 1))
    return ;
  broadcast_monitor_value(client->network->zappy, client, (void*)1, &pie);
  buffer = get_buffer(25);
  food = block->stock[0];
  memset(&block->stock, 0, sizeof(block->stock));
  block->stock[0] = food;
  size = sprintf(buffer, "niveau actuel : %u\n", client->level + 1);
  if (!up_client(block->players, buffer, size))
    broadcast_monitor_value(client->network->zappy, client, block, &bct2);
  release_buffer(buffer);
}

void		player_incantation(t_list *list)
{
  t_client	*client;
  int		nb;
  char		*buffer;

  client = (t_client*)((t_action*)list->value)->client;
  if (!verif_incantation(client, client->block, 0))
    return ;
  nb = ((t_action*)list->value)->cycle - client->network->zappy->cycle;
  buffer = get_buffer(30);
  sprintf(buffer, "%d,%d", client->block->x, client->block->y);
  push_action(client, nb + 300, &end_incantation, buffer);
  buffer = get_buffer(25);
  nb = sprintf(buffer, "elevation en cours\n");
  broadcast_monitor_value(client->network->zappy, client, client->block, &pic);
  add_packet_buffer_size(client->network->interface, buffer, nb);
}
