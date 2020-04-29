#ifndef		_CASE_HPP_
# define	_CASE_HPP_

#include <map>
#include <string>
#include "Egg.hpp"

class		Player;
class		Egg;

#define		PLAYER 0
#define		EGG 1

class		Case
{
public:
  Case(int x, int y, int food = 0, int linemate = 0, int deraumere = 0,
       int sibur = 0, int mendiane = 0, int phiras = 0, int thystame = 0);
  ~Case();

  int		getX() const;
  int		getY() const;
  int		&operator[](std::string const &ref);
  Player	*&operator[](int ref);
  Egg		*&operator[](float ref);

  void		erasePlayer(int num);
  void		eraseEgg(int num);
  bool		isEmpty() const;
  bool		isAnyEgg() const;
  int		getNbPlayers() const;
  int		getNumFirstPlayer() const;

private:
  int		_x;
  int		_y;
  std::map<std::string, int> _resources;
  std::map<int, Player *> _players;
  std::map<int, Egg *> _eggs;
};

#endif		/* !_CASE_HPP_*/
