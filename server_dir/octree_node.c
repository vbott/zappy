/*
** Octree.c for zappy in /home/castel_a//projets/c/zappy
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Tue Jun 14 17:04:10 2011 gianni castellani
** Last update Wed Jun 15 17:10:17 2011 laurine taing
*/

#include <stdlib.h>
#include <string.h>
#include "octree.h"

static void	addChild(struct s_node *this, struct s_node *node)
{
  int x;
  int y;
  int z;

  x = (node->x - this->x) >> node->size;
  y = (node->y - this->y) >> node->size;
  z = (node->z - this->z) >> node->size;
  this->childs[(x << 2) + (y << 1) + z] = node;
  this->lastChild = node;
  this->nbChilds++;
}

static t_node	*findChild(struct s_node *this, t_coord *coord)
{
  unsigned int size;
  int x2;
  int y2;
  int z2;

  if (this->size < 1)
    return (0);
  size = this->size - 1;
  x2 = ((coord->x >> size << size) - this->x) >> size;
  y2 = ((coord->y >> size << size) - this->y) >> size;
  z2 = ((coord->z >> size << size) - this->z) >> size;
  return (this->childs[(x2 << 2) + (y2 << 1) + z2]);
}

static void	find_new_last_child(t_node *this)
{
  int	i;

  for (i = 0; i < 8 && this->childs[i] == 0; ++i);
  if (i < 8)
    this->lastChild = this->childs[i];
}

static void	delChild(struct s_node *this, t_coord *coord)
{
  unsigned int size;
  int cpt;
  int x2;
  int y2;
  int z2;

  size = this->size - 1;
  x2 = ((coord->x >> size << size) - this->x) >> size;
  y2 = ((coord->y >> size << size) - this->y) >> size;
  z2 = ((coord->z >> size << size) - this->z) >> size;
  cpt = (x2 << 2) + (y2 << 1) + z2;
  if (this->childs[cpt] == this->lastChild)
    {
      this->childs[cpt] = 0;
      if (this->nbChilds == 1)
	this->lastChild = 0;
      else
	find_new_last_child(this);
    }
  else
    this->childs[cpt] = 0;
  this->nbChilds--;
}

t_node		*new_node(void *elem, t_coord *coord, unsigned int size)
{
  t_node *node;

  node = xmalloc(sizeof(*node));
  memset(node, 0, sizeof(*node));
  node->elem = elem;
  node->x = coord->x;
  node->y = coord->y;
  node->z = coord->z;
  node->size = size;
  node->addChild = &addChild;
  node->findChild = &findChild;
  node->delChild = &delChild;
  return (node);
}
