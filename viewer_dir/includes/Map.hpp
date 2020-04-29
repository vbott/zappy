#ifndef			__MAP_HPP__
# define		__MAP_HPP__

#include "Octree.hpp"
#include "Case.hpp"

class			Player;

class			Map
{
public:
  Map(int width, int height);
  ~Map();

  void		setWidth(int width);
  void		setHeight(int height);
  int		getWidth() const;
  int		getHeight() const;

  void		push(Case *obj);
  void		pop(Case *obj);
  Case		*find(int x, int y) const;
  Case		*find(int x, int y);

  void		erasePlayer(int num, int x, int y);
  void		eraseEgg(int num, int x, int y);

  void		addPlayer(int num, Player *p, int x, int y);

  bool		isCaseEmpty(Case *obj) const;
  bool		isCaseEmpty(int x, int y) const;
  void		transformEggInPlayer(int num);
  int		getNumFirstPlayer(int x, int y) const;

private:
  int		_width;
  int		_height;
  Octree<Case *>_octree;
};

#endif
