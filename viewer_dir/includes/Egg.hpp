#ifndef		_EGG_
# define	_EGG_

class		Egg
{
public:
  Egg(int x, int y);
  ~Egg();

  int		getX() const;
  int		getY() const;

private:
  int		_x;
  int		_y;
};

#endif		/*!_EGG_*/
