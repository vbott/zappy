#ifndef		_ERROR_RESOURCE_
# define	_ERROR_RESOURCE_

#include <exception>
#include <string>

namespace	Error
{
  class		Resource : public std::exception
  {
   protected:
    std::string _what;

  public:
    Resource(std::string const &what) throw();
    Resource(Resource const &src) throw();
    virtual ~Resource() throw();
    virtual const char * what() const throw();

  private:
    Resource&	operator=(Resource const &src);
    Resource();
  };
}

#endif		/* !_ERROR_RESOURCE_ */
