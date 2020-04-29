/*
** main.c for zappy in /home/shotgun/projets/c/zappy/server_dir
**
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
**
** Started on  Tue Jun 14 21:21:42 CEST 2011 cerisier mickael
** Last update Tue Jun 14 21:21:42 CEST 2011 cerisier mickael
*/

#include <stdlib.h>
#include <string.h>
#include "server.h"

typedef struct
{
  char			*cmd;
  size_t		time;
  int			argument;
  void			(*func)(t_list*);
}		t_func;

static const t_func	gl_func[] = {
	{"avance", 7, 0, &player_avance},
	{"droite", 7, 0, &player_droite},
	{"gauche", 7, 0, &player_gauche},
	{"voir", 7, 0, &player_voir},
	{"inventaire", 1, 0, &player_inventaire},
	{"prend", 7, 1, &player_prend},
	{"pose", 7, 1, &player_pose},
	{"expulse", 7, 0, &player_expulse},
	{"broadcast", 7, 1, &player_broadcast},
	{"incantation", 0, 0, &player_incantation},
	{"fork", 42, 0, &player_fork},
	{"connect_nbr", 0, 0, &player_connect}
};

void		handle_player_action(t_zappy *zappy)
{
  t_action	*action;
  t_list	*list;
  char		*buffer;

  while (zappy->actions)
  {
    list = zappy->actions;
    action = (t_action*)list->value;
    if (action->cycle > zappy->cycle)
      return ;
    zappy->actions = list->next;
    buffer = action->buffer;
    if (!action->system)
    {
      list->next = ((t_client*)action->client)->actions;
      ((t_client*)action->client)->actions = list;
      if (((t_client*)action->client)->inventory[0] > 0)
        action->func(list);
    }
    else
      action->func(list);
    if (buffer)
      release_buffer(buffer);
  }
}

inline void	fill_buffer(char **buffer, char *argument)
{
  size_t	size;

  size = strlen(argument) + 1;
  *buffer = get_buffer(size);
  memcpy(*buffer, argument, size);
}

int		client_parse(char *line, void *arg)
{
  size_t	i;
  char		*argument;
  char		*buffer;

  buffer = NULL;
  argument = NULL;
  if (((t_client*)arg)->actions && ((t_client*)arg)->inventory[0])
  {
    strtok_r(line, " ", &argument);
    for (i = 0; i < sizeof(gl_func) / sizeof(t_func); i++)
    {
      if (strcmp(gl_func[i].cmd, line))
        continue ;
      if (gl_func[i].argument)
        fill_buffer(&buffer, argument);
      push_action((t_client*)arg, gl_func[i].time, gl_func[i].func, buffer);
      if (!gl_func[i].time)
        handle_player_action(((t_client*)arg)->network->zappy);
      return (0);
    }
  }
  add_packet(((t_client*)arg)->network->interface, KO);
  return (0);
}
