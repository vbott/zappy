/*
** main.c for zappy in /home/shotgun/projets/c/zappy/server_dir
**
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
**
** Started on  Thu Jun 16 17:01:51 CEST 2011 cerisier mickael
** Last update Thu Jun 16 17:01:51 CEST 2011 cerisier mickael
*/

#include <stdlib.h>
#include "server.h"

static t_pool	gl_pool_buffer_size;
static t_pool	gl_pool_512;
static t_pool	gl_pool_64;
static t_pool	gl_pool_12;

static void	*malloc_buffer(size_t size)
{
  t_buffer		*buffer;

  buffer = xmalloc(sizeof(*buffer) + (size * sizeof(char)));
  buffer->size = size;
  buffer->nb = 0;
  buffer->buffer = (char*)(buffer + 1);
  return (buffer);
}

inline t_list	*get_list(size_t *size)
{
  if (*size <= 12)
  {
    *size = 12;
    return (get_elem_pool(&gl_pool_12, 0));
  }
  else if (*size <= 64)
  {
    *size = 64;
    return (get_elem_pool(&gl_pool_64, 0));
  }
  else if (*size <= 512)
  {
    *size = 512;
    return (get_elem_pool(&gl_pool_512, 0));
  }
  else
  {
    *size = BUFFER_SIZE;
    return (get_elem_pool(&gl_pool_buffer_size, 0));
  }
}

char		*get_buffer(size_t size)
{
  t_list	*list;

  list = get_list(&size);
  if (list->value == NULL)
    list->value = malloc_buffer(size);
  ((t_buffer*)list->value)->nb++;
  return (((t_buffer*)list->value)->buffer);
}

void		release_buffer(char *buffer)
{
  t_buffer	*ptr;

  if (!buffer)
    return ;
  ptr = (t_buffer*)buffer - 1;
  ptr->nb--;
  if (ptr->nb == 0)
  {
    if (ptr->size == 12)
      release_elem_pool(&gl_pool_12, ptr, 0);
    else if (ptr->size == 64)
      release_elem_pool(&gl_pool_64, ptr, 0);
    else if (ptr->size == 512)
      release_elem_pool(&gl_pool_512, ptr, 0);
    else if (ptr->size == BUFFER_SIZE)
      release_elem_pool(&gl_pool_buffer_size, ptr, 0);
  }
}

inline void	get_same_buffer(char *buffer)
{
  if (buffer)
    ((t_buffer*)buffer - 1)->nb++;
}
