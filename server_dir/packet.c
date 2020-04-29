/*
** packet for zappy in /home/snap/projects/zappy/server_dir
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Thu 16 Jun 2011 10:52:03 PM CEST botton vivien
** Last update Thu 16 Jun 2011 10:52:03 PM CEST botton vivien
*/

#include <string.h>
#include <sys/epoll.h>
#include <sys/uio.h>
#include <sys/ioctl.h>
#define __need_IOV_MAX
#include <stdio.h>
#include "server.h"

inline void	mod_epoll(t_interface *interface, int flags)
{
  struct epoll_event ev;

  ev.events = flags;
  ev.data.u64 = 0;
  ev.data.ptr = interface;
  epoll_ctl(interface->epoll_fd, EPOLL_CTL_MOD, interface->socket, &ev);
}

void		remove_packet(t_interface *interface)
{
  t_packet      *packet;
  t_list	*list;

  list = interface->packet_to_send;
  if (!list)
    return ;
  packet = (t_packet*)list->value;
  interface->packet_to_send = list->next;
  if (!interface->packet_to_send)
  {
    mod_epoll(interface, EPOLLIN);
    interface->last_packet = NULL;
  }
  release_buffer(packet->buffer);
  release_packet(list);
}

void		send_packet(t_interface *interface)
{
  int		ret;
  int		i;
  t_packet	*packet;
  t_list	*list;
  struct iovec	iov[IOV_MAX];

  if (!interface->packet_to_send || !interface->packet_to_send->value ||
		  interface->socket == -1)
    return ;
  for (i = 0, list = interface->packet_to_send; list && i < IOV_MAX; ++i)
  {
    packet = (t_packet*)list->value;
    iov[i].iov_base = &packet->buffer[packet->index];
    iov[i].iov_len = packet->size - packet->index;
    list = list->next;
  }
  for (ret = writev(interface->socket, iov, i); ret > 0; ret -= i)
  {
    packet = (t_packet*)interface->packet_to_send->value;
    i = packet->size - packet->index;
    if (ret >= i)
      remove_packet(interface);
    else
      packet->index += ret;
  }
}
