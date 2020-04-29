#include "Error_Resource.hpp"

Error::Resource::Resource(const std::string &what) throw() :
  _what(what)
{}

Error::Resource::Resource(Resource const &src) throw() :
  _what(src._what)
{}

Error::Resource::~Resource() throw()
{}

const char*	Error::Resource::what() const throw()
{
  return (_what.c_str());
}
