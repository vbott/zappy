/*
** args for zappy in /home/snap/projects/zappy/server_dir
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Tue 14 Jun 2011 02:21:26 PM CEST botton vivien
** Last update Tue 14 Jun 2011 02:21:26 PM CEST botton vivien
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "server.h"

int	x_arg(int ac, char **av, t_zappy *zappy)
{
  (void)ac;
  zappy->x = strtol(av[0], NULL, 10);
  if (zappy->x < 1)
    return (fprintf(stderr, "X must be at least 1\n"));
  return (0);
}

int	y_arg(int ac, char **av, t_zappy *zappy)
{
  (void)ac;
  zappy->y = strtol(av[0], NULL, 10);
  if (zappy->y < 1)
    return (fprintf(stderr, "Y must be at least 1\n"));
  return (0);
}

int	port(int ac, char **av, t_zappy *zappy)
{
  int	p;

  (void)ac;
  p = strtol(av[0], NULL, 10);
  if (p < 1 && p > 65535)
    return (fprintf(stderr, "port must be in range [1-65535]\n"));
  zappy->port = av[0];
  return (0);
}
