/*
** main for zappy in /home/snap/projects/zappy/server_dir
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Mon 13 Jun 2011 04:00:37 PM CEST botton vivien
** Last update Mon 13 Jun 2011 04:00:37 PM CEST botton vivien
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "server.h"

int		main(int ac, char **av)
{
  t_zappy	zappy;
  int		ret;

  srand(time(NULL));
  default_value(&zappy);
  ret = handle_args(ac, av, &zappy);
  if (!ret && !init(&zappy))
    network_loop(&zappy);
  if (ret)
    fprintf(stderr, "usage: %s [-x nb] [-y nb] [-t time] \
[-p port] [-c nb_player] -n team ...\n", av[0]);
  return (0);
}
