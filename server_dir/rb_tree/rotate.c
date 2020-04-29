/*
** rotate.c for malloc in /home/shotgun/projets/malloc
** 
** Made by botton vivien
** Login   <botton_v@epitech.net>
** 
** Started on  Sun Feb 13 23:00:27 2011 botton vivien
** Last update Sun Feb 13 23:00:27 2011 botton vivien
*/

#include "tree.h"

extern t_rb_tree	*gl_tree;

void		rotate_right(t_rb_tree *pivot, t_rb_tree **tree)
{
  t_rb_tree	*root;

  root = pivot->parent;
  root->left = pivot->right;
  if (pivot->right)
    pivot->right->parent = root;
  pivot->parent = root->parent;
  root->parent = pivot;
  pivot->right = root;
  if (!pivot->parent)
    *tree = pivot;
  else if (pivot->parent->left == root)
    pivot->parent->left = pivot;
  else
    pivot->parent->right = pivot;
}

void		rotate_left(t_rb_tree *pivot, t_rb_tree **tree)
{
  t_rb_tree	*root;

  root = pivot->parent;
  root->right = pivot->left;
  if (pivot->left)
    pivot->left->parent = root;
  pivot->parent = root->parent;
   root->parent = pivot;
  pivot->left = root;
  if (!pivot->parent)
    *tree = pivot;
  else if (pivot->parent->right == root)
    pivot->parent->right = pivot;
  else
    pivot->parent->left = pivot;
}
