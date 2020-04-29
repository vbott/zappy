//
// Error_Arguments.hpp for zappy in /home/chambi_r//proj/zappy/client_dir
// 
// Made by raphael chambily
// Login   <chambi_r@epitech.net>
// 
// Started on  Mon Jun 13 17:52:16 2011 raphael chambily
// Last update Wed Jun 15 17:10:59 2011 raphael chambily
//

#ifndef		_ERROR_PARSING_
# define	_ERROR_PARSING_

# include <exception>
# include <string>

namespace Error
{
  class		Parsing : public std::exception
  {
   protected:
    std::string _what;

  public:
    Parsing(std::string const &what) throw();
    Parsing(Parsing const &src) throw();
    virtual ~Parsing() throw();
    virtual const char * what() const throw();

  private:
    Parsing&	operator=(Parsing const &src);
    Parsing();
  };
}

#endif		/* _ERROR_PARSING_ */
