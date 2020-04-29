#ifndef		_ERROR_CONNECTION_
# define	_ERROR_CONNECTION_

#include	<exception>
#include	<string>

namespace	Error
{
  class		Connection : public std::exception
  {
   protected:
    std::string _what;

  public:
    Connection(std::string const &what) throw();
    Connection(Connection const &src) throw();
    virtual ~Connection() throw();
    virtual const char * what() const throw();

  private:
    Connection&	operator=(Connection const &src);
    Connection();
  };
}

#endif		/*!_ERROR_CONNECTION_*/
