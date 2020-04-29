#include <algorithm>
#include "Case.hpp"

Case::Case(int x, int y, int food, int linemate, int deraumere, int sibur,
	   int mendiane, int phiras, int thystame) :
  _x(x), _y(y)
{
  _resources["food"] = food;
  _resources["linemate"] = linemate;
  _resources["deraumere"] = deraumere;
  _resources["sibur"] = sibur;
  _resources["mendiane"] = mendiane;
  _resources["phiras"] = phiras;
  _resources["thystame"] = thystame;
}

Case::~Case()
{}

int		Case::getX() const
{
  return (_x);
}

int		Case::getY() const
{
  return (_y);
}

int		&Case::operator[](std::string const &key)
{
  return (_resources[key]);
}

Player		*&Case::operator[](int ref)
{
  return (_players[ref]);
}

Egg		*&Case::operator[](float ref)
{
  return (_eggs[static_cast<int>(ref)]);
}

void		Case::erasePlayer(int num)
{
  _players.erase(num);
}

void		Case::eraseEgg(int num)
{
  _eggs.erase(num);
}

static bool	isNotNull(std::pair<std::string, int> const &pair)
{
  return (pair.second);
}

bool		Case::isEmpty() const
{
  std::map<std::string, int>::const_iterator it;
  bool		noResource;

  it = std::find_if(_resources.begin(), _resources.end(), isNotNull);
  if (it == _resources.end())
    noResource = true;
  else
    noResource = false;
  return (noResource && _players.empty() && _eggs.empty());
}

bool		Case::isAnyEgg() const
{
  return (!_eggs.empty());
}

int		Case::getNbPlayers() const
{
  return (_players.size());
}

int		Case::getNumFirstPlayer() const
{
  std::map<int, Player *>::const_iterator it = _players.begin();

  if (_players.begin() != _players.end())
    return (it->first);
  return (-1);
}
