/*
** pop_octree.c for zappy in /home/castel_a//projets/c/zappy/server_dir
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Tue Jun 14 23:40:57 2011 gianni castellani
** Last update Wed Jun 15 17:23:34 2011 laurine taing
*/

#include <stdlib.h>
#include "octree.h"

static void	delBranch(t_node **tree, t_node *node, t_coord *coord)
{
  t_node *tmpNode;

  if (node->size == 0)
    {
      free(*tree);
      *tree = 0;
      return ;
    }
  tmpNode = node->findChild(node, coord);
  node->delChild(node, coord);
  node = tmpNode;
  while (node->size)
    {
      tmpNode = node->lastChild;
      free(node);
      node = tmpNode;
    }
  free(node);
  while ((*tree)->nbChilds == 1)
    {
      node = *tree;
      *tree = (*tree)->lastChild;
      free(node);
    }
}

static t_node	*find_node_to_del(t_node *node, t_node **tmpNode,
				  t_coord *coord)
{
  while (node->size)
    {
      if (node->nbChilds > 1)
	*tmpNode = node;
      node = node->findChild(node, coord);
      if (!node)
	return (NULL);
    }
  return (node);
}

void		pop_octree(struct s_octree *this, t_coord *coord)
{
  int id;
  t_node *node;
  t_node *tmpNode;

  id = findOctreeId(coord);
  coord->x = ABS(coord->x);
  coord->y = ABS(coord->y);
  coord->z = ABS(coord->z);
  if (this->node[id])
    {
      node = this->node[id];
      tmpNode = 0;
      if (isContain(node, coord))
	{
	  node = find_node_to_del(node, &tmpNode, coord);
	  if (node && isContain(node, coord))
	    {
	      if (tmpNode)
		delBranch(this->node + id, tmpNode, coord);
	      else
		delBranch(this->node + id, this->node[id], coord);
	    }
	}
    }
}
