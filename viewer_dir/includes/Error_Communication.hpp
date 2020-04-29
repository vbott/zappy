#ifndef		_ERROR_COMMUNICATION_
# define	_ERROR_COMMUNICATION_

#include <exception>
#include <string>

namespace	Error
{
  class		Communication : public std::exception
  {
   protected:
    std::string _what;

  public:
    Communication(std::string const &what) throw();
    Communication(Communication const &src) throw();
    virtual ~Communication() throw();
    virtual const char * what() const throw();

  private:
    Communication&	operator=(Communication const &src);
    Communication();
  };
}

#endif		/* !_ERROR_COMMUNICATION */
