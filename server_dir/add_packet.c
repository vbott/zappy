/*
** main.c for zappy in /home/shotgun/projets/c/zappy/server_dir
**
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
**
** Started on  Fri Jun 17 22:50:44 CEST 2011 cerisier mickael
** Last update Fri Jun 17 22:50:44 CEST 2011 cerisier mickael
*/

#include <string.h>
#include <sys/epoll.h>
#include "server.h"

inline void	add_packet(t_interface *interface, char *content)
{
  add_packet_size(interface, content, strlen(content));
}

inline void	add_packet_buffer(t_interface *interface, char *content)
{
  add_packet_buffer_size(interface, content, strlen(content));
}

void		add_packet_size(t_interface *interface,
		char *content, size_t size)
{
  char		*buffer;

  if (!interface || !content || interface->socket == -1)
    return ;
  buffer = get_buffer(size);
  memcpy(buffer, content, size);
  add_packet_buffer_size(interface, buffer, size);
}

void		add_packet_buffer_size(t_interface *interface, char *content,
				       size_t size)
{
  t_list	*list;
  t_packet	*packet;

  if (!interface || !content || interface->socket == -1)
  {
    release_buffer(content);
    return ;
  }
  list = get_packet();
  packet = (t_packet*)list->value;
  packet->buffer = content;
  packet->size = size;
  packet->index = 0;
  if (!interface->packet_to_send)
    mod_epoll(interface, EPOLLIN | EPOLLOUT);
  list->next = NULL;
  if (interface->last_packet)
    interface->last_packet->next = list;
  else
    interface->packet_to_send = list;
  interface->last_packet = list;
}
