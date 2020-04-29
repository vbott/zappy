/*
** change_parent.c for malloc in /home/shotgun/projets/malloc
** 
** Made by botton vivien
** Login   <botton_v@epitech.net>
** 
** Started on  Sat Feb 12 15:50:31 2011 botton vivien
** Last update Sat Feb 12 15:50:31 2011 botton vivien
*/

#include "tree.h"

void		change_parent(t_rb_tree *n, t_rb_tree *new,
				      t_rb_tree **tree)
{
  if (!n->parent)
    *tree = new;
  else if (n->parent->left == n)
    n->parent->left = new;
  else
    n->parent->right = new;
}

void		change_parent_2(t_rb_tree *n, t_rb_tree *new,
					t_rb_tree **tree)
{
  if (!n->parent)
    *tree = n;
  else if (n->parent->left == new)
    n->parent->left = n;
  else
    n->parent->right = n;
}
