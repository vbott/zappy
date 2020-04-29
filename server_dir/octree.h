/*
** Octree.h for zappy in /home/castel_a//projets/c/zappy/server_dir
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Tue Jun 14 23:43:12 2011 gianni castellani
** Last update Wed Jun 15 17:18:15 2011 laurine taing
*/

#ifndef _OCTREE_H_
# define _OCTREE_H_

# define ABS(x) (((x) < 0) ? (-x) : (x))

#include <unistd.h>

typedef struct s_coord
{
  int		x;
  int		y;
  int		z;
}		t_coord;

typedef struct	s_node
{
  void	*elem;
  int	x;
  int	y;
  int	z;
  unsigned int size;
  unsigned int nbChilds;
  struct s_node *lastChild;
  struct s_node *childs[8];

  void (*addChild)(struct s_node *, struct s_node *);
  struct s_node *(*findChild)(struct s_node *, t_coord *coord);
  void (*delChild)(struct s_node *, t_coord *coord);
}		t_node;

t_node	*new_node(void *elem, t_coord *coord, unsigned int size);

typedef struct	s_octree
{
  t_node *node[8];

  void (*push)(struct s_octree *, void *elem, t_coord *coord);
  void (*pop)(struct s_octree *, t_coord *coord);
  void **(*find)(struct s_octree *, t_coord *coord);
}		t_octree;

t_octree	*new_octree();
void		del_octree(t_octree *);

void		push_octree(struct s_octree *this, void *elem, t_coord *coord);
void		pop_octree(struct s_octree *this, t_coord *coord);
void		**find_octree(struct s_octree *this, t_coord *coord);
void		*find_in_map(t_octree *octree, int x, int y);

int		findOctreeId(t_coord *coord);
int		isContain(t_node *node, t_coord *coord);

void		*xmalloc(size_t);

#endif /* !_OCTREE_H_ */
