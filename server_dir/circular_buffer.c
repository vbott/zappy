/*
** circular_buffer for zappy in /home/snap/projects/zappy/server_dir
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Thu 16 Jun 2011 04:15:12 PM CEST botton vivien
** Last update Thu 16 Jun 2011 04:15:12 PM CEST botton vivien
*/

#include <string.h>
#include "server.h"

static int		parse_buffer(t_interface *network, int left)
{
  int                   i;
  char                  *current;
  char			*begin;
  int			lu;

  current = &network->buffer[network->index];
  if ((lu = read(network->socket, current, left)) <= 0)
    return ((lu != 0) ? -1 : -2);
  network->index += lu;
  begin = network->buffer;
  for (i = 0; i < lu; ++i)
   if (current[i] == '\n')
   {
     current[i] = '\0';
     if (!network->incorrect && network->parsing(begin, network->arg))
       return (-1);
     network->incorrect = 0;
     begin = current + i + 1;
   }
  if (begin != network->buffer &&
  (network->index = &current[lu] - begin))
    memmove(network->buffer, begin, network->index);
 return (0);
}

void			circular_buffer(t_interface *network)
{
  int			left;
  int			ret;

  left = BUFFER_SIZE - 1 - network->index;
  ret = 0;
  while (left > 0 && ret == 0)
  {
   ret = parse_buffer(network, left);
   if (!ret)
     left = BUFFER_SIZE - 1 - network->index;
  }
  if (!left && !ret)
  {
    if (!network->incorrect)
    {
      network->buffer[BUFFER_SIZE - 1] = '\0';
      network->parsing(network->buffer, network->arg);
    }
    network->index = 0;
    network->incorrect = 1;
  }
  if (ret == -2)
    network->hangup(network);
}
