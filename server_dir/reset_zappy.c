/*
** main.c for zappy in /home/shotgun/projets/c/zappy/server_dir
**
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
**
** Started on  Sat Jul  9 23:58:34 CEST 2011 cerisier mickael
** Last update Sat Jul  9 23:58:34 CEST 2011 cerisier mickael
*/

#include <stdlib.h>
#include <string.h>
#include "server.h"

static void	reset_actions(t_zappy *zappy)
{
  t_action	*action;
  t_list	*tmp;

  while (zappy->actions)
  {
    tmp = zappy->actions->next;
    action = (t_action*)zappy->actions->value;
    if (action->buffer)
      release_buffer(action->buffer);
    free(action);
    free(zappy->actions);
    zappy->actions = tmp;
  }
}

static void	broadcast_map(t_zappy *zappy)
{
  int		x;
  int		y;
  t_case	block;
  t_case	*tmp;

  memset(&block, 0, sizeof(block));
  for (x = 0; x < zappy->x; x++)
  {
    for (y = 0; y < zappy->y; y++)
    {
      tmp = (t_case*)find_in_map(zappy->map, x, y);
      if (tmp)
	broadcast_monitor_value(zappy, NULL, tmp, &bct2);
      else
      {
	block.x = x;
	block.y = y;
	broadcast_monitor_value(zappy, NULL, &block, &bct2);
      }
    }
  }
}

static void	reset_teams(t_zappy *zappy)
{
  t_team	*team;
  t_list	*list;
  t_list	*tmp;

  for (list = zappy->teams; list; list = list->next)
  {
    team = (t_team*)list->value;
    while (team->egg)
    {
      tmp = team->egg->next;
      free(team->egg);
      team->egg = tmp;
    }
    memset(team, 0, sizeof(*team) - sizeof(team->name));
    team->nb_max = zappy->limit;
  }
}

void		reset_zappy(t_team *team, t_zappy *zappy)
{
  broadcast_monitor_msg(zappy, NULL, team->name, &seg);
  while (zappy->clients.last)
    free_player(zappy->clients.last->value);
  reset_teams(zappy);
  reset_actions(zappy);
  zappy->nbplayers = 0;
  zappy->cycle = 0;
  zappy->bread = 0;
  del_octree(zappy->map);
  build_map(zappy);
  broadcast_map(zappy);
  push_system_action_2(zappy, EAT, &restore_food, NULL);
}
