/*
** main.c for zappy in /home/shotgun/projets/c/zappy/server_dir
**
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
**
** Started on  Thu Jun 16 18:44:41 CEST 2011 cerisier mickael
** Last update Thu Jun 16 18:44:41 CEST 2011 cerisier mickael
*/

#include "server.h"

void		player_avance(t_list *list)
{
  t_client	*client;
  int		pos[2];

  client = (t_client*)((t_action*)list->value)->client;
  pos[0] = client->block->x;
  pos[1] = client->block->y;
  if (client->direction == 1)
    pos[1]--;
  else if (client->direction == 2)
    pos[0]++;
  else if (client->direction == 3)
    pos[1]++;
  else
    pos[0]--;
  change_position(client, pos[0], pos[1]);
  add_packet(client->network->interface, OK);
  broadcast_monitor(client->network->zappy, client, ppo2);
}

void		player_droite(t_list *list)
{
  t_client	*client;

  client = (t_client*)((t_action*)list->value)->client;
  client->direction++;
  if (client->direction > 4)
    client->direction = 1;
  add_packet(client->network->interface, OK);
  broadcast_monitor(client->network->zappy, client, ppo2);
}

void		player_gauche(t_list *list)
{
  t_client	*client;

  client = (t_client*)((t_action*)list->value)->client;
  client->direction--;
  if (client->direction <= 0)
    client->direction = 4;
  add_packet(client->network->interface, OK);
  broadcast_monitor(client->network->zappy, client, ppo2);
}
