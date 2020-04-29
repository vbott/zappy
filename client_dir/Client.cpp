#include <cstring>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include "Client.hpp"
#include "Converter.hpp"
#include "Error_Arguments.hpp"
#include "Error_Connection.hpp"
#include "Error_Parsing.hpp"

Client::Client() :
  offset_read(0), offset_buf(0), port(""), host(""), socket(-1)
{}

Client::~Client()
{
  if (this->socket != -1)
    ::close(this->socket);
}

void	Client::getNextResponse(std::string & to_fill)
{
  to_fill = "";
  while (1)
    {
      for (int i = 0; i < this->offset_read; ++i)
  	{
  	  if (this->buf[i] == '\n')
  	    {
  	      this->buf[i] = '\0';
  	      to_fill += this->buf;
  	      memmove(this->buf, this->buf + i + 1, this->offset_read - i - 1);
	      this->offset_read -= i + 1;
  	      return ;
  	    }
  	}
      this->buf[this->offset_read] = '\0';
      to_fill += this->buf;
      this->offset_read = recv(this->socket, this->buf, BUF_LEN - 1, 0);
      if (this->offset_read <= 0)
	throw Error::Connection("Error while receiving data");
    }
}

int	Client::writeServer(std::string const &str)
{
  int	nb_write;

  if ((nb_write = send(this->socket, str.c_str(), str.size(), 0)) < 0)
    throw Error::Connection("Can't write on socket");
  return (nb_write);
}

void	Client::connect()
{
  struct addrinfo	hints;
  struct addrinfo	*res;
  struct addrinfo	*cpy;
  int			n = -1;

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = 0;
  hints.ai_protocol = IPPROTO_TCP;
  if (getaddrinfo(this->host.c_str(), this->port.c_str(), &hints, &res) != 0)
    throw Error::Connection("Can't use getaddrinfo");
  cpy = res;
  while (cpy)
    {
      this->socket = ::socket(cpy->ai_family, cpy->ai_socktype, cpy->ai_protocol);
      if (this->socket != -1 &&
	  (n = ::connect(this->socket, cpy->ai_addr, cpy->ai_addrlen)) == 0)
	cpy = NULL;
      cpy = (cpy) ? cpy->ai_next : NULL;
      if (this->socket != -1 && n != 0)
	::close(this->socket);
    }
  if (n == -1)
    throw Error::Connection("Can't connect");
  freeaddrinfo(res);
}
