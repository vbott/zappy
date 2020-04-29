#ifndef		_VIEWER_
# define	_VIEWER_

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <map>
#include <string>
#include <vector>
#include "Map.hpp"
#include "Client.hpp"
#include "Thread.hpp"
#include "Mutex.hpp"
#include "Player.hpp"
#include "ConditionVar.hpp"
#include "Animation.hpp"

// size of main window
# define	XWIN 1250
# define	YWIN 850

// map offsets
# define	OFFSET_Y 80
# define	OFFSET_X 550


// size of resources sprites
# define	RES_X 25
# define	RES_Y 25

// size of ground sprite
# define	BLOCK_X 134.f
# define	BLOCK_Y 67.f

// size of caption window
# define	XCAPTION 200
# define	YCAPTION 370

// size of time selector
# define	XTIME	300
# define	YTIME	50

// size of time icons
# define	XTIME_ICON 63

// size of inventory
# define	XINVENTORY 150
# define	YINVENTORY 500

// minimal size of level window
# define	XLEVEL	650
# define	NAME_SPACE 150

// Stuff about walking sprites
# define	MOVE_PLAYER_FRAMES 8
# define	MOVE_PLAYER_PADDING 49
# define	MOVE_PLAYER_HEIGHT 95
# define	MOVE_PLAYER_PADDING_X 30
# define	MOVE_PLAYER_PADDING_Y -50

// frames
# define	INCANTATION_FRAMES 5
# define	INCANTATION_PADDING 190
# define	INCANTATION_HEIGHT 80
# define	INCANTATION_PADDING_X -10
# define	INCANTATION_PADDING_Y -20

class		Egg;

class		Viewer : public Client, public Thread
{
public:
  Viewer(int ac, char **av);
  ~Viewer();

  void		mainLoop();
  virtual void	getConnectionInfos(int ac, char **av);

  virtual void	*run(void *arg = NULL);

private:
  sf::RenderWindow			_window;
  sf::RenderWindow			_caption;
  sf::RenderWindow			_levelWindow;
  sf::RenderWindow			_inventory;
  std::multiset<std::string>		_teamNames;
  bool					_displayCaption;
  bool					_displaySummary;
  bool					_displayInventory;
  std::map<std::string, sf::Texture>	_images;
  std::map<std::string, sf::Sprite >	_sprites;
  bool					_background;
  Map					_map;
  sf::Shape				_bg;
  sf::Shape				_menuTime;
  sf::Shape				_bgGameOver;
  sf::Shape				_msgServer;
  sf::Font				_font;
  std::map<std::string, void (Viewer::*)(std::vector<std::string> &)>	_receivedCmds;
  std::map<int, Player *>		_players;
  std::map<int, Egg *>			_eggs;
  std::map<std::string, std::string>	_resourceTranslator;
  std::list<std::string>		_cmds;
  mutable Mutex				_mutex;
  int					_t;
  ConditionVar				_wait;
  int					_scrollLeft;
  int					_scrollUp;
  int					_lastSelectedX;
  int					_lastSelectedY;
  int					_target;
  sf::Sprite				_chara[4];
  sf::Sprite				_charasit[4];
  sf::Sprite				_charabent[4];
  sf::Sprite				_incantation[7];
  std::string				_winner;

  sf::Clock				_timer;
  bool					_end;
  bool					_pause;

private:
  void		close();
  void		showMap();
  void		drawCase(int x, int y, sf::Sprite &sprite);
  void		setBackground(std::string const &path);
  void		displayBackground();
  void		showMsg(std::string const& msg);

  void		drawPlayers();
  void		drawChara(unsigned int x, unsigned int y,
			  Player* player);
  void		drawSprite(unsigned int x, unsigned int y, sf::Sprite &sprite,
			   int offsetX = 0, int offsetY = 0);
  void		drawEndOfGame(std::string const& winner);
  void		drawArrows();

  void		selectCase(int x, int y);
  bool		clickArrow(unsigned int xMouse, unsigned int yMouse);
  void		selectTarget(int x, int y);
  void		focusOn(int x, int y);

  void		scrollUp(int value = 1);
  void		scrollLeft(int value = 1);
  void		scrollDown(int value = 1);
  void		scrollRight(int value = 1);

  void		displayNbItem(Case *obj, std::string const &ref,
			      int x, int y);
  void		displayNbPlayers(Case *obj, int x, int y);

  void		drawLastSelectedCase(std::string const &ref);

  void		showTimeUnity();
  bool		changeTime(unsigned int xMouse, unsigned int yMouse);

  void		showCaseContent(int x, int y);
  void		checkAnimations();

  void		handshake();
  void		updateInformations();

  void		initCaption();
  void		initLevelWindow();
  void		initInventoryWindow();

  void		manageCaseContentEvents(sf::Event &event);
  void		manageCaptionEvents(sf::Event &event);
  void		manageMainWindowEvents(sf::Event &event);
  void		manageSummaryEvents(sf::Event &event);
  void		manageInventoryEvents(sf::Event &event);
  void		manageKeyboardInput(sf::Event const &event);

  void		inputKeyH();
  void		inputKeyS();
  void		inputKeyI();

  void		displayTeamNames();
  void		refreshLevelWindow();
  int		calcTeamLevelPlayers(int level, std::string const &teamName) const;

  void		receiveCmdMsz(std::vector<std::string> &cmd);
  void		receiveCmdBct(std::vector<std::string> &cmd);
  void		receiveCmdTna(std::vector<std::string> &cmd);
  void		receiveCmdPnw(std::vector<std::string> &cmd);
  void		receiveCmdPpo(std::vector<std::string> &cmd);
  void		receiveCmdPlv(std::vector<std::string> &cmd);
  void		receiveCmdPin(std::vector<std::string> &cmd);
  void		receiveCmdPex(std::vector<std::string> &cmd);
  void		receiveCmdPbc(std::vector<std::string> &cmd);
  void		receiveCmdPic(std::vector<std::string> &cmd);
  void		receiveCmdPie(std::vector<std::string> &cmd);
  void		receiveCmdPfk(std::vector<std::string> &cmd);
  void		receiveCmdPdr(std::vector<std::string> &cmd);
  void		receiveCmdPgt(std::vector<std::string> &cmd);
  void		receiveCmdPdi(std::vector<std::string> &cmd);
  void		receiveCmdEnw(std::vector<std::string> &cmd);
  void		receiveCmdEht(std::vector<std::string> &cmd);
  void		receiveCmdEbo(std::vector<std::string> &cmd);
  void		receiveCmdEdi(std::vector<std::string> &cmd);
  void		receiveCmdSgt(std::vector<std::string> &cmd);
  void		receiveCmdSeg(std::vector<std::string> &cmd);
  void		receiveCmdSmg(std::vector<std::string> &cmd);
  void		receiveCmdSuc(std::vector<std::string> &cmd);
  void		receiveCmdSbp(std::vector<std::string> &cmd);

  void		sendCmdMsz();
  void		sendCmdBct();
  void		sendCmdMct();
  void		sendCmdTna();
  void		sendCmdPpo(int num);
  void		sendCmdPlv(int num);
  void		sendCmdPin(int num);
  void		sendCmdSgt();
  void		sendCmdSst(int t);

  std::pair<float, float> mapToIso(float x, float y) const;
  std::pair<int, int> isoToMap(int x, int y) const;
  e_direction	convertToDirection(const std::string &ref);
  std::string	&takeOffSharp(std::string &src) const;
  std::vector<Animation *>	_animations;
};

#endif		/* !_VIEWER_*/
