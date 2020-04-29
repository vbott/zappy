#include <cstdlib>
#include <iostream>
#include <exception>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include "Viewer.hpp"

int		main(int ac, char **av)
{
  if (ac > 0)
    {
      strrchr(av[0], '/')[0] = '\0';
      if (chdir(av[0]) == -1)
	{
	  perror("chdir");
	  return (EXIT_FAILURE);
	}
    }
  try
    {
      Viewer	viewer(ac, av);

      viewer.mainLoop();
    }
  catch (std::exception const &e)
    {
      std::cerr << e.what() << std::endl;
      return (EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}
