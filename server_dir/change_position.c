/*
** main.c for zappy in /home/shotgun/projets/c/zappy/server_dir
**
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
**
** Started on  Thu Jun 16 22:25:27 CEST 2011 cerisier mickael
** Last update Thu Jun 16 22:25:27 CEST 2011 cerisier mickael
*/

#include "server.h"

static void	add_in_octree(t_octree *octree, t_client *client,
			      t_coord *coord)
{
  t_case	*tmp;
  t_case	**block;

  block = (t_case**)octree->find(octree, coord);
  if (block)
  {
    tmp = *block;
    if (tmp->players)
    {
      client->node.next = tmp->players;
      tmp->players->prev = &client->node;
      tmp->players = &client->node;
    }
    else
      tmp->players = &client->node;
  }
  else
  {
    tmp = get_case();
    tmp->x = coord->x;
    tmp->y = coord->y;
    tmp->players = &client->node;
    octree->push(octree, tmp, coord);
  }
  client->block = tmp;
}

static void	remove_in_octree(t_octree *octree, t_client *client,
				 t_coord *coord)
{
  t_case	*block;

  block = client->block;
  if (block->players->next == NULL && block->stock[0] == 0 &&
      block->stock[1] == 0 && block->stock[2] == 0 &&
      block->stock[3] == 0 && block->stock[4] == 0 &&
      block->stock[5] == 0 && block->stock[6] == 0)
  {
    release_case(block);
    octree->pop(octree, coord);
  }
  else
  {
    if (client->node.prev)
      client->node.prev->next = client->node.next;
    if (client->node.next)
      client->node.next->prev = client->node.prev;
    if (block->players->value == client)
      block->players = client->node.next;
    client->node.prev = NULL;
    client->node.next = NULL;
  }
}

void		change_position(t_client *client, int x, int y)
{
  t_coord	coord;
  t_zappy	*zappy;
  t_octree	*octree;

  zappy = client->network->zappy;
  octree = zappy->map;
  coord.z = 0;
  if (client->block)
  {
    coord.x = client->block->x;
    coord.y = client->block->y;
    remove_in_octree(octree, client, &coord);
  }
  if (x < 0)
    x = zappy->x - 1;
  else if (x >= zappy->x)
    x = 0;
  if (y < 0)
    y = zappy->y - 1;
  else if (y >= zappy->y)
    y = 0;
  coord.x = x;
  coord.y = y;
  add_in_octree(octree, client, &coord);
}
