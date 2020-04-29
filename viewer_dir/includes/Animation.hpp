#ifndef		__ANIMATION_HPP__
# define	__ANIMATION_HPP__

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>

class			Animation
{
public:
  Animation(unsigned int x, unsigned int y, unsigned int maxFrame,
	    unsigned int padding, unsigned int height,
	    sf::Sprite sprite, int paddingX = 0, int paddingY = 0);
  ~Animation();

  int			getX() const;
  int			getY() const;
  sf::Sprite &		getSprite() const;
  sf::Clock &		getClock() const;

  bool			nextFrame();
  std::pair<float, float> mapToIso(float x, float y, int scrollLeft, int scrollUp) const;
  void			show(sf::RenderWindow &window, int scrollLeft, int scrollUp, int width, int height);

private:
  unsigned int		_x;
  unsigned int		_y;
  unsigned int		_maxFrame;
  unsigned int		_padding;
  unsigned int		_height;
  unsigned int		_frame;
  sf::Sprite		_sprite;
  sf::Clock		_clock;
  int			_paddingX;
  int			_paddingY;
};

#endif
