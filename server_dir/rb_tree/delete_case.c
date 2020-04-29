/*
** delete_case.c for malloc in /home/shotgun/projets/malloc
** 
** Made by botton vivien
** Login   <botton_v@epitech.net>
** 
** Started on  Sun Feb 13 22:01:22 2011 botton vivien
** Last update Sun Feb 13 22:01:22 2011 botton vivien
*/

#include "tree.h"

static void		delete_case4(t_rb_tree *n, t_rb_tree **tree)
{
  t_rb_tree	*s;

  s = sibling(n);
  if (s)
    {
      s->color = n->parent->color;
      n->parent->color = BLACK;
      if (n == n->parent->left)
	{
	  if (s->right)
	    s->right->color = BLACK;
	  rotate_left(s, tree);
	}
      else
	{
	  if (s->left)
	    s->left->color = BLACK;
	  rotate_right(s, tree);
	}
    }
}

static void		delete_case3(t_rb_tree *n, t_rb_tree **tree)
{
  t_rb_tree	*s;

  s = sibling(n);
  if (s && s->color == BLACK)
    {
      if (n == n->parent->left && (!s->right || s->right->color == BLACK) &&
	  s->left && s->left->color == RED)
	{
	  s->color = RED;
	  s->left->color = BLACK;
	  rotate_right(s->left, tree);
	}
      else if (n == n->parent->right &&
	       (!s->left || s->left->color == BLACK) &&
	       s->right && s->right->color == RED)
	{
	  s->color = RED;
	  s->right->color = BLACK;
	  rotate_left(s->right, tree);
	}
    }
  delete_case4(n, tree);
}

static void		delete_case2(t_rb_tree *n, t_rb_tree **tree)
{
  t_rb_tree	*s;

  s = sibling(n);
  if (n->parent->color == BLACK && s && s->color == BLACK &&
      (!s->left || s->left->color == BLACK) &&
      (!s->right || s->right->color == BLACK))
    {
      s->color = RED;
      delete_case1(n->parent, tree);
    }
  else
    {
      s = sibling(n);
      if (n->parent->color == RED && s && s->color == BLACK &&
	  (!s->left || s->left->color == BLACK) &&
	  (!s->right || s->right->color == BLACK))
	{
	  s->color = RED;
	  n->parent->color = BLACK;
	}
      else
	delete_case3(n, tree);
    }
}

void			delete_case1(t_rb_tree *n, t_rb_tree **tree)
{
  t_rb_tree	*s;

  if (n->parent == NULL)
    return ;
  s = sibling(n);
  if (s && s->color == RED)
    {
      n->parent->color = RED;
      s->color = BLACK;
      if (n == n->parent->left)
	rotate_left(s, tree);
      else
	rotate_right(s, tree);
    }
  delete_case2(n, tree);
}
