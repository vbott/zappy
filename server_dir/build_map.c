/*
** main.c for zappy in /home/shotgun/projets/c/zappy/server_dir
**
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
**
** Started on  Tue Jun 14 18:34:03 CEST 2011 cerisier mickael
** Last update Wed Jun 15 17:57:26 2011 gianni castellani
*/

#include <stdlib.h>
#include <string.h>
#include "server.h"

static const int	gl_nb[][2] = {
	{10, 5},
	{5, 2},
	{5, 2},
	{5, 2},
	{3, 1},
	{3, 1},
	{1, 1}
};

t_case			*get_case_map(t_zappy *zappy, size_t x, size_t y)
{
  t_case		**elem;
  t_case		*tmp;
  t_coord		coord;

  coord.x = x;
  coord.y = y;
  coord.z = 0;
  elem = (t_case**)zappy->map->find(zappy->map, &coord);
  if (!elem)
  {
    tmp = get_case();
    memset(tmp, 0, sizeof(*tmp));
    tmp->x = x;
    tmp->y = y;
    zappy->map->push(zappy->map, tmp, &coord);
    return tmp;
  }
  return *elem;
}

void			release_ressources(t_zappy *zappy, size_t inventory[7])
{
  int			i;
  t_case		*block;

  for (i = 1; i < 7; i++)
  {
    while (inventory[i])
    {
      block = get_case_map(zappy, rand() % zappy->x, rand() % zappy->y);
      block->stock[i]++;
      inventory[i]--;
    }
  }
}

static void		create_food(t_zappy *zappy, size_t nb)
{
  size_t		x;
  size_t		y;
  t_case		*elem;

  nb *= rand() % 11 + 10;
  for (; nb > 0; nb--)
  {
    x = rand() % zappy->x;
    y = rand() % zappy->y;
    elem = get_case(zappy, x, y);
    elem->stock[0] += rand() % 16 + 5;
  }
}

static void		create_mineral(t_zappy *zappy, size_t nb)
{
  size_t		tmp;
  size_t		i;
  t_case		*elem;

  for (i = 1; i < 7; i++)
  {
    if (i == 4)
      nb /= 2;
    for (tmp = nb; tmp > 0; tmp--)
    {
      elem = get_case_map(zappy, rand() % zappy->x, rand() % zappy->y);
      elem->stock[i] += (rand() % gl_nb[i][0]) + gl_nb[i][1];
    }
  }
}

void			build_map(t_zappy *zappy)
{
  int			nb;
  int			tmp;

  zappy->map = new_octree();
  nb = zappy->limit * zappy->nb_team;
  tmp = (zappy->x * zappy->y) / 10;
  if (tmp > nb)
    nb = tmp;
  create_food(zappy, nb);
  create_mineral(zappy, nb);
}
