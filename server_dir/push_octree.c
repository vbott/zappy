/*
** push_octree.c for zappy in /home/castel_a//projets/c/zappy/server_dir
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Tue Jun 14 23:41:08 2011 gianni castellani
** Last update Wed Jun 15 17:31:52 2011 laurine taing
*/

#include "octree.h"

static t_node	*createParent(t_node *node)
{
  t_node	*newNode;
  t_coord	coord;
  unsigned int size;

  size = node->size + 1;
  coord.x = node->x >> size << size;
  coord.y = node->y >> size << size;
  coord.z = node->z >> size << size;
  newNode = new_node(0, &coord, size);
  newNode->addChild(newNode, node);
  return (newNode);
}

static t_node	*createChild(t_node *node, void *elem, t_coord *coord)
{
  t_node	*newNode;
  t_coord	tmp;
  unsigned int size;

  size = node->size - 1;
  tmp.x = coord->x >> size << size;
  tmp.y = coord->y >> size << size;
  tmp.z = coord->z >> size << size;
  newNode = new_node(elem, &tmp, size);
  node->addChild(node, newNode);
  return (newNode);
}

void		push_octree(struct s_octree *this, void *elem, t_coord *coord)
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
      while (!isContain(this->node[id], coord))
	this->node[id] = createParent(this->node[id]);
      node = this->node[id];
      while ((tmpNode = node->findChild(node, coord)) != 0)
	node = tmpNode;
      if (node->size > 0)
	{
	  while (node->size > 1)
	    node = createChild(node, 0, coord);
	  createChild(node, elem, coord);
	}
    }
  else
    this->node[id] = new_node(elem, coord, 0);
}
