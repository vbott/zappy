/*
** monitor_functions4 for zappy in /home/snap/projects/zappy/server_dir
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Wed 22 Jun 2011 05:50:00 PM CEST botton vivien
** Last update Wed 22 Jun 2011 05:50:00 PM CEST botton vivien
*/

#include <stdio.h>
#include "server.h"

void		pnw(char *buffer, int *size, t_client *client)
{
  *size = sprintf(buffer, "pnw %u %d %d %u %u %s\n", client->id,
		 client->block->x, client->block->y, client->direction,
		 client->level, client->team->name);
}

void		pnw2(t_interface *interface, t_client *client)
{
  int		size;
  char		*buffer;

  buffer = get_buffer(64);
  pnw(buffer, &size, client);
  add_packet_buffer_size(interface, buffer, size);
}

void		pex(char *buffer, int *size, t_client *client)
{
  *size = sprintf(buffer, "pex %u\n", client->id);
}

void		seg(char *buffer, int *size, t_client *client, char *team)
{
  (void)(client);
  *size = sprintf(buffer, "seg %s\n", team);
}

void		smg(char *buffer, int *size, t_client *client, char *team)
{
  (void)(client);
  *size = sprintf(buffer, "smg %s\n", team);
}
