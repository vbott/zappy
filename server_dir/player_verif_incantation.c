/*
** main.c for zappy in /home/shotgun/projets/c/zappy/server_dir
**
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
**
** Started on  Thu Jun 23 00:55:27 CEST 2011 cerisier mickael
** Last update Thu Jun 23 00:55:27 CEST 2011 cerisier mickael
*/

#include <stdio.h>
#include <string.h>
#include "server.h"

static const size_t	gl_level[][7] = {
	{1, 1, 0, 0, 0, 0, 0},
	{2, 1, 1, 1, 0, 0, 0},
	{2, 2, 0, 1, 0, 2, 0},
	{4, 1, 1, 2, 0, 1, 0},
	{4, 1, 2, 1, 3, 0, 0},
	{6, 1, 2, 3, 0, 1, 0},
	{6, 2, 2, 2, 2, 2, 1}
};

static void	error_incantation(t_case *block, t_client *client)
{
  t_dlist	*list;
  int		size;
  char		*buffer;

  if (!block)
    add_packet(client->network->interface, KO);
  else
  {
    buffer = get_buffer(strlen(KO) + 1);
    size = sprintf(buffer, "%s", KO);
    for (list = block->players; list; list = list->next)
    {
      get_same_buffer(buffer);
      add_packet_buffer_size(((t_client*)list->value)->network->interface,
		      	     buffer, size);
    }
    release_buffer(buffer);
  }
}

static size_t	verif_player(t_client *client, t_dlist *list, size_t level)
{
  size_t	nb;

  nb = 0;
  for (; list && nb <= level; list = list->next)
  {
    if (((t_client*)list->value)->level != client->level)
      return (0);
    nb++;
  }
  return (nb);
}

static void	handle_incantation_error(t_client *client,
				         t_case *block, int end)
{
  if (end)
  {
    broadcast_monitor_value(client->network->zappy, client, (void*)0, &pie);
    error_incantation(block, client);
  }
  else
    add_packet(client->network->interface, KO);
}

int		verif_incantation(t_client *client, t_case *block, int end)
{
  size_t	level;

  level = client->level - 1;
  if (end && block &&
     (client->block->x != block->x || client->block->y != block->y))
    add_packet(client->network->interface, KO);
  if (block && level <= sizeof(gl_level) / (7 * sizeof(size_t)))
  {
    if (block->stock[1] == gl_level[level][1] &&
	block->stock[2] == gl_level[level][2] &&
	block->stock[3] == gl_level[level][3] &&
	block->stock[4] == gl_level[level][4] &&
	block->stock[5] == gl_level[level][5] &&
	block->stock[6] == gl_level[level][6])
    {
      if (verif_player(client, block->players, gl_level[level][0]) ==
	  gl_level[level][0])
        return (1);
    }
  }
  handle_incantation_error(client, block, end);
  return (0);
}
