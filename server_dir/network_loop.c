/*
** main.c for zappy in /home/shotgun/projets/c/zappy/server_dir
**
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
**
** Started on  Tue Jun 21 19:29:26 CEST 2011 cerisier mickael
** Last update Tue Jun 21 19:29:26 CEST 2011 cerisier mickael
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/epoll.h>
#define _GNU_SOURCE
#include <sys/socket.h>
#include "server.h"

int			choose_type(char *line, void *arg)
{
  t_zappy		*zappy;
  t_list		*tmp;
  t_team		*team;

  zappy = (t_zappy*)(((t_interface*)arg)->userdata);
  if (!strcmp(line, "GRAPHIC"))
    add_monitor(zappy, (t_interface*)arg);
  else
  {
    for (tmp = zappy->teams; tmp; tmp = tmp->next)
    {
      team = (t_team*)tmp->value;
      if (!strcmp(team->name, line))
	break ;
    }
    if (tmp && team->nb_player < team->nb_max)
      add_client(zappy, team, (t_interface*)arg);
    else
    {
      close_interface((t_interface*)arg);
      return (1);
    }
  }
  return (0);
}

static int		getElapsedTime(int update)
{
  static struct timeval	tp;
  struct timeval tmp;

  if (update)
  {
    gettimeofday(&tp, NULL);
    return (0);
  }
  else
  {
    gettimeofday(&tmp, NULL);
    return ((tmp.tv_sec * 1000 + tmp.tv_usec / 1000)
		    - (tp.tv_sec * 1000 + tp.tv_usec / 1000));
  }
}

static void		treat_fd(int retval, struct epoll_event *events)
{
  int			i;
  t_interface           *tmp;

  for (i = 0; i < retval; i++)
  {
    tmp = (t_interface*) events[i].data.ptr;
    if (events[i].events & EPOLLHUP && tmp->hangup)
      tmp->hangup(tmp);
    else
    {
      if (events[i].events & EPOLLOUT && tmp->write)
        tmp->write(tmp);
      if (events[i].events & EPOLLIN && tmp->read)
        tmp->read(tmp);
    }
  }
}

void			network_loop(t_zappy *zappy)
{
  int           	retval;
  struct epoll_event 	events[100];
  int			diff;
  int			towait;

  retval = 0;
  towait = 1000 / zappy->t;
  getElapsedTime(1);
  while (retval != -1)
  {
    retval = epoll_wait(zappy->epoll_fd, events, 100, towait);
    treat_fd(retval, events);
    diff = getElapsedTime(0);
    getElapsedTime(1);
    towait -= diff;
    if (towait <= 0 && zappy->t > 0)
    {
      zappy->cycle++;
      handle_player_action(zappy);
      diff = 1000 / zappy->t;
      towait = (towait < diff) ? diff : towait + diff;
    }
    else if (zappy->t == 0)
      towait = -1;
  }
}
