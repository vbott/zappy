/*
** interface for zappy in /home/snap/projects/zappy/server_dir
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Thu 16 Jun 2011 01:14:14 PM CEST botton vivien
** Last update Thu 16 Jun 2011 01:14:14 PM CEST botton vivien
*/

#include <stdlib.h>
#include <sys/epoll.h>
#include "server.h"

void			add_interface(t_zappy *zappy,
		t_interface *interface, int socket, int flags)
{
  struct epoll_event ev;

  interface->socket = socket;
  interface->epoll_fd = zappy->epoll_fd;
  ev.events = flags;
  ev.data.u64 = 0;
  ev.data.ptr = interface;
  epoll_ctl(interface->epoll_fd, EPOLL_CTL_ADD, socket, &ev);
}

inline void		remove_interface(t_interface *interface)
{
  epoll_ctl(interface->epoll_fd, EPOLL_CTL_DEL, interface->socket, NULL);
}

void			close_interface(t_interface *interface)
{
  t_list		*tmp;
  t_zappy		*zappy;

  zappy = (t_zappy*)((interface->hangup == &close_client) ?
	   ((t_client*)interface->userdata)->network->zappy :
	   interface->userdata);
  zappy->nbclients--;
  if (zappy->nbclients < zappy->threshold)
    add_interface(zappy, zappy->accept_interface,
		  zappy->accept_interface->socket, EPOLLIN);
  if (interface->socket != -1)
  {
    remove_interface(interface);
    shutdown(interface->socket, SHUT_RDWR);
    close(interface->socket);
  }
  while (interface->packet_to_send)
  {
    tmp = interface->packet_to_send->next;
    release_buffer(((t_packet*)interface->packet_to_send->value)->buffer);
    release_packet(interface->packet_to_send);
    interface->packet_to_send = tmp;
  }
  release_buffer(interface->buffer);
  free(interface);
}
