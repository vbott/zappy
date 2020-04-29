/*
** system_actions for zappy in /home/snap/projects/zappy/server_dir
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Thu 16 Jun 2011 07:17:01 PM CEST botton vivien
** Last update Thu 16 Jun 2011 07:17:01 PM CEST botton vivien
*/

#include <stdio.h>
#include <stdlib.h>
#include "server.h"

void		hungry(t_list *node)
{
  t_action	*action;
  t_client	*client;

  action = (t_action*)node->value;
  client = (t_client*)action->client;
  client->inventory[0]--;
  if (client->inventory[0] == 0)
  {
    free_player(action->client);
    free(node->value);
    free(node);
    return ;
  }
  action->cycle += EAT;
  sorted_insert(&client->network->zappy->actions, node, cmp_action);
}

void		restore_food(t_list *node)
{
  t_action	*action;
  t_zappy	*zappy;
  t_case	*block;
  int		nb;

  action = (t_action*)node->value;
  zappy = (t_zappy*)action->client;
  nb = (zappy->nbplayers * zappy->x * zappy->y / 10) - zappy->bread;
  for (; nb > 0; nb--)
  {
    block = get_case_map(zappy, rand() % zappy->x, rand() % zappy->y);
    block->stock[0] += 1;
    zappy->bread++;
    broadcast_monitor_value(zappy, NULL, block, &bct2);
  }
  action->cycle += EAT;
  sorted_insert(&zappy->actions, node, cmp_action);
}
