/*
** main.c for zappy in /home/shotgun/projets/c/zappy/server_dir
**
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
**
** Started on  Sat Jun 18 14:07:04 CEST 2011 cerisier mickael
** Last update Sat Jun 18 14:07:04 CEST 2011 cerisier mickael
*/

#include <string.h>
#include <stdio.h>
#include "server.h"

static const char	*gl_name[] = {
	" nourriture",
	" linemate",
	" deraumere",
	" sibur",
	" mendiane",
	" phiras",
	" thystame",
	" joueur"
};

static void	init_voir(t_client *client, size_t nb[2], t_coord *pos,
			  int up[2])
{
  if (client->direction == 1)
  {
    pos->x = client->network->zappy->x + client->block->x - (nb[0] / 2);
    pos->y = client->network->zappy->y + client->block->y - nb[1];
    up[0] = 1;
  }
  else if (client->direction == 2)
  {
    pos->x = client->network->zappy->x + client->block->x + nb[1];
    pos->y = client->network->zappy->y + client->block->y - (nb[0] / 2);
    up[1] = 1;
  }
  else if (client->direction == 3)
  {
    pos->x = client->network->zappy->x + client->block->x + (nb[0] / 2);
    pos->y = client->network->zappy->y + client->block->y + nb[1];
    up[0] = -1;
  }
  else
  {
    pos->x = client->network->zappy->x + client->block->x - nb[1];
    pos->y = client->network->zappy->y + client->block->y + (nb[0] / 2);
    up[1] = -1;
  }
}

static size_t	get_nbr(t_case *block, size_t id)
{
  size_t	tmp;
  t_dlist	*list;

  if (id < 7)
    return (block->stock[id]);
  tmp = 0;
  for (list = block->players; list; list = list->next)
  {
    if (((t_client*)list->value)->parent == 0)
      tmp++;
  }
  return (tmp);
}

static void	fill_buffer(t_client *client, t_case *block,
			     char **buffer, size_t nb[3])
{
  int		tmp[3];
  size_t	id;
  size_t	number;

  for (id = 0; id < 8; id++)
  {
    tmp[1] = (nb[1] != 0 || nb[2] > 1) ? 0 : 1;
    tmp[2] = strlen(gl_name[id]);
    for (number = get_nbr(block, id); number; number--)
    {
      tmp[1] = (tmp[1] == tmp[2]) ? 0 : tmp[1];
      tmp[0] = snprintf(&(*buffer)[nb[2]], 510 - nb[2], &gl_name[id][tmp[1]]);
      tmp[0] = (tmp[0] > 509 - (int)nb[2]) ? 509 - (int)nb[2] : tmp[0];
      tmp[1] += tmp[0];
      nb[2] += tmp[0];
      if (nb[2] >= 500)
      {
        if (tmp[1] != tmp[2])
	  number++;
	add_packet_buffer_size(client->network->interface, *buffer, nb[2]);
	*buffer = get_buffer(512);
	nb[2] = 0;
      }
    }
  }
}

static void	voir_case(t_client *client, size_t nb[3],
			  char **buffer)
{
  t_coord	pos;
  t_coord	tmp;
  int		up[2];
  t_case	**block;
  size_t	i;

  up[0] = 0;
  up[1] = 0;
  tmp.z = 0;
  init_voir(client, nb, &pos, up);
  for (i = 0; i < nb[0]; i++)
  {
    tmp.x = pos.x % client->network->zappy->x;
    tmp.y = pos.y % client->network->zappy->y;
    if (nb[1] != 0 || i != 0)
      nb[2] += sprintf(&((*buffer)[nb[2]]), ",");
    block = (t_case**)find_octree(client->network->zappy->map, &tmp);
    if (block)
      fill_buffer(client, *block, buffer, nb);
    pos.x += up[0];
    pos.y += up[1];
  }
}

void		player_voir(t_list *list)
{
  size_t	nb[3];
  t_client	*client;
  char		*buffer;

  client = (t_client*)((t_action*)list->value)->client;
  nb[0] = 1;
  buffer = get_buffer(512);
  nb[2] = sprintf(buffer, "{");
  for (nb[1] = 0; nb[1] <= client->level; nb[1]++)
  {
    voir_case(client, nb, &buffer);
    nb[0] += 2;
  }
  nb[2] += sprintf(&buffer[nb[2]], "}\n");
  add_packet_buffer_size(client->network->interface, buffer, nb[2]);
}
