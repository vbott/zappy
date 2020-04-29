#ifndef __AI_HPP__
# define __AI_HPP__

#include <queue>
#include <utility>
#include <list>
#include <map>
#include <string>
#include "Client.hpp"

typedef std::pair<int, int> Coord;
typedef std::pair<int, int> Size;
typedef std::map<std::string, size_t> Case;

typedef struct s_broadcastInfo
{
  Coord		coord;
  size_t	direction;
}		broadcastInfo;

#define PLAYER "joueur"
#define LINEMATE "linemate"
#define DERAUMERE "deraumere"
#define SIBUR "sibur"
#define MENDIANE "mendiane"
#define PHIRAS "phiras"
#define THYSTAME "thystame"
#define FOOD "nourriture"

#define STOPTIME 20

#define FOODLIMIT 50

enum	e_direction {
  LEFT = 0,
  UP,
  RIGHT,
  DOWN
};

enum	e_incant_statement {
  INCANTATING = 0,
  FAIL,
  SUCCESS
};

class AI : public Client
{
public:
  AI(int ac, char **av);
  ~AI();

  void	runAI(char **av);

private:
  std::map<std::string, int> joinMap;
  std::vector<std::string> messageRessources;

  size_t level;
  std::map<std::string, size_t> inventory;
  std::queue<Coord> coord;
  std::queue<struct s_broadcastInfo> broadcastCoords;
  std::queue<std::string> urgentCmd;
  std::string team_name;
  int id;
  int nb_players;
  bool isLast;
  enum e_direction direction;
  Coord	Pos;
  size_t broadcastStopper;
  bool onIncantationCase;
  bool hasLaid;
  bool hasFork;
  enum e_incant_statement endIncantation;

  Size mapSize;
  std::map<Coord, Case> voirMap;

private:
  virtual void	getConnectionInfos(int ac, char **av);
  void	initCase(Case &myCase) const;
  void	recupFirstInfos();
  bool	inventoryCmd();
  void	voirCmd();
  int	connectNbrCmd();
  std::string	sendAndLookForSpecialAnswer(std::string const &, std::string const &);
  bool	sendCmdToServer(std::string const &);
  void	treatDeath();
  void	treatNewPlayer();
  void	treatMsg(std::string const &, std::string const &);
  Coord	transCoord(int, int) const;
  void	createAI(char **av);
  void	popRessources();

  /* incantation */
  void	followBroadcast();
  void	lookAtIncantation();
  bool	checkForIncantationCase();
  bool	finalizeIncantation();
  bool	callForTheOthers();
  void	prepareIncantationCase();
  bool	enoughRessources();
  void	addBroadcastCoord(size_t, std::string const &);

  /* movements */
  void	takeWhatYouNeed(bool);
  void	followCoords(bool);
  void	turn(enum e_direction);
  void	findCoords(bool);
  void	goToCoord(int, int);
  bool	somethingInteresting(Case &, bool);

  /* food */
  void	takeFood();


  void	getId();
};

#endif /* !__AI_HPP__ */
