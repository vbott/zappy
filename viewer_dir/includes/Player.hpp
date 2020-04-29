#ifndef		_PLAYER_
# define	_PLAYER_

#include	<map>
#include	<string>

enum		e_direction
  {
    LEFTUP,
    RIGHTUP,
    LEFTBOTTOM,
    RIGHTBOTTOM,
    NONE
  };

enum		e_posture
  {
    STRAIGHT,
    BENT,
    SAT
  };

class		Player
{
public:
  Player(int x, int y, e_direction direction, int level, std::string const &team,
	 unsigned int lenTruncatedTeamName = 12);
  ~Player();

  unsigned int	&operator[](std::string const &key);
  void		setX(int x);
  void		setY(int y);
  void		setDirection(e_direction dir);
  void		setPosture(e_posture posture);
  void		setLevel(int level);
  int		getX() const;
  int		getY() const;
  int		getLevel() const;
  e_direction	getDirection() const;
  e_posture	getPosture() const;
  std::string const &getTeamName() const;
  std::string const &getTruncatedTeamName() const;
  bool		operator<(Player const &) const;

private:
  int		_x;
  int		_y;
  e_direction	_direction;
  e_posture	_posture;
  int		_level;
  std::string	_teamName;
  std::string	_truncatedTeamName;
  std::map<std::string, unsigned int> _resources;
};

#endif		/*_!PLAYER_*/
