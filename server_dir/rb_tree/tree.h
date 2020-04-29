/*
** malloc.h for malloc in /home/snap/projects/malloc
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Wed Feb  2 14:33:20 2011 botton vivien
** Last update Wed Feb  2 14:33:20 2011 botton vivien
*/

#ifndef		_MALLOC_H_
# define	_MALLOC_H_

#include <unistd.h>

# define BLACK 1
# define RED 0

typedef struct		s_rb_tree
{
  struct s_rb_tree	*parent;
  struct s_rb_tree	*left;
  struct s_rb_tree	*right;
  struct s_rb_tree      *next;
  struct s_rb_tree      *prev;
  size_t		size;
  void			*value;
  int			color;
}			t_rb_tree;

typedef struct		s_tree
{
 t_rb_tree		*root;
 t_rb_tree		*last;
}			t_tree;

inline t_rb_tree	*grandparent(t_rb_tree *n);
inline t_rb_tree	*uncle(t_rb_tree *n);
inline t_rb_tree	*sibling(t_rb_tree *n);

/* change_parent.c */
inline void		change_parent(t_rb_tree *n, t_rb_tree *new,
	       	t_rb_tree **tree);
inline void		change_parent_2(t_rb_tree *n, t_rb_tree *new,
		t_rb_tree **tree);

/* delete.c */
void			delete_node(t_rb_tree *n, t_tree *tree);

/* delete_case.c */
void			delete_case1(t_rb_tree *n, t_rb_tree **tree);

/* delete_swap.c */
void			replace_node(t_rb_tree *n, t_rb_tree *child,
	       	t_rb_tree **tree);
void			swap_node(t_rb_tree *n, t_rb_tree **tree);

/* insert.c */
void			insert_node(t_rb_tree *n, t_rb_tree **tree);
void			insert_node2(size_t id, void *value, t_tree *tree);

/* rotate.c */
void			rotate_right(t_rb_tree *pivot, t_rb_tree **tree);
void			rotate_left(t_rb_tree *pivot, t_rb_tree **tree);

/* utils_functions.c */
inline t_rb_tree	*sibling(t_rb_tree *n);
inline t_rb_tree	*grandparent(t_rb_tree *n);
inline t_rb_tree	*uncle(t_rb_tree *n);
t_rb_tree		*find_node(size_t size, t_tree *tree);
t_rb_tree		*find_parent(size_t size, t_rb_tree *tree);

#endif		/* _MALLOC_H_ */
