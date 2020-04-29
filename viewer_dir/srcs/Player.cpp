#include "Player.hpp"

Player::Player(int x, int y, e_direction direction, int level, std::string const &team, unsigned int lenTruncatedTeamName) :
  _x(x), _y(y), _direction(direction), _level(level), _teamName(team)
{
  _resources["food"] = 10;
  _resources["linemate"] = 0;
  _resources["deraumere"] = 0;
  _resources["sibur"] = 0;
  _resources["mendiane"] = 0;
  _resources["phiras"] = 0;
  _resources["thystame"] = 0;
  _truncatedTeamName = team;
  _posture = STRAIGHT;
  if (team.length() > lenTruncatedTeamName)
    _truncatedTeamName.resize(lenTruncatedTeamName);
}

Player::~Player()
{}

unsigned int	&Player::operator[](std::string const &key)
{
  return (_resources[key]);
}

void		Player::setX(int x)
{
  _x = x;
}

void		Player::setY(int y)
{
  _y = y;
}

void		Player::setDirection(e_direction dir)
{
  _direction = dir;
}

void		Player::setPosture(e_posture pos)
{
  _posture = pos;
}

void		Player::setLevel(int level)
{
  _level = level;
}

int		Player::getX() const
{
  return (_x);
}

int		Player::getY() const
{
  return (_y);
}

int		Player::getLevel() const
{
  return (_level);
}

e_direction	Player::getDirection() const
{
  return (_direction);
}

e_posture	Player::getPosture() const
{
  return (_posture);
}

std::string const &Player::getTeamName() const
{
  return (_teamName);
}

std::string const &Player::getTruncatedTeamName() const
{
  return (_truncatedTeamName);
}

bool		Player::operator<(Player const &rhs) const
{
  return (this->_x + this->_y < rhs._x + rhs._y);
}
