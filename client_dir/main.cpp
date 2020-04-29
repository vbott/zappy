//
// main.cpp for zappy in /home/chambi_r//proj/zappy/client_dir
// 
// Made by raphael chambily
// Login   <chambi_r@epitech.net>
// 
// Started on  Mon Jun 13 17:06:43 2011 raphael chambily
// Last update Fri Jul  8 17:13:57 2011 raphael chambily
//

#include <list>
#include <string>
#include <iostream>
#include "AI.hpp"
#include "Converter.hpp"

void		aff_list(std::list<std::list<std::string> > const &list)
{
  std::list<std::list<std::string> >::const_iterator	it;
  std::list<std::string>::const_iterator		it2;

  for (it = list.begin(); it != list.end(); ++it)
    {
      std::cout << "[";
      for (it2 = (*it).begin(); it2 != (*it).end(); ++it2)
	std::cout << (*it2) << "-";
      std::cout << "]" << std::endl;
    }
}

int		main(int ac, char **av)
{
  try {
    AI	client(ac, av);

    client.runAI(av);
  }
  catch (std::exception const &e) {
    std::cerr << e.what() << std::endl;
  }
}
