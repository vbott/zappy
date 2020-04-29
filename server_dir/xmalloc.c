/*
** xfunctions.c for kong in /home/audrade/work/epikong
**
** Made by cailleux carole
** Login   <caille_c@epitech.net>
**
** Started on  Fri Mar 25 21:43:33 2011 cailleux carole
** Last update Fri Mar 25 21:43:33 2011 cailleux carole
*/

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

void		*xmalloc(size_t size)
{
  void		*ret;

  ret = malloc(size);
  if (ret == NULL)
  {
    perror("malloc()");
    exit(errno);
  }
  return (ret);
}
