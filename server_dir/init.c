/*
** init for zappy in /home/snap/projects/zappy/server_dir
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Thu 16 Jun 2011 01:09:16 PM CEST botton vivien
** Last update Thu 16 Jun 2011 01:09:16 PM CEST botton vivien
*/

#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/epoll.h>
#define _GNU_SOURCE
#include <sys/socket.h>
#include "server.h"

int accept4(int sockfd, struct sockaddr *addr, socklen_t *addrlen, int flags);

static inline void	set_threshold_fd(t_zappy *zappy,
		t_interface *interface)
{
  zappy->threshold = zappy->nbclients;
  remove_interface(interface);
}

void			accept_client(t_interface *interface)
{
  int			client;
  t_zappy		*zappy;
  t_interface           *new_interface;

  zappy = (t_zappy*)interface->userdata;
  client = accept4(zappy->server_socket, NULL, NULL, SOCK_NONBLOCK);
  if (client == -1)
  {
    if (errno == EMFILE || errno == ENFILE)
      set_threshold_fd(zappy, interface);
    return ;
  }
  zappy->nbclients++;
  new_interface = xmalloc(sizeof(*new_interface));
  memset(new_interface, 0, sizeof(*new_interface));
  new_interface->read = &circular_buffer;
  new_interface->hangup = &close_interface;
  new_interface->write = &send_packet;
  new_interface->buffer = get_buffer(BUFFER_SIZE);
  new_interface->userdata = zappy;
  new_interface->arg = new_interface;
  new_interface->parsing = &choose_type;
  add_interface(zappy, new_interface, client, EPOLLIN);
  add_packet(new_interface, "BIENVENUE\n");
}

void			default_value(t_zappy *zappy)
{
  memset(zappy, 0, sizeof(*zappy));
  zappy->t = 100;
  zappy->port = "4242";
  zappy->x = 10;
  zappy->y = 10;
  zappy->limit = 1;
}

void			set_non_blocking(int sock)
{
  int flags;

  flags = fcntl(sock, F_GETFL);
  fcntl(sock, F_SETFL, flags | O_NONBLOCK);
}

int			init(t_zappy *zappy)
{
  struct sigaction      act;
  t_interface		*tmp;

  zappy->epoll_fd = epoll_create(1);
  if (zappy->epoll_fd == -1)
    return (-1);
  zappy->server_socket = listen_to(zappy->port);
  if (zappy->server_socket == -1)
    return (-1);
  set_non_blocking(zappy->server_socket);
  memset(&act, 0, sizeof(act));
  act.sa_handler = SIG_IGN;
  sigaction(SIGPIPE, &act, NULL);
  tmp = xmalloc(sizeof(*tmp));
  memset(tmp, 0, sizeof(*tmp));
  tmp->read = &accept_client;
  tmp->userdata = zappy;
  add_interface(zappy, tmp, zappy->server_socket, EPOLLIN);
  zappy->accept_interface = tmp;
  init_stdin(zappy);
  build_map(zappy);
  push_system_action_2(zappy, EAT, &restore_food, NULL);
  return (0);
}
