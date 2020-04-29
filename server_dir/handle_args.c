/*
** handle_args for zappy in /home/snap/projects/zappy/server_dir
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Thu 16 Jun 2011 01:11:47 PM CEST botton vivien
** Last update Thu 16 Jun 2011 01:11:47 PM CEST botton vivien
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

static const t_arg gl_arg[] = {
	{'x', x_arg},
	{'y', y_arg},
	{'p', port},
	{'c', limit},
	{'t', timevalue},
	{'n', teams}
};

void		add_team(char *name, t_zappy *zappy)
{
  t_team		*team;

  if (!strcmp("GRAPHIC", name))
  {
    fprintf(stderr, "name GRAPHIC forbidden\n");
    exit(EXIT_FAILURE);
  }
  team = xmalloc(sizeof(*team));
  memset(team, 0, sizeof(*team));
  if (strlen(name) > 64)
    name[64] = '\0';
  team->name = name;
  team->nb_max = zappy->limit;
  push_front(&zappy->teams, team);
  zappy->nb_team++;
}

int		handle_args(int ac, char **av, t_zappy *zappy)
{
  int			i;
  size_t		j;

  for (i = 1; i < ac; i++)
    if (av[i][0] == '-' && av[i][1] >= 'a' && av[i][1] <= 'z' && i + 1 < ac)
     for (j = 0; j < sizeof(gl_arg) / sizeof(t_arg); j++)
       if (av[i][1] == gl_arg[j].option)
       {
	 if (gl_arg[j].func(ac - i - 1, &av[i + 1], zappy))
	   return (1);
         break ;
       }
 if (zappy->x * zappy->y > 1000000)
 {
   fprintf(stderr, "Cannot generate over 1 million blocks\n");
   return (1);
 }
 if (zappy->nb_team < 2 || zappy->limit < 1)
 {
   fprintf(stderr, "2 or more teams with 1 player mininum is mandatory\n");
   return (1);
 }
 return (0);
}
