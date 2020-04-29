//
// Error_Arguments.cpp for zappy in /home/chambi_r//proj/zappy/client_dir
// 
// Made by raphael chambily
// Login   <chambi_r@epitech.net>
// 
// Started on  Mon Jun 13 17:52:23 2011 raphael chambily
// Last update Mon Jun 13 17:52:24 2011 raphael chambily
//

#include "Error_Arguments.hpp"

Error::Arguments::Arguments(const std::string &what) throw() :
  _what(what)
{}

Error::Arguments::Arguments(Arguments const &src) throw() :
  _what(src._what)
{}

Error::Arguments::~Arguments() throw()
{}

const char*		Error::Arguments::what() const throw()
{
  return (this->_what.c_str());
}
