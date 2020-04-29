#include "Error_Communication.hpp"

Error::Communication::Communication(const std::string &what) throw() :
  _what(what)
{}

Error::Communication::Communication(Communication const &src) throw() :
  _what(src._what)
{}

Error::Communication::~Communication() throw()
{}

const char*	Error::Communication::what() const throw()
{
  return (_what.c_str());
}
