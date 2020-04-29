/*
** monitor_functions2 for zappy in /home/snap/projects/zappy/server_dir
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Mon 20 Jun 2011 10:03:06 PM CEST botton vivien
** Last update Mon 20 Jun 2011 10:03:06 PM CEST botton vivien
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

static void		send_case_info(int x, int y,
		t_interface *interface, t_zappy *zappy)
{
  char		*buffer;
  int		size;
  t_case	*block;

 if (x < 0 || y < 0 || x >= zappy->x || y >= zappy->y)
 {
   add_packet(interface, "sbp\n");
   return ;
 }
 block = (t_case*)find_in_map(zappy->map, x, y);
 buffer = get_buffer(64);
 if (block)
  bct2(buffer, &size, NULL, block);
 else
  size = sprintf(buffer, "bct %d %d 0 0 0 0 0 0 0\n", x, y);
 add_packet_buffer_size(interface, buffer, size);
}

void		bct(t_interface *interface, char *arg)
{
  int		x;
  int		y;
  t_zappy       *zappy;
  char		*nb;

  nb = NULL;
  arg = strtok_r(arg, " ", &nb);
  if (!arg || !nb || !nb[0])
  {
    add_packet(interface, "sbp\n");
    return ;
  }
  zappy = (t_zappy*)interface->userdata;
  x = strtol(arg, NULL, 10);
  y = strtol(nb, NULL, 10);
  send_case_info(x, y, interface, zappy);
}

void		mct(t_interface *interface, char *arg)
{
  int		x;
  int		y;
  t_zappy       *zappy;

  (void)(arg);
  zappy = (t_zappy*)interface->userdata;
  for (x = 0; x < zappy->x; x++)
  {
    for (y = 0; y < zappy->y; y++)
    {
      send_case_info(x, y, interface, zappy);
    }
  }
}

void		sgt2(char *buffer, int *size, t_client *client, void *arg)
{
  (void)client;
  *size = sprintf(buffer, "sgt %d\n", ((t_zappy*)arg)->t);
}
