//
// Client.hh for zappy in /home/chambi_r//proj/zappy/client_dir
// 
// Made by raphael chambily
// Login   <chambi_r@epitech.net>
// 
// Started on  Mon Jun 13 17:07:54 2011 raphael chambily
// Last update Wed Jul  6 16:33:16 2011 gianni castellani
//

#ifndef __CLIENT_HH__
# define __CLIENT_HH__

#include <string>
#include <list>

# define BUF_LEN 1024

class Client
{
private:
  char		buf[BUF_LEN];
  int		offset_read;
  int		offset_buf;

protected:
  std::string	port;
  std::string	host;
  int		socket;

protected:
  int		writeServer(std::string const &);
  void		connect();
  void		getNextResponse(std::string &);

  Client();
  virtual ~Client();

public:
  virtual void	getConnectionInfos(int ac, char **av) = 0;

};

#endif /* !__CLIENT_HH__ */
