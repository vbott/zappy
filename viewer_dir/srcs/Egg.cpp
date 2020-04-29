#include "Egg.hpp"

Egg::Egg(int x, int y)
  : _x(x), _y(y)
{}

Egg::~Egg()
{}

int	Egg::getX() const
{
  return (_x);
}

int	Egg::getY() const
{
  return (_y);
}
