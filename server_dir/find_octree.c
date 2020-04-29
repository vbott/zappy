/*
** find_octree.c for zappy in /home/castel_a//projets/c/zappy/server_dir
**
** Made by gianni castellani
** Login   <castel_a@epitech.net>
**
** Started on  Tue Jun 14 23:39:29 2011 gianni castellani
** Last update Wed Jun 15 17:18:53 2011 laurine taing
*/

#include "octree.h"

void		*find_in_map(t_octree *octree, int x, int y)
{
  t_coord	coord;
  void		**block;

  coord.x = x;
  coord.y = y;
  coord.z = 0;
  block = find_octree(octree, &coord);
  if (block)
    return (*block);
  return (NULL);
}

void		**find_octree(struct s_octree *this, t_coord *coord)
{
  int id;
  t_node *node;

  id = findOctreeId(coord);
  coord->x = ABS(coord->x);
  coord->y = ABS(coord->y);
  coord->z = ABS(coord->z);
  if (this->node[id])
    {
      node = this->node[id];
      if (isContain(node, coord))
	{
	  while (node->size)
	    {
	      node = node->findChild(node, coord);
	      if (!node)
		return (0);
	    }
	  if (isContain(node, coord))
	    return (&node->elem);
	}
    }
  return (0);
}
