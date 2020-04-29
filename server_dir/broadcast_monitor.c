/*
** broadcast_monitor for zappy in /home/snap/projects/zappy/server_dir
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Thu 23 Jun 2011 12:52:25 AM CEST botton vivien
** Last update Thu 23 Jun 2011 12:52:25 AM CEST botton vivien
*/

#include <string.h>
#include "server.h"

void		broadcast_monitor(t_zappy *zappy, t_client *client,
	       	void (*func)(char *, int *, t_client *))
{
  t_list	*tmp;
  char		*buffer;
  int		size;

  if (!zappy->monitors)
    return ;
  buffer = get_buffer(64);
  func(buffer, &size, client);
  for (tmp = zappy->monitors; tmp; tmp = tmp->next)
  {
   get_same_buffer(buffer);
   add_packet_buffer_size(((t_monitor*)tmp->value)->network->interface,
		   buffer, size);
  }
  release_buffer(buffer);
}

void		broadcast_monitor_value(t_zappy *zappy, t_client *client,
	       	void *value, void (*func)(char *, int *, t_client *, void *))
{
  t_list	*tmp;
  char		*buffer;
  int		size;

  if (!zappy->monitors)
    return ;
  buffer = get_buffer(64);
  func(buffer, &size, client, value);
  for (tmp = zappy->monitors; tmp; tmp = tmp->next)
  {
   get_same_buffer(buffer);
   add_packet_buffer_size(((t_monitor*)tmp->value)->network->interface,
		   buffer, size);
  }
  release_buffer(buffer);
}

void		broadcast_monitor_msg(t_zappy *zappy, t_client *client,
	       	char *msg, void (*func)(char *, int *, t_client *, char *))
{
  t_list	*tmp;
  char		*buffer;
  int		size;
  int		len;

  if (!zappy->monitors)
    return ;
  len = strlen(msg);
  if (len > 8150)
    msg[8150] = '\0';
  buffer = get_buffer(len + 20);
  func(buffer, &size, client, msg);
  for (tmp = zappy->monitors; tmp; tmp = tmp->next)
  {
   get_same_buffer(buffer);
   add_packet_buffer_size(((t_monitor*)tmp->value)->network->interface,
		   buffer, size);
  }
  release_buffer(buffer);
}
