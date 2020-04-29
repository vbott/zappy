/*
** main.c for zappy in /home/shotgun/projets/c/zappy/server_dir
**
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
**
** Started on  Mon Jun 20 19:00:43 CEST 2011 cerisier mickael
** Last update Mon Jun 20 19:00:43 CEST 2011 cerisier mickael
*/

#include <string.h>
#include <stdio.h>
#include <math.h>
#include "server.h"

static const double	gl_angle[] = {
	M_PI / 8,
	M_PI / 8 * 3,
	M_PI / 8 * 5,
	M_PI / 8 * 7,
	M_PI / 8 * 9,
	M_PI / 8 * 11,
	M_PI / 8 * 13,
	M_PI / 8 * 15,
};

static int	get_y(t_client *src, t_client *dest, size_t *coef)
{
  int		pos[2];

  if (src->block->y > dest->block->y)
  {
    pos[0] = src->block->y - dest->block->y;
    pos[1] = (src->network->zappy->y - src->block->y) + dest->block->y;
    if (pos[0] > pos[1])
      return (pos[1]);
    *coef = 1;
    return (pos[0]);
  }
  pos[0] = dest->block->y - src->block->y;
  pos[1] = (src->network->zappy->y - dest->block->y) + src->block->y;
  if (pos[0] < pos[1])
    return (pos[0]);
  *coef = 1;
  return (pos[1]);

}

static int	get_x(t_client *src, t_client *dest, size_t *coef)
{
  int		pos[2];

  if (src->block->x > dest->block->x)
  {
    pos[0] = src->block->x - dest->block->x;
    pos[1] = (src->network->zappy->x - src->block->x) + dest->block->x;
    if (pos[0] > pos[1])
      return (pos[1]);
    *coef = (*coef == 1) ? 2 : 3;
    return (pos[0]);
  }
  pos[0] = dest->block->x - src->block->x;
  pos[1] = (src->network->zappy->x - dest->block->x) + src->block->x;
  if (pos[0] < pos[1])
    return (pos[0]);
  *coef = (*coef == 1) ? 2 : 3;
  return (pos[1]);
}

static int	get_direction(t_client *src, t_client *dest)
{
  int		pos[2];
  size_t	coef;
  double	angle;

  if (src->block->x == dest->block->x && src->block->y == dest->block->y)
    return (0);
  coef = 0;
  pos[1] = get_y(src, dest, &coef);
  pos[0] = get_x(src, dest, &coef);
  angle = coef * M_PI / 2;
  if (angle <= M_PI / 2 || (angle >= M_PI && angle < M_PI * 1.5))
    angle += (pos[1] > 0) ? atan((double)pos[0] / (double)pos[1]) : M_PI / 2;
  else
    angle += (pos[0] > 0) ? atan((double)pos[1] / (double)pos[0]) : M_PI / 2;
  angle = angle + ((dest->direction - 1) * M_PI / 2);
  while (angle > M_PI * 2)
    angle -= M_PI * 2;
  pos[0] = 1;
  for (coef = 0; coef < sizeof(gl_angle) / sizeof(double); coef++)
  {
    if (angle < gl_angle[coef])
      return (coef + 1);
  }
  return (1);
}

static void	send_to_client(t_client *src, t_rb_tree *list,
			       char *buffer, int size)
{
  char		*tmp;
  int		len;
  t_client	*client;

  for (; list; list = list->prev)
  {
    if (list->value != src)
    {
      client = (t_client*)list->value;
      tmp = get_buffer(12);
      get_same_buffer(buffer);
      len = sprintf(tmp, "message %d,", get_direction(src, client));
      add_packet_buffer_size(client->network->interface, tmp, len);
      add_packet_buffer_size(client->network->interface, buffer, size);
    }
  }
}

void		player_broadcast(t_list *node)
{
  t_action	*action;
  t_client	*client;
  int		size;

  action = (t_action*)node->value;
  client = (t_client*)action->client;
  size = strlen(action->buffer);
  broadcast_monitor_msg(client->network->zappy,
		  client, action->buffer, &pbc);
  action->buffer[size] = '\n';
  send_to_client(client, client->network->zappy->clients.last,
		 action->buffer, size + 1);
  add_packet(client->network->interface, OK);
}
