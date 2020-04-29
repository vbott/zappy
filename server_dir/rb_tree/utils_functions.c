/*
** utils_functions.c for malloc in /home/shotgun/projets/malloc
** 
** Made by botton vivien
** Login   <botton_v@epitech.net>
** 
** Started on  Sun Feb 13 22:30:48 2011 botton vivien
** Last update Sun Feb 13 22:30:48 2011 botton vivien
*/

#include "tree.h"

t_rb_tree	*sibling(t_rb_tree *n)
{
  if (!n->parent)
    return NULL;
  return ((n == n->parent->left) ? n->parent->right : n->parent->left);
}

t_rb_tree	*grandparent(t_rb_tree *n)
{
  return ((n && n->parent) ? n->parent->parent : NULL);
}

t_rb_tree	*uncle(t_rb_tree *n)
{
  t_rb_tree		*g;

  g = grandparent(n);
  if (!g)
    return NULL;
  return ((n->parent == g->left) ? g->right : g->left);
}

t_rb_tree		*find_node(size_t size, t_tree *tree)
{
  t_rb_tree		*tmp;

  tmp = tree->root;
  while (tmp)
    {
      if (tmp->size == size)
	return (tmp);
      tmp = (size > tmp->size) ? tmp->right : tmp->left;
    }
  return (tmp);
}

t_rb_tree		*find_parent(size_t size, t_rb_tree *tree)
{
  t_rb_tree		*tmp;
  t_rb_tree		*prev;

  prev = NULL;
  tmp = tree;
  while (tmp)
    {
      prev = tmp;
      tmp = (size > tmp->size) ? tmp->right : tmp->left;
    }
  return (prev);
}
