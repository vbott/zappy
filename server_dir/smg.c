/*
** smg for zappy in /home/snap/projects/zappy/server_dir
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sun 10 Jul 2011 04:59:50 PM CEST botton vivien
** Last update Sun 10 Jul 2011 04:59:50 PM CEST botton vivien
*/

#include <string.h>
#include <sys/epoll.h>
#include "server.h"

static int		read_stdin(char *line, void *arg)
{
  broadcast_monitor_msg(arg, NULL, line, &smg);
  return (0);
}

void 			init_stdin(t_zappy *zappy)
{
  t_interface           *tmp;

  set_non_blocking(STDIN_FILENO);
  tmp = xmalloc(sizeof(*tmp));
  memset(tmp, 0, sizeof(*tmp));
  tmp->read = &circular_buffer;
  tmp->userdata = zappy;
  tmp->parsing = &read_stdin;
  tmp->arg = zappy;
  tmp->buffer = get_buffer(BUFFER_SIZE);
  add_interface(zappy, tmp, STDIN_FILENO, EPOLLIN);
}
