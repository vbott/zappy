/*
** monitor_functions for zappy in /home/snap/projects/zappy/server_dir
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sat 18 Jun 2011 06:06:40 PM CEST botton vivien
** Last update Sat 18 Jun 2011 06:06:40 PM CEST botton vivien
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

void		msz(t_interface *interface, char *arg)
{
  t_zappy	*zappy;
  char		*buffer;
  int		size;

  (void)(arg);
  zappy = (t_zappy*)interface->userdata;
  buffer = get_buffer(64);
  size = sprintf(buffer, "msz %d %d\n", zappy->x, zappy->y);
  add_packet_buffer_size(interface, buffer, size);
}

void		tna(t_interface *interface, char *arg)
{
  t_zappy	*zappy;
  char		*buffer;
  int		size;
  t_list	*teams;
  t_team	*team;

  (void)(arg);
  zappy = (t_zappy*)interface->userdata;
  for (teams = zappy->teams; teams; teams = teams->next)
  {
    team = (t_team*)teams->value;
    size = strlen(team->name);
    buffer = get_buffer(size);
    size = sprintf(buffer, "tna %s\n", team->name);
    add_packet_buffer_size(interface, buffer, size);
  }
}

void		ppo(t_interface *interface, char *arg)
{
  t_rb_tree	*node;
  t_zappy       *zappy;
  char		*buffer;
  int		size;
  int		id;
  t_client	*client;

  id = strtol((arg[0] == '#') ? &arg[1] : arg, NULL, 10);
  if (id < 1)
  {
    add_packet(interface, "sbp\n");
    return ;
  }
  zappy = (t_zappy*)interface->userdata;
  node = find_node(id, &zappy->clients);
  if (!node)
  {
    add_packet(interface, "sbp\n");
    return ;
  }
  buffer = get_buffer(64);
  client = (t_client*)node->value;
  ppo2(buffer, &size, client);
  add_packet_buffer_size(interface, buffer, size);
}

void		plv(t_interface *interface, char *arg)
{
  t_rb_tree	*node;
  t_zappy       *zappy;
  char		*buffer;
  int		size;
  int		id;

  id = strtol((arg[0] == '#') ? &arg[1] : arg, NULL, 10);
  zappy = (t_zappy*)interface->userdata;
  if (id < 1 || !(node = find_node(id, &zappy->clients)))
  {
    add_packet(interface, "sbp\n");
    return ;
  }
  node = find_node(id, &zappy->clients);
  buffer = get_buffer(64);
  size = sprintf(buffer, "plv %d %u\n", id,
		  ((t_client*)node->value)->level);
  add_packet_buffer_size(interface, buffer, size);
}

void		pin(t_interface *interface, char *arg)
{
  t_rb_tree	*node;
  t_zappy       *zappy;
  char		*buffer;
  int		size;
  int		id;
  t_client	*client;

  id = strtol((arg[0] == '#') ? &arg[1] : arg, NULL, 10);
  zappy = (t_zappy*)interface->userdata;
  if (id < 1 || !(node = find_node(id, &zappy->clients)))
  {
    add_packet(interface, "sbp\n");
    return ;
  }
  buffer = get_buffer(64);
  client = (t_client*)node->value;
  pin2(buffer, &size, client);
  add_packet_buffer_size(interface, buffer, size);
}

