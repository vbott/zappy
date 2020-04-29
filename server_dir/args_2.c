/*
** main.c for zappy in /home/shotgun/projets/c/zappy/server_dir
**
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
**
** Started on  Fri Jun 17 18:57:14 CEST 2011 cerisier mickael
** Last update Fri Jun 17 18:57:14 CEST 2011 cerisier mickael
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "server.h"

int		limit(int ac, char **av, t_zappy *zappy)
{
  t_list	*team;

  (void)ac;
  zappy->limit = strtol(av[0], NULL, 10);
  if (zappy->limit < 1)
    return (fprintf(stderr, "limit must be at least 1\n"));
  for (team = zappy->teams; team; team = team->next)
    ((t_team*)team->value)->nb_max = zappy->limit;
  return (0);
}

int		timevalue(int ac, char **av, t_zappy *zappy)
{
  (void)ac;
  zappy->t = strtol(av[0], NULL, 10);
  if (zappy->t < 1)
    return (fprintf(stderr, "t must be at least 1\n"));
  else if (zappy->t > 1000)
    return (fprintf(stderr, "t must be less than 1000\n"));
  return (0);
}

int		teams(int ac, char **av, t_zappy *zappy)
{
  int	i;

  for (i = 0; i < ac && av[i][0] != '-'; i++)
  {
   add_team(av[i], zappy);
  }
  return (0);
}
