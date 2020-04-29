/*
** delete.c for malloc in /home/shotgun/projets/malloc
** 
** Made by botton vivien
** Login   <botton_v@epitech.net>
** 
** Started on  Thu Feb  3 15:03:53 2011 botton vivien
** Last update Thu Feb  3 15:03:53 2011 botton vivien
*/

#include <stdlib.h>
#include "tree.h"

static inline void	change_ptr(t_rb_tree *n, t_tree *rb_tree)
{
  if (n->prev)
    n->prev->next = n->next;
  if (n->next)
    n->next->prev = n->prev;
  else
    rb_tree->last = n->prev;
}

void			delete_node(t_rb_tree *n, t_tree *rb_tree)
{
  t_rb_tree		*child;

  change_ptr(n, rb_tree);
  if (n->right && n->left)
    swap_node(n, &rb_tree->root);
  child = (n->right) ? n->right : n->left;
  if (child)
    replace_node(n, child, &rb_tree->root);
  else
    child = n;
  if (n->color == BLACK)
    {
      if (child->color == RED)
	child->color = BLACK;
      else
      	delete_case1(child, &rb_tree->root);
    }
  change_parent(n, NULL, &rb_tree->root);
  free(n);
}
