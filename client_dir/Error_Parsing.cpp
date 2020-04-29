//
// Error_Parsing.cpp for zappy in /home/chambi_r//proj/zappy/client_dir
// 
// Made by raphael chambily
// Login   <chambi_r@epitech.net>
// 
// Started on  Mon Jun 13 17:52:23 2011 raphael chambily
// Last update Wed Jun 15 17:11:00 2011 raphael chambily
//

#include "Error_Parsing.hpp"

Error::Parsing::Parsing(const std::string &what) throw() :
  _what(what)
{}

Error::Parsing::Parsing(Parsing const &src) throw() :
  _what(src._what)
{}

Error::Parsing::~Parsing() throw()
{}

const char*		Error::Parsing::what() const throw()
{
  return (this->_what.c_str());
}
