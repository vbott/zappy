#include <iostream>
#include <SFML/Window.hpp>
#include <Viewer.hpp>
#include "Animation.hpp"

Animation::Animation(unsigned int x, unsigned int y, unsigned int maxFrame,
		     unsigned int padding, unsigned int height, sf::Sprite sprite,
		     int paddingX, int paddingY)
  : _x(x), _y(y), _maxFrame(maxFrame), _padding(padding), _height(height),
    _frame(0), _sprite(sprite), _paddingX(paddingX),
    _paddingY(paddingY)
{
}

Animation::~Animation()
{
}

void		Animation::show(sf::RenderWindow & window, int scrollLeft,
				int scrollUp, int width, int height)
{
  int		tmpx;
  int		tmpy;

  tmpx = _x - scrollLeft;
  if (tmpx < 0)
    tmpx += width;
  if (tmpx >= width)
    tmpx %= width;
  tmpy = _y - scrollUp;
  if (tmpy < 0)
    tmpy += height;
  if (tmpy >= height)
    tmpy %= height;
  if (tmpx < 9 && tmpx < width && tmpx >= 0 &&
      tmpy < 9 && tmpy < height && tmpy >= 0)
    {
      std::pair<float, float> iso = this->mapToIso(tmpx + scrollLeft, tmpy + scrollUp, scrollLeft, scrollUp);

      int offset = this->_frame * this->_padding;
      this->_sprite.SetSubRect(sf::IntRect(offset, 0, offset + this->_padding,
				       this->_height));

      int           resx = iso.first + OFFSET_X + this->_paddingX;
      int           resy = iso.second + OFFSET_Y + this->_paddingY;
      
      this->_sprite.SetPosition(resx, resy);
      window.Draw(this->_sprite);
    }
}

bool		Animation::nextFrame()
{
  this->_frame += 1;
  if (this->_frame == this->_maxFrame)
    return false;
  return true;
}

std::pair<float, float>	Animation::mapToIso(float x, float y,
					    int scrollLeft, int scrollUp) const
{
  float		resx;
  float		resy;

  x -= scrollLeft;
  y -= scrollUp;
  resx = ((x - y) * (BLOCK_X / 2));
  resy = ((x + y) * (BLOCK_Y / 2));
  return (std::pair<float, float>(resx, resy));
}
