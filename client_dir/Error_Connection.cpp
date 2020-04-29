#include "Error_Connection.hpp"

Error::Connection::Connection(const std::string &what) throw() :
  _what(what)
{}

Error::Connection::Connection(Connection const &src) throw() :
  _what(src._what)
{}

Error::Connection::~Connection() throw()
{}

const char*	Error::Connection::what() const throw()
{
  return (_what.c_str());
}
