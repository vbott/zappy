//
// Error_Arguments.hpp for zappy in /home/chambi_r//proj/zappy/client_dir
// 
// Made by raphael chambily
// Login   <chambi_r@epitech.net>
// 
// Started on  Mon Jun 13 17:52:16 2011 raphael chambily
// Last update Mon Jun 13 17:52:26 2011 raphael chambily
//

#ifndef		_ERROR_ARGUMENTS_
# define	_ERROR_ARGUMENTS_

# include <exception>
# include <string>

namespace Error
{
  class		Arguments : public std::exception
  {
   protected:
    std::string _what;

  public:
    Arguments(std::string const &what) throw();
    Arguments(Arguments const &src) throw();
    virtual ~Arguments() throw();
    virtual const char * what() const throw();

  private:
    Arguments&	operator=(Arguments const &src);
    Arguments();
  };
}

#endif		/* _ERROR_COMMUNICATION_ */
