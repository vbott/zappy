/*
** monitor_functions3 for zappy in /home/snap/projects/zappy/server_dir
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Mon 20 Jun 2011 10:05:20 PM CEST botton vivien
** Last update Mon 20 Jun 2011 10:05:20 PM CEST botton vivien
*/

#include <stdio.h>
#include <stdlib.h>
#include "server.h"

void		sgt(t_interface *interface, char *arg)
{
  t_zappy	*zappy;
  char		*buffer;
  int		size;

  (void)(arg);
  zappy = (t_zappy*)interface->userdata;
  buffer = get_buffer(64);
  size = sprintf(buffer, "sgt %d\n", zappy->t);
  add_packet_buffer_size(interface, buffer, size);
}

void		sst(t_interface *interface, char *arg)
{
  t_zappy	*zappy;
  int		t;

  zappy = (t_zappy*)interface->userdata;
  t = strtol(arg, NULL, 10);
  if (t >= 0 && t <= 1000)
   zappy->t = t;
  broadcast_monitor_value(zappy, NULL, zappy, &sgt2);
}

void		pin2(char *buffer, int *size, t_client *client)
{
  *size = sprintf(buffer, "pin %d %d %d %u %u %u %u %u %u %u\n",
  client->id, client->block->x, client->block->y, client->inventory[0],
  client->inventory[1], client->inventory[2], client->inventory[3],
  client->inventory[4], client->inventory[5], client->inventory[6]);
}

void		enw2(t_interface *interface, t_client *client)
{
  int		size;
  char		*buffer;

  buffer = get_buffer(64);
  enw(buffer, &size, client);
  add_packet_buffer_size(interface, buffer, size);
}

void		bct2(char *buffer, int *size, t_client *client, void *arg)
{
   t_case	*block;

   (void)client;
   block = (t_case*)arg;
   if (block)
     *size = sprintf(buffer, "bct %d %d %u %u %u %u %u %u %u\n",
		     block->x, block->y, block->stock[0],
		     block->stock[1], block->stock[2], block->stock[3],
		     block->stock[4], block->stock[5], block->stock[6]);
}
