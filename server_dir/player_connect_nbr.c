/*
** main.c for zappy in /home/shotgun/projets/c/zappy/server_dir
**
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
**
** Started on  Tue Jun 21 02:45:12 CEST 2011 cerisier mickael
** Last update Tue Jun 21 02:45:12 CEST 2011 cerisier mickael
*/

#include <stdio.h>
#include "server.h"

void		send_map_info(t_client *client)
{
  int		size;
  char		*buffer;

  buffer = get_buffer(64);
  size = sprintf(buffer, "%d %d\n", client->network->zappy->x,
		  client->network->zappy->y);
  add_packet_buffer_size(client->network->interface, buffer, size);
}

void		connect_nbr(t_client *client)
{
  int		size;
  char		*buffer;

  buffer = get_buffer(12);
  size = client->team->nb_max - client->team->nb_player;
  size = sprintf(buffer, "%d\n", size);
  add_packet_buffer_size(client->network->interface, buffer, size);
}

void		player_connect(t_list *list)
{
  connect_nbr((t_client*)((t_action*)list->value)->client);
}
