/*
** insert.c for malloc in /home/shotgun/projets/malloc
** 
** Made by botton vivien
** Login   <botton_v@epitech.net>
** 
** Started on  Sat Feb 12 14:22:40 2011 botton vivien
** Last update Sat Feb 12 14:22:40 2011 botton vivien
*/

#include <stdlib.h>
#include "tree.h"

static void		insert_case3(t_rb_tree *n, t_rb_tree **tree)
{
  t_rb_tree		*g;

  g = grandparent(n);
  if ((n == n->parent->right) && (n->parent == g->left))
    {
      rotate_left(n, tree);
      n = n->left;
    }
  else if ((n == n->parent->left) && (n->parent == g->right))
    {
      rotate_right(n, tree);
      n = n->right;
    }
  g = grandparent(n);
  if (n->parent)
    n->parent->color = BLACK;
  g->color = RED;
  if ((n == n->parent->left) && (n->parent == g->left))
    rotate_right(n->parent, tree);
  else
    rotate_left(n->parent, tree);
}

static void		insert_case2(t_rb_tree *n, t_rb_tree **tree)
{
  t_rb_tree		*u;
  t_rb_tree		*g;

  u = uncle(n);
  if (u && u->color == RED)
    {
      n->parent->color = BLACK;
      u->color = BLACK;
      g = grandparent(n);
      g->color = RED;
      insert_node(g, tree);
    }
  else
    insert_case3(n, tree);
}

void			insert_node(t_rb_tree *n, t_rb_tree **tree)
{
  if (n->parent == NULL)
    {
      n->color = BLACK;
      *tree = n;
    }
  else
    {
      if (n->parent->size > n->size)
  	n->parent->left = n;
      else
  	n->parent->right = n;
      if (n->parent->color == RED)
      	insert_case2(n, tree);
    }
}

void			insert_node2(size_t id, void *value, t_tree *tree)
{
  t_rb_tree		*node;

  node = malloc(sizeof(*node));
  if (!node)
   return ;
  node->parent = find_parent(id, tree->root);
  node->left = NULL;
  node->right = NULL;
  node->size = id;
  node->value = value;
  node->color = RED;
  node->next = NULL;
  node->prev = tree->last;
  if (tree->last)
    tree->last->next = node;
  tree->last = node;
  insert_node(node, &tree->root);
}
