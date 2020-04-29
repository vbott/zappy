#include "../includes/Map.hpp"

Map::Map(int width, int height) :
  _width(width), _height(height)
{
}

Map::~Map()
{
}

void			Map::setWidth(int width)
{
  this->_width = width;
}

void			Map::setHeight(int height)
{
  this->_height = height;
}

int			Map::getWidth() const
{
  return (this->_width);
}

int			Map::getHeight() const
{
  return (this->_height);
}

void			Map::push(Case *obj)
{
  int			x = obj->getX();
  int			y = obj->getY();

  _octree.push(obj, x, y, 0);
}

void			Map::pop(Case *obj)
{
  int			x = obj->getX();
  int			y = obj->getY();

  _octree.pop(x, y, 0);
}

Case			*Map::find(int x, int y) const
{
  Case			**obj;

  if ((obj = _octree.find(x, y, 0)))
    return (*obj);
  return (0);
}

Case			*Map::find(int x, int y)
{
  Case			**obj;

  if ((obj = _octree.find(x, y, 0)))
    return (*obj);
  return (0);
}

void			Map::erasePlayer(int num, int x, int y)
{
  Case			*obj = this->find(x, y);

  if (obj)
    {
      obj->erasePlayer(num);
      if (isCaseEmpty(obj))
	{
	  this->pop(obj);
	  delete obj;
	}
    }
}

void			Map::eraseEgg(int num, int x, int y)
{
  Case			*obj = this->find(x, y);

  if (obj)
    {
      obj->eraseEgg(num);
      if (isCaseEmpty(obj))
	{
	  this->pop(obj);
	  delete obj;
	}
    }
}

void			Map::addPlayer(int num, Player *p, int x, int y)
{
  Case			*obj = this->find(x, y);

  if (obj)
    (*obj)[num] = p;
  else
    {
      obj = new Case(x, y);

      (*obj)[num] = p;
      push(obj);
    }
}

bool			Map::isCaseEmpty(Case *obj) const
{
  if (obj)
    {
      return (obj->isEmpty());
    }
  return (false);
}

bool			Map::isCaseEmpty(int x, int y) const
{
  Case			*obj = this->find(x, y);

  if (obj)
    {
      return (obj->isEmpty());
    }
  return (false);
}

int			Map::getNumFirstPlayer(int x, int y) const
{
  Case			*obj = this->find(x, y);

  if (obj)
    {
      return (obj->getNumFirstPlayer());
    }
  return (-1);
}
