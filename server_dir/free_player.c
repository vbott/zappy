/*
** free_player for zappy in /home/snap/projects/zappy/server_dir
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sun 19 Jun 2011 07:11:42 PM CEST botton vivien
** Last update Sun 19 Jun 2011 07:11:42 PM CEST botton vivien
*/

#include <stdlib.h>
#include <sys/epoll.h>
#include "server.h"

static void		cancel_action_player(t_client *client)
{
  t_list		*tmp;
  t_list		*prev;
  t_list		*cpy;

  prev = NULL;
  for (tmp = client->network->zappy->actions; tmp; )
  {
    if (((t_action*)tmp->value)->client == client)
    {
      if (!prev)
       client->network->zappy->actions = tmp->next;
      else
       prev->next = tmp->next;
      cpy = tmp->next;
      if (((t_action*)tmp->value)->buffer)
       release_buffer(((t_action*)tmp->value)->buffer);
      push_front_node(&client->actions, tmp);
      tmp = cpy;
    }
    else
    {
      prev = tmp;
      tmp = tmp->next;
    }
  }
}

static void		remove_player_in_team(t_client *client)
{
  t_list		*tmp;
  t_list		*list;

  tmp = NULL;
  for (list = client->team->client; list; list = list->next)
  {
    if (list->value == client)
    {
      if (!tmp)
	client->team->client = list->next;
      else
	tmp->next = list->next;
      if (!list->next)
       client->team->lastclient = tmp;
      free(list);
      return ;
    }
    tmp = list;
  }
}

static void		remove_client(t_client *client)
{
  broadcast_monitor(client->network->zappy, client,
    		    (client->parent) ? &edi : &pdi);
  release_ressources(client->network->zappy, client->inventory);
  if (!client->node.prev)
    client->block->players = client->block->players->next;
  else
    client->node.prev->next = client->node.next;
  if (client->node.next)
    client->node.next->prev = client->node.prev;
  client->node.prev = NULL;
  client->node.next = NULL;
  if (client->level == 8)
    client->team->nbhl--;
  if (!client->parent)
    client->network->zappy->nbplayers--;
  if (client->team->nb_player > client->network->zappy->limit)
    client->team->nb_max--;
  remove_player_in_team(client);
}

void			free_player(t_client *client)
{
  t_list		*mem;
  t_list		*cpy;
  t_rb_tree		*node;

  mem = NULL;
  remove_client(client);
  cancel_action_player(client);
  for (cpy = client->actions; cpy; )
  {
    mem = cpy;
    cpy = cpy->next;
    free(mem->value);
    free(mem);
  }
  client->actions = NULL;
  node = find_node(client->id, &client->network->zappy->clients);
  if (node)
    delete_node(node, &client->network->zappy->clients);
  if (client->network->interface)
  {
    write(client->network->interface->socket, "mort\n", 5);
    close_client(client->network->interface);
  }
  free(client->network);
  free(client);
}

void			close_client(t_interface *interface)
{
  t_client		*client;
  t_list		*list;

  client = (t_client*)interface->userdata;
  if (client->team->nb_player > 0)
    client->team->nb_player--;
  if (client->inventory[0] && !client->parent)
  {
    list = xmalloc(sizeof(*list));
    list->value = client;
    list->next = NULL;
    if (client->team->lastclient)
      client->team->lastclient->next = list;
    else
      client->team->client = list;
    client->team->lastclient = list;
  }
  close_interface(interface);
  client->network->interface = NULL;
}
