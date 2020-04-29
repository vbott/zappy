/*
** utils for ftpd in /home/snap/projects/my_ftp/serveur
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Sat 02 Apr 2011 05:18:12 PM CEST botton vivien
** Last update Sat 02 Apr 2011 05:18:12 PM CEST botton vivien
*/

#define _XOPEN_SOURCE
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include "net.h"

inline int	min(int a, int b)
{
  return ((a < b) ? a : b);
}

static inline  void	cleanup(SOCKET *tmp)
{
  if (*tmp == INVALID_SOCKET)
    return ;
  close(*tmp);
  *tmp = -1;
}

inline static void	setreuse(SOCKET sock)
{
  int reuse = 1;

  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (void *)&reuse, sizeof(reuse));
}

int		connect_to(char *addr, char *port)
{
  t_addrinfo	*cpy;
  t_addrinfo	*result;
  t_addrinfo	hints;
  SOCKET	tmp;

  tmp = -1;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  if (getaddrinfo(addr, port, &hints, &result) != 0)
    return (-1);
  for (cpy = result; cpy; cpy = cpy->ai_next)
    {
     tmp = xsocket(cpy->ai_family, cpy->ai_socktype, cpy->ai_protocol);
     if (tmp == INVALID_SOCKET)
      return (-1);
     if (xconnect(tmp, cpy->ai_addr, cpy->ai_addrlen) == 0)
      break ;
     return (-1);
    }
  freeaddrinfo(result);
  return (tmp);
}

int		listen_to(char *port)
{
  t_addrinfo	*cpy;
  t_addrinfo	*result;
  t_addrinfo	hints;
  SOCKET	tmp;

  tmp = -1;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_flags = AI_PASSIVE;
  if (getaddrinfo(NULL, port, &hints, &result) != 0)
    return (-1);
  for (cpy = result; cpy; cpy = cpy->ai_next)
    {
     tmp = xsocket(cpy->ai_family, cpy->ai_socktype, cpy->ai_protocol);
     setreuse(tmp);
     if (tmp != INVALID_SOCKET &&
	 xbind(tmp, cpy->ai_addr, cpy->ai_addrlen) == 0 &&
	 xlisten(tmp, BACKLOG) == 0)
      break ;
     cleanup(&tmp);
    }
  freeaddrinfo(result);
  return (tmp);
}
