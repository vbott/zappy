/*
** delete_swap.c for malloc in /home/shotgun/projets/malloc
** 
** Made by botton vivien
** Login   <botton_v@epitech.net>
** 
** Started on  Fri Feb 11 14:24:06 2011 botton vivien
** Last update Fri Feb 11 14:24:06 2011 botton vivien
*/

#include <string.h>
#include "tree.h"

void			replace_node(t_rb_tree *n, t_rb_tree *child, t_rb_tree **tree)
{
  change_parent(n, child, tree);
  child->parent = n->parent;
  n->parent = child;
  if (n->left == child)
    {
      child->left = n;
      n->left = NULL;
    }
  else
    {
      child->right = n;
      n->right = NULL;
    }
}

static void		swap_node_2(t_rb_tree *n, t_rb_tree *node,
	       	t_rb_tree *tmp, t_rb_tree **tree)
{
  if (n == node->parent)
    {
      node->parent = tmp->parent;
      n->parent = node;
      node->left = n;
    }
  else
    {
      n->parent = node->parent;
      node->parent = tmp->parent;
      node->left = tmp->left;
      change_parent_2(n, node, tree);
    }
}

void			swap_node(t_rb_tree *n, t_rb_tree **tree)
{
  t_rb_tree		*node;
  t_rb_tree		tmp;

  node = n->left;
  while (node->right)
    node = node->right;
  memcpy(&tmp, n, sizeof(*n));
  n->right = node->right;
  n->left = node->left;
  node->right = tmp.right;
  n->color = node->color;
  node->color = tmp.color;
  swap_node_2(n, node, &tmp, tree);
  change_parent_2(node, n, tree);
  if (n->right)
    n->right->parent = n;
  if (n->left)
    n->left->parent = n;
  if (node->right)
    node->right->parent = node;
  if (node->left)
    node->left->parent = node;
}
