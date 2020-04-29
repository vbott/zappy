/*
** Octree.c for zappy in /home/castel_a//projets/c/zappy/server_dir
**
** Made by gianni castellani
** Login   <castel_a@epitech.net>
**
** Started on  Tue Jun 14 23:27:19 2011 gianni castellani
** Last update Wed Jun 15 17:50:44 2011 gianni castellani
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "octree.h"

int		findOctreeId(t_coord *coord)
{
  int x2;
  int y2;
  int z2;

  x2 = coord->x >> 31 & 1;
  y2 = coord->y >> 31 & 1;
  z2 = coord->z >> 31 & 1;
  return ((x2 << 2) + (y2 << 1) + z2);
}

int		isContain(t_node *node, t_coord *coord)
{
  int size;

  size = 1 << node->size;
  return (coord->x >= node->x && coord->x < node->x + size &&
	  coord->y >= node->y && coord->y < node->y + size &&
	  coord->z >= node->z && coord->z < node->z + size);
}

t_octree	*new_octree()
{
  t_octree *octree;

  octree = xmalloc(sizeof(*octree));
  memset(octree, 0, sizeof(*octree));
  octree->push = &push_octree;
  octree->pop = &pop_octree;
  octree->find = &find_octree;
  return (octree);
}

static void	freeOctree(t_node *node)
{
  unsigned int cpt;
  unsigned int nbChilds;

  for (nbChilds = cpt = 0; cpt < 8 && nbChilds < node->nbChilds; ++cpt)
    {
      if (node->childs[cpt])
	{
	  freeOctree(node->childs[cpt]);
	  ++nbChilds;
	}
    }
  free(node);
}

void		del_octree(t_octree *this)
{
  int cpt;

  for (cpt = 0; cpt < 8; cpt++)
    {
      if (this->node[cpt])
	freeOctree(this->node[cpt]);
    }
  free(this);
}
