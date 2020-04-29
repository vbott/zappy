#include <iostream>
#include "Converter.hpp"

std::auto_ptr<std::vector<std::string> >	Converter::explode(const std::string& str, char sep)
{
  std::istringstream split(str);
  std::auto_ptr<std::vector<std::string> > ret;
  std::vector<std::string>	*tokens = new std::vector<std::string>;

  for (std::string each; std::getline(split, each, sep); tokens->push_back(each));
  if (str[str.size() - 1] == sep)
    tokens->push_back("");
  ret.reset(tokens);
  return (ret);
}
