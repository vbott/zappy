#include <map>
#include <string>
#include <SFML/Window.hpp>
#include <iostream>
#include <algorithm>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <math.h>
#include <cstring>
#include "Map.hpp"
#include "Viewer.hpp"
#include "Error_Arguments.hpp"
#include "Error_Connection.hpp"
#include "Error_Parsing.hpp"
#include "Error_Communication.hpp"
#include "Error_Resource.hpp"
#include "Converter.hpp"

Viewer::Viewer(int ac, char **av)
  : Client(), _displayCaption(false), _displaySummary(true),
    _displayInventory(false), _background(false),
    _map(0, 0), _t(1),
    _scrollLeft(0), _scrollUp(0),
    _lastSelectedX(-1), _lastSelectedY(-1),
    _target(-1), _end(false), _pause(false)
{
  getConnectionInfos(ac, av);
  connect();
  handshake();

  this->_images["deraumere"].LoadFromFile("viewer_dir/resource/sprites/deraumere.png");
  this->_images["egg"].LoadFromFile("viewer_dir/resource/sprites/egg.png");
  this->_images["food"].LoadFromFile("viewer_dir/resource/sprites/food.png");
  this->_images["linemate"].LoadFromFile("viewer_dir/resource/sprites/linemate.png");
  this->_images["mendiane"].LoadFromFile("viewer_dir/resource/sprites/mendiane.png");
  this->_images["phiras"].LoadFromFile("viewer_dir/resource/sprites/phiras.png");
  this->_images["sibur"].LoadFromFile("viewer_dir/resource/sprites/sibur.png");
  this->_images["thystame"].LoadFromFile("viewer_dir/resource/sprites/thystame.png");
  this->_images["ground"].LoadFromFile("viewer_dir/resource/sprites/ground.png");
  this->_images["grass"].LoadFromFile("viewer_dir/resource/sprites/grass.png");
  this->_images["selected_ground"].LoadFromFile("viewer_dir/resource/sprites/selected_ground.png");
  this->_images["chara_LEFTUP"].LoadFromFile("viewer_dir/resource/sprites/chara_LEFTUP.png");
  this->_images["chara_LEFTBOTTOM"].LoadFromFile("viewer_dir/resource/sprites/chara_LEFTBOTTOM.png");
  this->_images["chara_RIGHTUP"].LoadFromFile("viewer_dir/resource/sprites/chara_RIGHTUP.png");
  this->_images["chara_RIGHTBOTTOM"].LoadFromFile("viewer_dir/resource/sprites/chara_RIGHTBOTTOM.png");
  this->_images["charasit_LEFTUP"].LoadFromFile("viewer_dir/resource/sprites/charasit_LEFTUP.png");
  this->_images["charasit_LEFTBOTTOM"].LoadFromFile("viewer_dir/resource/sprites/charasit_LEFTBOTTOM.png");
  this->_images["charasit_RIGHTUP"].LoadFromFile("viewer_dir/resource/sprites/charasit_RIGHTUP.png");
  this->_images["charasit_RIGHTBOTTOM"].LoadFromFile("viewer_dir/resource/sprites/charasit_RIGHTBOTTOM.png");
  this->_images["charabent_LEFTUP"].LoadFromFile("viewer_dir/resource/sprites/charabent_LEFTUP.png");
  this->_images["charabent_LEFTBOTTOM"].LoadFromFile("viewer_dir/resource/sprites/charabent_LEFTBOTTOM.png");
  this->_images["charabent_RIGHTUP"].LoadFromFile("viewer_dir/resource/sprites/charabent_RIGHTUP.png");
  this->_images["charabent_RIGHTBOTTOM"].LoadFromFile("viewer_dir/resource/sprites/charabent_RIGHTBOTTOM.png");
  this->_images["arrow_leftup"].LoadFromFile("viewer_dir/resource/sprites/arrow_leftup.png");
  this->_images["arrow_leftdown"].LoadFromFile("viewer_dir/resource/sprites/arrow_leftdown.png");
  this->_images["arrow_rightup"].LoadFromFile("viewer_dir/resource/sprites/arrow_rightup.png");
  this->_images["arrow_rightdown"].LoadFromFile("viewer_dir/resource/sprites/arrow_rightdown.png");
  this->_images["less"].LoadFromFile("viewer_dir/resource/sprites/less.png");
  this->_images["more"].LoadFromFile("viewer_dir/resource/sprites/more.png");
  this->_images["head"].LoadFromFile("viewer_dir/resource/sprites/head.png");
  this->_images["incantation1"].LoadFromFile("viewer_dir/resource/sprites/incantation.png");
  this->_images["incantation2"].LoadFromFile("viewer_dir/resource/sprites/incantation2.png");
  this->_images["incantation3"].LoadFromFile("viewer_dir/resource/sprites/incantation3.png");
  this->_images["incantation4"].LoadFromFile("viewer_dir/resource/sprites/incantation4.png");
  this->_images["incantation5"].LoadFromFile("viewer_dir/resource/sprites/incantation5.png");
  this->_images["incantation6"].LoadFromFile("viewer_dir/resource/sprites/incantation6.png");
  this->_images["incantation7"].LoadFromFile("viewer_dir/resource/sprites/incantation7.png");
  this->_images["pause"].LoadFromFile("viewer_dir/resource/sprites/pause.png");
  this->_images["play"].LoadFromFile("viewer_dir/resource/sprites/play.png");

  this->_sprites["deraumere"].SetTexture(this->_images["deraumere"]);
  this->_sprites["egg"].SetTexture(this->_images["egg"]);
  this->_sprites["food"].SetTexture(this->_images["food"]);
  this->_sprites["linemate"].SetTexture(this->_images["linemate"]);
  this->_sprites["mendiane"].SetTexture(this->_images["mendiane"]);
  this->_sprites["phiras"].SetTexture(this->_images["phiras"]);
  this->_sprites["sibur"].SetTexture(this->_images["sibur"]);
  this->_sprites["thystame"].SetTexture(this->_images["thystame"]);
  this->_sprites["ground"].SetTexture(this->_images["ground"]);
  this->_sprites["grass"].SetTexture(this->_images["grass"]);
  this->_sprites["selected_ground"].SetTexture(this->_images["selected_ground"]);
  this->_sprites["arrow_leftup"].SetTexture(this->_images["arrow_leftup"]);
  this->_sprites["arrow_leftdown"].SetTexture(this->_images["arrow_leftdown"]);
  this->_sprites["arrow_rightup"].SetTexture(this->_images["arrow_rightup"]);
  this->_sprites["arrow_rightdown"].SetTexture(this->_images["arrow_rightdown"]);
  this->_sprites["less"].SetTexture(this->_images["less"]);
  this->_sprites["more"].SetTexture(this->_images["more"]);
  this->_sprites["head"].SetTexture(this->_images["head"]);
  this->_sprites["incantation"].SetTexture(this->_images["incantation"]);
  this->_sprites["pause"].SetTexture(_images["pause"]);
  this->_sprites["play"].SetTexture(_images["play"]);

  this->_chara[LEFTBOTTOM].SetTexture(this->_images["chara_LEFTBOTTOM"]);
  this->_chara[LEFTUP].SetTexture(this->_images["chara_LEFTUP"]);
  this->_chara[RIGHTBOTTOM].SetTexture(this->_images["chara_RIGHTBOTTOM"]);
  this->_chara[RIGHTUP].SetTexture(this->_images["chara_RIGHTUP"]);
  this->_charasit[LEFTBOTTOM].SetTexture(this->_images["charasit_LEFTBOTTOM"]);
  this->_charasit[LEFTUP].SetTexture(this->_images["charasit_LEFTUP"]);
  this->_charasit[RIGHTBOTTOM].SetTexture(this->_images["charasit_RIGHTBOTTOM"]);
  this->_charasit[RIGHTUP].SetTexture(this->_images["charasit_RIGHTUP"]);
  this->_charabent[LEFTBOTTOM].SetTexture(this->_images["charabent_LEFTBOTTOM"]);
  this->_charabent[LEFTUP].SetTexture(this->_images["charabent_LEFTUP"]);
  this->_charabent[RIGHTBOTTOM].SetTexture(this->_images["charabent_RIGHTBOTTOM"]);
  this->_charabent[RIGHTUP].SetTexture(this->_images["charabent_RIGHTUP"]);

  this->_incantation[0].SetTexture(this->_images["incantation1"]);
  this->_incantation[1].SetTexture(this->_images["incantation2"]);
  this->_incantation[2].SetTexture(this->_images["incantation3"]);
  this->_incantation[3].SetTexture(this->_images["incantation4"]);
  this->_incantation[4].SetTexture(this->_images["incantation5"]);
  this->_incantation[5].SetTexture(this->_images["incantation6"]);
  this->_incantation[6].SetTexture(this->_images["incantation7"]);

  this->_bg = sf::Shape::Rectangle(0, 0, XWIN, YWIN - 105, sf::Color(0, 0, 0));
  this->_menuTime = sf::Shape::Rectangle(XWIN - XTIME, 0, XWIN, YTIME, sf::Color(0, 0, 0));
  this->_bgGameOver = sf::Shape::Rectangle(0, YWIN / 2 - 50, XWIN, YWIN / 2 + 50, sf::Color(0, 0, 0),
					   5, sf::Color(47, 84, 245));
  this->_msgServer = sf::Shape::Rectangle(1, YWIN - 50, XWIN - 1, YWIN - 1, sf::Color(0, 0, 0),
					  1, sf::Color(47, 84, 245));

  if (!this->_font.LoadFromFile("viewer_dir/resource/font/bgrove.ttf"))
    throw Error::Resource("Can't load font");

  _receivedCmds["msz"] = &Viewer::receiveCmdMsz;
  _receivedCmds["bct"] = &Viewer::receiveCmdBct;
  _receivedCmds["tna"] = &Viewer::receiveCmdTna;
  _receivedCmds["pnw"] = &Viewer::receiveCmdPnw;
  _receivedCmds["ppo"] = &Viewer::receiveCmdPpo;
  _receivedCmds["plv"] = &Viewer::receiveCmdPlv;
  _receivedCmds["pin"] = &Viewer::receiveCmdPin;
  _receivedCmds["pex"] = &Viewer::receiveCmdPex;
  _receivedCmds["pbc"] = &Viewer::receiveCmdPbc;
  _receivedCmds["pic"] = &Viewer::receiveCmdPic;
  _receivedCmds["pie"] = &Viewer::receiveCmdPie;
  _receivedCmds["pfk"] = &Viewer::receiveCmdPfk;
  _receivedCmds["pdr"] = &Viewer::receiveCmdPdr;
  _receivedCmds["pgt"] = &Viewer::receiveCmdPgt;
  _receivedCmds["pdi"] = &Viewer::receiveCmdPdi;
  _receivedCmds["enw"] = &Viewer::receiveCmdEnw;
  _receivedCmds["eht"] = &Viewer::receiveCmdEht;
  _receivedCmds["ebo"] = &Viewer::receiveCmdEbo;
  _receivedCmds["edi"] = &Viewer::receiveCmdEdi;
  _receivedCmds["sgt"] = &Viewer::receiveCmdSgt;
  _receivedCmds["seg"] = &Viewer::receiveCmdSeg;
  _receivedCmds["smg"] = &Viewer::receiveCmdSmg;
  _receivedCmds["suc"] = &Viewer::receiveCmdSuc;
  _receivedCmds["sbp"] = &Viewer::receiveCmdSbp;

  _resourceTranslator["0"] = "food";
  _resourceTranslator["1"] = "linemate";
  _resourceTranslator["2"] = "deraumere";
  _resourceTranslator["3"] = "sibur";
  _resourceTranslator["4"] = "mendiane";
  _resourceTranslator["5"] = "phiras";
  _resourceTranslator["6"] = "thystame";
  _window.Create(sf::VideoMode(XWIN, YWIN, 32), "Zappy Viewer", sf::Style::Close);
  _timer.Reset();
  std::cout << "h : caption" << std::endl
	    << "s : summary" << std::endl
	    << "i : inventory" << std::endl
	    << "left button : show case content" << std::endl
	    << "right button : focus on case or player" << std::endl
	    << "esc : quit" << std::endl;
}

Viewer::~Viewer()
{
}

void		Viewer::mainLoop()
{
  sf::Event	Event;
  int		endTime = 30;

  start();
  _wait.uniqueWait();
  this->updateInformations();
  if (_map.getWidth() == 0 || _map.getHeight() == 0)
    throw Error::Communication("Server sent an incorrect map");
  if (_window.IsOpened())
    {
      _window.Clear();
      this->displayBackground();
      this->showMap();
      this->showMsg("[No server message]");
    }
  while (_window.IsOpened())
    {
      this->manageMainWindowEvents(Event);
      this->manageCaptionEvents(Event);
      this->manageSummaryEvents(Event);
      this->manageInventoryEvents(Event);
      this->updateInformations();
      this->_window.Display();
      if (_caption.IsOpened() && _displayCaption)
	this->_caption.Display();
      if (_levelWindow.IsOpened() && _displaySummary)
	this->_levelWindow.Display();
      if (_inventory.IsOpened() && _displayInventory)
	this->_inventory.Display();
      if (_end || endTime < 30)
	{
	  if (endTime == 30)
	    endTime = 0;
	  endTime++;
	  drawEndOfGame(_winner);
	}
      sf::Sleep(0.1);
    }
  this->cancel();
}

void		Viewer::close()
{
  this->_window.Close();
  if (_caption.IsOpened())
    _caption.Close();
  if (_levelWindow.IsOpened())
    _levelWindow.Close();
  if (_inventory.IsOpened())
    _inventory.Close();
}

void		Viewer::initLevelWindow()
{
  sf::Text	text("1", _font, 20);

  _levelWindow.Create(sf::VideoMode(XLEVEL, 20 + 40 * (_teamNames.size() + 1), 32), "Team Summary", sf::Style::Close);
  _levelWindow.Clear();
  //text.SetFont(_font);
  text.SetCharacterSize(20);
  text.SetPosition(NAME_SPACE, 10.f);
  text.SetStyle(sf::Text::Bold);
  for (int i = 1; i <= 8; ++i)
    {
      text.SetString(Converter::toString<int>(i));
      _levelWindow.Draw(text);
      text.Move((XLEVEL - NAME_SPACE) / 8, 0);
    }
  this->displayTeamNames();
  this->refreshLevelWindow();
}

void		Viewer::refreshLevelWindow()
{
  sf::Text	nbPlayers;
  std::multiset<std::string>::const_iterator	it = _teamNames.begin();
  int		j;
  static sf::Shape rect = sf::Shape::Rectangle(NAME_SPACE, 55.f, XLEVEL, 20 + 40 * (_teamNames.size() + 1), sf::Color(0, 0, 0));

  nbPlayers.SetFont(_font);
  nbPlayers.SetCharacterSize(20);
  _levelWindow.Draw(rect);
  for (float i = 40.f; it != _teamNames.end(); ++it, i += 40.f)
    {
      nbPlayers.SetPosition(NAME_SPACE, 15.f + i);
      for (j = 1; j <= 8; ++j)
	{
	  nbPlayers.SetString(Converter::toString<int>(this->calcTeamLevelPlayers(j, *it)));
	  _levelWindow.Draw(nbPlayers);
	  nbPlayers.Move((XLEVEL - NAME_SPACE) / 8, 0);
	}
    }
}

void		Viewer::initInventoryWindow()
{
  sf::Text    Text("Inventory", _font);

  _inventory.Create(sf::VideoMode(XINVENTORY, YINVENTORY, 32),
		    "Inventory", sf::Style::Close);
  _inventory.Clear();
  Text.SetPosition(20.f, 8.0f);
  this->_inventory.Draw(Text);
}

void		Viewer::displayTeamNames()
{
  std::multiset<std::string>::const_iterator	it = _teamNames.begin();
  sf::Text	text;
  std::string	name;

  text.SetFont(_font);
  text.SetStyle(sf::Text::Bold);
  text.SetPosition(5.f, 10.f);
  for (float i = 40.f; it != _teamNames.end(); ++it, i += 40.f)
    {
      text.Move(0.f, 40.f);
      name.assign(*it, 0, 9);
      text.SetString(name);
      _levelWindow.Draw(text);
    }
}

int		Viewer::calcTeamLevelPlayers(int level, std::string const &teamName) const
{
  std::map<int, Player *>::const_iterator it = _players.begin();
  int		nb = 0;

  for (; it != _players.end(); ++it)
    {
      if (it->second->getTeamName() == teamName && it->second->getLevel() == level)
	++nb;
    }
  return (nb);
}

void		Viewer::initCaption()
{
  _caption.Create(sf::VideoMode(XCAPTION, YCAPTION, 32), "Help", sf::Style::Close);
  if (_caption.IsOpened())
    {
      std::list<std::string> names;
      std::list<sf::Sprite> sprites;

      names.push_back("food");
      names.push_back("linemate");
      names.push_back("deraumere");
      names.push_back("sibur");
      names.push_back("mendiane");
      names.push_back("phiras");
      names.push_back("thystame");

      sprites.push_back(_sprites["food"]);
      sprites.push_back(_sprites["linemate"]);
      sprites.push_back(_sprites["deraumere"]);
      sprites.push_back(_sprites["sibur"]);
      sprites.push_back(_sprites["mendiane"]);
      sprites.push_back(_sprites["phiras"]);
      sprites.push_back(_sprites["thystame"]);

      std::list<std::string>::iterator item = names.begin();
      std::list<sf::Sprite>::iterator sprite = sprites.begin();
      sf::Text name;

      name.SetFont(this->_font);
      name.SetCharacterSize(22);
      _caption.Clear();
      for (size_t y = 20; item != names.end(); ++item, ++sprite)
	{
	  sprite->SetPosition(10, y);
	  _caption.Draw(*sprite);
	  name.SetString(*item);
	  name.SetPosition(60, y - 3);
	  _caption.Draw(name);
	  y += 50;
	}
    }
}

void		Viewer::manageKeyboardInput(sf::Event const &Event)
{
  if (Event.Key.Code == 'h')
    this->inputKeyH();
  else if (Event.Key.Code == 's')
    this->inputKeyS();
  else if (Event.Key.Code == 'i')
    this->inputKeyI();
}

void		Viewer::manageSummaryEvents(sf::Event &Event)
{
    #if (SFML_VERSION_MAJOR == 2)
    while (this->_levelWindow.PollEvent(Event))
    #else
    while (this->_levelWindow.GetEvent(Event))
    #endif
      {
      	if (Event.Type == sf::Event::Closed ||
      	    ((Event.Type == sf::Event::KeyPressed) &&
      	     (Event.Key.Code == sf::Keyboard::Escape)))
	  {
	    _levelWindow.Show(false);
	    _displaySummary = false;
	  }
	else if (Event.Type == sf::Event::KeyReleased)
	  manageKeyboardInput(Event);
      }
}

void		Viewer::manageCaptionEvents(sf::Event &Event)
{
    #if (SFML_VERSION_MAJOR == 2)
    while (this->_caption.PollEvent(Event))
    #else
    while (this->_caption.GetEvent(Event))
    #endif
      {
      	if (Event.Type == sf::Event::Closed ||
      	    ((Event.Type == sf::Event::KeyPressed) &&
      	     (Event.Key.Code == sf::Keyboard::Escape)))
	  {
	    _caption.Show(false);
	    _displayCaption = false;
	  }
	else if (Event.Type == sf::Event::KeyReleased)
	  manageKeyboardInput(Event);
      }
}

void		Viewer::manageInventoryEvents(sf::Event &Event)
{
    #if (SFML_VERSION_MAJOR == 2)
    while (this->_inventory.PollEvent(Event))
    #else
    while (this->_inventory.GetEvent(Event))
    #endif
      {
      	if (Event.Type == sf::Event::Closed ||
      	    ((Event.Type == sf::Event::KeyPressed) &&
      	     (Event.Key.Code == sf::Keyboard::Escape)))
	  {
	    _inventory.Show(false);
	    _displayInventory = false;
	  }
	else if (Event.Type == sf::Event::KeyReleased)
	  manageKeyboardInput(Event);
      }
}

void		Viewer::manageMainWindowEvents(sf::Event &Event)
{
    #if (SFML_VERSION_MAJOR == 2)
    while (this->_window.PollEvent(Event))
    #else
    while (this->_window.GetEvent(Event))
    #endif
      {
      	if (Event.Type == sf::Event::Closed ||
      	    ((Event.Type == sf::Event::KeyPressed) &&
      	     (Event.Key.Code == sf::Keyboard::Escape)))
      	  this->close();
      	else if (!_end && Event.Type == sf::Event::MouseButtonReleased)
	  {
	    if (Event.MouseButton.Button == sf::Mouse::Left &&
		this->clickArrow(Event.MouseButton.X, Event.MouseButton.Y) == false &&
		this->changeTime(Event.MouseButton.X, Event.MouseButton.Y) == false)
	      this->selectCase(Event.MouseButton.X, Event.MouseButton.Y);
	    else if (Event.MouseButton.Button == sf::Mouse::Right)
	      this->selectTarget(Event.MouseButton.X, Event.MouseButton.Y);
      	  }
	else if (!_end && Event.Type == sf::Event::KeyReleased)
	  manageKeyboardInput(Event);
      }
}

void			Viewer::inputKeyH()
{
  if (_displayCaption)
    {
      _displayCaption = false;
      _caption.Show(false);
    }
  else
    {
      if (!_caption.IsOpened())
	this->initCaption();
      _displayCaption = true;
      _caption.Show(true);
    }
}

void			Viewer::inputKeyI()
{
  if (_displayInventory)
    {
      _displayInventory = false;
      _inventory.Show(false);
    }
  else
    {
      if (!_inventory.IsOpened())
	this->initInventoryWindow();
      _displayInventory = true;
      _inventory.Show(true);
    }
}

void			Viewer::inputKeyS()
{
  if (_displaySummary)
    {
      _displaySummary = false;
      _levelWindow.Show(false);
    }
  else
    {
      _displaySummary = true;
      _levelWindow.Show(true);
    }
}

void			Viewer::focusOn(int x, int y)
{
  int	shiftx = x % 9 - ((_map.getWidth() > 9) ? 4 : _map.getWidth() / 2);
  int	shifty = y % 9 - ((_map.getHeight() > 9) ? 4 : _map.getHeight() / 2);

  _scrollLeft += shiftx;
  if (this->_scrollLeft < 0)
    _scrollLeft += _map.getWidth();
  else
    _scrollLeft %= _map.getWidth();
  _scrollUp += shifty;
  if (this->_scrollUp < 0)
    _scrollUp += _map.getHeight();
  else
    _scrollUp %= _map.getHeight();
  this->showMap();
}

void			Viewer::selectTarget(int x, int y)
{
  std::pair<int, int> coords = this->isoToMap(x - OFFSET_X, y - OFFSET_Y);
  int		resx = coords.first % _map.getWidth();
  int		resy = coords.second % _map.getHeight();

  int		tmpx = coords.first - _scrollLeft;
  int		tmpy = coords.second - _scrollUp;

  if (tmpx < 9 && tmpx < _map.getWidth() && tmpx >= 0 &&
      tmpy < 9 && tmpy < _map.getHeight() && tmpy >= 0)
    {
      if (_target != -1 && tmpx == 4 && tmpy == 4)
	_target = -1;
      else
	_target = _map.getNumFirstPlayer(resx, resy);
      if (_target == -1)
	{
	  this->selectCase(x, y);
	}
      this->focusOn(tmpx, tmpy);
    }
}

std::pair<float, float>	Viewer::mapToIso(float x, float y) const
{
  float		resx;
  float		resy;

  x -= this->_scrollLeft;
  y -= this->_scrollUp;

  resx = ((x - y) * (BLOCK_X / 2));
  resy = ((x + y) * (BLOCK_Y / 2));
  return (std::pair<float, float>(resx, resy));
}

void		Viewer::drawCase(int x, int y, sf::Sprite &sprite)
{
  float		resx;
  float		resy;
  std::pair<float, float> iso = this->mapToIso(x, y);
  Case		*pCase = this->_map.find(x % _map.getWidth(), y % _map.getHeight());

  resx = iso.first + OFFSET_X;
  resy = iso.second + OFFSET_Y;
  sprite.SetPosition(resx, resy);
  this->_window.Draw(sprite);
  if (pCase)
    {
      Case		&refCase = *(pCase);

      if (refCase["thystame"])
  	{
	  sf::Sprite &sprite = _sprites["thystame"];

  	  sprite.SetPosition(resx + 55, resy + 2);
          this->_window.Draw(sprite);
  	}
      if (refCase["linemate"])
  	{
	  sf::Sprite &sprite = _sprites["linemate"];

  	  sprite.SetPosition(resx + 70, resy + 10);
          this->_window.Draw(sprite);
  	}
      if (refCase["food"])
  	{
	  sf::Sprite &sprite = _sprites["food"];

  	  sprite.SetPosition(resx + 90, resy + 22);
  	  this->_window.Draw(sprite);
  	}
      if (refCase["deraumere"])
      	{
	  sf::Sprite &sprite = _sprites["deraumere"];

      	  sprite.SetPosition(resx + 35, resy + 10);
          this->_window.Draw(sprite);
      	}
      if (refCase.isAnyEgg())
	{
	  sf::Sprite &sprite = _sprites["egg"];

	  sprite.SetPosition(resx + 50, resy);
          _window.Draw(sprite);
	}
      if (refCase["sibur"])
      	{
	  sf::Sprite &sprite = _sprites["sibur"];

      	  sprite.SetPosition(resx + 15, resy + 20);
          this->_window.Draw(sprite);
      	}
      if (refCase["mendiane"])
      	{
	  sf::Sprite &sprite = _sprites["mendiane"];

      	  sprite.SetPosition(resx + 50, resy + 22);
          this->_window.Draw(sprite);
      	}
      if (refCase["phiras"])
      	{
	  sf::Sprite &sprite = _sprites["phiras"];

      	  sprite.SetPosition(resx + 55, resy + 39);
          this->_window.Draw(sprite);
      	}
    }
}

void		Viewer::drawLastSelectedCase(std::string const &ref)
{
  int		tmpx;
  int		tmpy;

  if (_lastSelectedX != -1 && _lastSelectedY != -1)
    {
      tmpx =_lastSelectedX - _scrollLeft;
      if (tmpx < 0)
	tmpx += _map.getWidth();
      if (tmpx >= _map.getWidth())
	tmpx = tmpx % _map.getWidth();
      tmpy = _lastSelectedY - _scrollUp;
      if (tmpy < 0)
	tmpy += _map.getHeight();
      if (tmpy >= _map.getHeight())
	tmpy %= _map.getHeight();
      if (tmpx < 9 && tmpx < _map.getWidth() && tmpx >= 0 &&
	  tmpy < 9 && tmpy < _map.getHeight() && tmpy >= 0)
	this->drawCase(tmpx + this->_scrollLeft, tmpy + this->_scrollUp, this->_sprites[ref]);
    }
}

void		Viewer::drawEndOfGame(std::string const & winner)
{
  sf::Text	text;
  std::string	string;

  _window.Draw(this->_bgGameOver);
  string = "La team " + winner + " a gagne !";
  text.SetString(string);
  text.SetPosition(450, YWIN / 2 - 20);
  _window.Draw(text);
}

void		Viewer::showMap()
{
  int		x;
  int		y;
  int		width;
  int		height;

  this->_window.Draw(this->_bg);
  width = this->_map.getWidth();
  height = this->_map.getHeight();
  if (width <= 0 || height <= 0)
    throw Error::Communication("Server sent an incorrect map");
  x = 0;
  while (x < 9 && x < width)
    {
      y = 0;
      while (y < 9 && y < height)
	{
	  if (x == width - 1 || x == 8 || y == height - 1 || y == 8)
	    this->drawCase(x + this->_scrollLeft, y + this->_scrollUp, this->_sprites["ground"]);
	  this->drawCase(x + this->_scrollLeft, y + this->_scrollUp, this->_sprites["grass"]);
	  y += 1;
	}
      x += 1;
    }
  this->drawLastSelectedCase("selected_ground");
  this->drawPlayers();
  this->drawArrows();
  this->showTimeUnity();
}

void		Viewer::setBackground(const std::string &path)
{
  _images["background"].LoadFromFile(path);
  _sprites["background"].SetTexture(_images["background"]);
  _background = true;
}

void		Viewer::displayBackground()
{
  if (_background)
    _window.Draw(_sprites["background"]);
}

void		Viewer::drawPlayers()
{
  std::map<int, Player *>::const_iterator	it = this->_players.begin();
  int		x;
  int		y;
  int		tmpx;
  int		tmpy;

  for (; it != this->_players.end(); ++it)
    {
      x = it->second->getX();
      y = it->second->getY();

      tmpx = x - _scrollLeft;
      if (tmpx < 0)
	tmpx += _map.getWidth();
      if (tmpx >= _map.getWidth())
	tmpx %= _map.getWidth();
      tmpy = y - _scrollUp;
      if (tmpy < 0)
	tmpy += _map.getHeight();
      if (tmpy >= _map.getHeight())
	tmpy %= _map.getHeight();
      if (tmpx < 9 && tmpx < _map.getWidth() && tmpx >= 0 &&
	  tmpy < 9 && tmpy < _map.getHeight() && tmpy >= 0)
	this->drawChara(x, y, it->second);
    }
}

void		Viewer::drawSprite(unsigned int x, unsigned int y, sf::Sprite &sprite,
				   int offsetX, int offsetY)
{
  if (x >= (unsigned int)this->_scrollLeft && x < (unsigned int)this->_scrollLeft + 8
      && y >= (unsigned int)this->_scrollUp && y < (unsigned int)this->_scrollUp + 8)
    {
      int           resx;
      int           resy;
      std::pair<float, float> iso = this->mapToIso(x, y);

      resx = iso.first + offsetX;
      resy = iso.second + offsetY;
      sprite.SetPosition(resx, resy);
      this->_window.Draw(sprite);
    }
}

void		Viewer::drawChara(unsigned int x, unsigned int y,
				  Player* player)
{
  std::pair<float, float> coords = this->mapToIso(x, y);
  int		resx;
  int		resy;

  resx = coords.first + OFFSET_X + 50;
  resy = coords.second + OFFSET_Y - 50;
  if (player->getPosture() == STRAIGHT)
    {
      this->_chara[player->getDirection()].SetPosition(resx, resy);
      this->_window.Draw(this->_chara[player->getDirection()]);
    }
  else if (player->getPosture() == BENT)
    {
      this->_charabent[player->getDirection()].SetPosition(resx, resy);
      this->_window.Draw(this->_charabent[player->getDirection()]);
    }
  else
    {
      this->_charasit[player->getDirection()].SetPosition(resx, resy);
      this->_window.Draw(this->_charasit[player->getDirection()]);
    }
  if (player->getTruncatedTeamName() != "")
    {
      sf::Text	Text(player->getTruncatedTeamName() + " [" +
			     Converter::toString(player->getLevel()) + "]"
			     , _font, 16);

      Text.SetStyle(sf::Text::Bold);
      Text.Move(resx - player->getTeamName().length() + 10, resy - 25);
      this->_window.Draw(Text);
    }
}

std::pair<int, int> Viewer::isoToMap(int x, int y) const
{
  float		tmpx = x;
  float		tmpy = y;
  return (std::pair<int, int>(floor(tmpy / BLOCK_Y + tmpx / BLOCK_X - 0.5) + _scrollLeft,
			      ceil(tmpy / BLOCK_Y - tmpx / BLOCK_X - 0.5) + _scrollUp));
}

void		Viewer::selectCase(int x, int y)
{
  x -= OFFSET_X;
  y -= OFFSET_Y;

  std::pair<int, int> coords = this->isoToMap(x, y);
  int		resx = coords.first % _map.getWidth();
  int		resy = coords.second % _map.getHeight();

  int		tmpx = coords.first - _scrollLeft;
  int		tmpy = coords.second - _scrollUp;

  if (tmpx < 9 && tmpx < _map.getWidth() && tmpx >= 0 &&
      tmpy < 9 && tmpy < _map.getHeight() && tmpy >= 0)
    {
      if (!_displayInventory)
	this->inputKeyI();
      this->drawLastSelectedCase("grass");
      this->drawCase(coords.first, coords.second, _sprites["selected_ground"]);
      this->_lastSelectedX = coords.first;
      this->_lastSelectedY = coords.second;
      this->drawPlayers();
      this->showCaseContent(resx, resy);
    }
}

void		Viewer::showMsg(std::string const& msg)
{
  sf::Text	text;

  _window.Draw(this->_msgServer);
  text.SetString(msg);
  text.SetCharacterSize(20);
  text.SetPosition(20, YWIN - 40);
  _window.Draw(text);
}

void		Viewer::displayNbItem(Case *obj, std::string const &item, int x, int y)
{
  sf::Sprite	&sprite = this->_sprites[item];
  sf::Text	text;

  text.SetFont(this->_font);
  sprite.SetPosition(x, y);
  _inventory.Draw(sprite);
  if (obj)
    text.SetString(Converter::toString((*obj)[item]));
  else
    text.SetString("0");
  text.Move(x + RES_X + 12, y - 5);
  _inventory.Draw(text);
}

void		Viewer::displayNbPlayers(Case *obj, int x, int y)
{
  sf::Sprite	&sprite = this->_sprites["head"];
  sf::Text	text;

  text.SetFont(this->_font);
  sprite.SetPosition(x, y);
  _inventory.Draw(sprite);
  if (obj)
    text.SetString(Converter::toString(obj->getNbPlayers()));
  else
    text.SetString("0");
  text.Move(x + RES_X + 12, y - 5);
  _inventory.Draw(text);
}

void		Viewer::showCaseContent(int x, int y)
{
  static sf::Shape rect = sf::Shape::Rectangle(15, RES_Y * 2,
					      XINVENTORY, YINVENTORY, sf::Color(0, 0, 0));

  _inventory.Draw(rect);

  Case		*pCase = this->_map.find(x, y);
  std::string	str = "(" + Converter::toString<int>(x) + "," + Converter::toString<int>(y) + ")";
  sf::Text	text(str, _font, 26);

  this->displayNbItem(pCase, "food", 15, RES_Y * 2);
  this->displayNbItem(pCase, "linemate", 15, RES_Y * 4);
  this->displayNbItem(pCase, "deraumere", 15, RES_Y * 6);
  this->displayNbItem(pCase, "sibur", 15, RES_Y * 8);
  this->displayNbItem(pCase, "mendiane", 15, RES_Y * 10);
  this->displayNbItem(pCase, "phiras", 15, RES_Y * 12);
  this->displayNbItem(pCase, "thystame", 15, RES_Y * 14);
  this->displayNbPlayers(pCase, 15, RES_Y * 16);
  text.SetPosition(20, RES_Y * 18);
  _inventory.Draw(text);
}

void		Viewer::drawArrows()
{
  this->_sprites["arrow_leftdown"].SetPosition(150, 600);
  this->_sprites["arrow_rightdown"].SetPosition(1000, 600);
  this->_sprites["arrow_leftup"].SetPosition(150, 150);
  this->_sprites["arrow_rightup"].SetPosition(1000, 150);

  this->_window.Draw(this->_sprites["arrow_leftup"]);
  this->_window.Draw(this->_sprites["arrow_rightdown"]);
  this->_window.Draw(this->_sprites["arrow_rightup"]);
  this->_window.Draw(this->_sprites["arrow_leftdown"]);
}

void		Viewer::scrollDown(int value)
{
  _scrollUp = (_scrollUp + value) % _map.getHeight();
}

void		Viewer::scrollRight(int value)
{
  _scrollLeft = (_scrollLeft + value) % _map.getWidth();
}

void		Viewer::scrollLeft(int value)
{
  _scrollLeft -= value;
  if (this->_scrollLeft < 0)
    _scrollLeft += _map.getWidth();
}

void		Viewer::scrollUp(int value)
{
  _scrollUp -= value;
  if (this->_scrollUp < 0)
    this->_scrollUp += _map.getHeight();
}

bool		Viewer::clickArrow(unsigned int xMouse, unsigned int yMouse)
{
  if (xMouse >= 150 && xMouse <= 250 && yMouse >= 600 && yMouse <= 700)
    this->scrollDown();
  else if (xMouse >= 1000 && xMouse <= 1100 && yMouse >= 600 && yMouse <= 700)
    this->scrollRight();
  else if (xMouse >= 150 && xMouse <= 250 && yMouse >= 150 && yMouse <= 250)
    this->scrollLeft();
  else if (xMouse >= 1000 && xMouse <= 1100 && yMouse >= 150 && yMouse <= 250)
    this->scrollUp();
  else
    return false;
  this->showMap();
  return true;
}

bool		Viewer::changeTime(unsigned int xMouse, unsigned int yMouse)
{
  if (yMouse >= 40.f && yMouse <= 65.f &&
      xMouse >= XWIN - XTIME / 2 - XTIME / 3 &&
      xMouse <= XWIN - XTIME / 2 - XTIME / 3 + 63) // less
    {
      if (_t > 10)
	sendCmdSst(_t - 10);
      else
	sendCmdSst(_t - 1);
    }
  else if (yMouse >= 20.f && yMouse <= 100.f &&
	   xMouse >= XWIN - 70 && xMouse <= XWIN - 7) //more
    {
      if (_t >= 10)
	sendCmdSst(_t + 10);
      else
	sendCmdSst(_t + 1);
    }
  else if (yMouse >= 20.f && yMouse <= 90.f &&
	   xMouse >= 910.f && xMouse <= 950.f)
    {
      if (_pause)
	sendCmdSst(_t);
      else
	sendCmdSst(0);
      _pause = !_pause;
    }
    return (false);
  return (true);
}

void		Viewer::showTimeUnity()
{
  sf::Text	text(Converter::toString<int>(_t), _font);
  sf::Sprite	&more = _sprites["more"];
  sf::Sprite	&less = _sprites["less"];
  sf::Sprite	&pause = (_pause == false ? _sprites["pause"] : _sprites["play"]);

  _window.Draw(_menuTime);
  text.SetPosition(XWIN - XTIME / 2, 34.f);
  _window.Draw(text);
  more.SetPosition(XWIN - 70, 23.f);
  less.SetPosition(XWIN - XTIME / 2 - XTIME / 3, 22.f);
  _window.Draw(more);
  _window.Draw(less);
  pause.SetPosition(XWIN - XTIME / 2 - 2 * (XTIME / 3), 22.f);
  _window.Draw(pause);
}

void		Viewer::checkAnimations()
{
  std::vector<Animation *>::iterator	it;

  for (it = this->_animations.begin() ; it != this->_animations.end() ;)
    {
      (*it)->show(this->_window, this->_scrollLeft, this->_scrollUp, _map.getWidth(), _map.getHeight());
      if ((*it)->nextFrame() == false)
       	{
	  delete *it;
	  it = this->_animations.erase(it);
	}
      if (it != _animations.end())
	++it;
    }
}

void		Viewer::getConnectionInfos(int ac, char **av)
{
  std::string	tmp;

  if (ac < 3)
    throw Error::Arguments("Usage : ./viewer -p port [-h host]");
  for (int i = 0; i < ac; ++i)
    {
      tmp = av[i];
      if (tmp == "-p" && ac > i + 1)
	this->port = av[i + 1];
      else if (tmp == "-h" && ac > i + 1)
	this->host = av[i + 1];
    }
  if (this->host == "")
    this->host = "localhost";
  if (this->port == "")
    throw Error::Arguments("Usage : ./viewer -p port [-h host]");
}

void		Viewer::handshake()
{
  std::auto_ptr<std::vector<std::string> >      tab;
  std::string	res;

  this->getNextResponse(res);
  if (res != "BIENVENUE" && res != "BIENVENUE\r")
    throw Error::Communication("Bad answer from server (received " + res + " instead of BIENVENUE)");
  this->writeServer("GRAPHIC\n");
}

void		Viewer::receiveCmdMsz(std::vector<std::string> &cmd)
{
  if (cmd.size() != 3)
    throw Error::Communication("Received bad answer from server (msz)");
  int		width = Converter::toInt<int>(cmd[1]);
  int		height = Converter::toInt<int>(cmd[2]);

  if (width <= 0 || height <= 0)
    throw Error::Communication("Server sent an incorrect map");
  _map.setWidth(width);
  _map.setHeight(height);
}

void		Viewer::receiveCmdBct(std::vector<std::string> &cmd)
{
  if (cmd.size() != 10)
    throw Error::Communication("Received bad answer from server (bct)");

  int		x = Converter::toInt<int>(cmd[1]);
  int		y = Converter::toInt<int>(cmd[2]);
  Case		*obj = _map.find(x, y);

  if (!obj)
    {
      int	food = Converter::toInt<int>(cmd[3]);
      int	linemate = Converter::toInt<int>(cmd[4]);
      int	deraumere = Converter::toInt<int>(cmd[5]);
      int	sibur = Converter::toInt<int>(cmd[6]);
      int	mendiane = Converter::toInt<int>(cmd[7]);
      int	phiras = Converter::toInt<int>(cmd[8]);
      int	thystame = Converter::toInt<int>(cmd[9]);

      if (food || linemate || deraumere || sibur || mendiane
	  || phiras || thystame)
	{
	  obj = new Case(x, y, food, linemate, deraumere,
			 sibur, mendiane, phiras, thystame);
	  _map.push(obj);
	}
    }
  else
    {
      (*obj)["food"] = Converter::toInt<int>(cmd[3]);
      (*obj)["linemate"] = Converter::toInt<int>(cmd[4]);
      (*obj)["deraumere"] = Converter::toInt<int>(cmd[5]);
      (*obj)["sibur"] = Converter::toInt<int>(cmd[6]);
      (*obj)["mendiane"] = Converter::toInt<int>(cmd[7]);
      (*obj)["phiras"] = Converter::toInt<int>(cmd[8]);
      (*obj)["thystame"] = Converter::toInt<int>(cmd[9]);
    }
  if (_lastSelectedX == x && _lastSelectedY == y)
    this->showCaseContent(x, y);
}

void		Viewer::receiveCmdTna(std::vector<std::string> &cmd)
{
  if (cmd.size() != 2)
    throw Error::Communication("Received bad answer from server (tna)");
  _teamNames.insert(cmd[1]);
}

void		Viewer::receiveCmdPnw(std::vector<std::string> &cmd)
{
  if (cmd.size() != 7)
    throw Error::Communication("Received bad answer from server (pnw)");

  if (!_levelWindow.IsOpened())
    this->initLevelWindow();

  e_direction	direction = convertToDirection(cmd[4]);
  int		num = Converter::toInt<int>(this->takeOffSharp(cmd[1]));
  int		x = Converter::toInt<int>(cmd[2]);
  int		y = Converter::toInt<int>(cmd[3]);

  Player	*p = new Player(x, y, direction,
				Converter::toInt<int>(cmd[5]),
				cmd[6]);

  _players[num] = p;
  _map.addPlayer(num, p, x, y);
  this->refreshLevelWindow();
  if (_lastSelectedX == x && _lastSelectedY == y)
    this->showCaseContent(x, y);
  _end = false;
}

void		Viewer::receiveCmdPpo(std::vector<std::string> &cmd)
{
  if (cmd.size() != 5)
    throw Error::Communication("Received bad answer from server (ppo)");
  int		num = Converter::toInt<int>(this->takeOffSharp(cmd[1]));
  std::map<int, Player *>::iterator it = _players.find(num);

  if (it != _players.end())
    {
      int		oldx = it->second->getX();
      int		oldy = it->second->getY();
      int		x = Converter::toInt<int>(cmd[2]);
      int		y = Converter::toInt<int>(cmd[3]);

      it->second->setPosture(STRAIGHT);
      _map.erasePlayer(num, oldx, oldy);
      if (num == _target)
	this->focusOn(x - _scrollLeft, y - _scrollUp);
      it->second->setX(x);
      it->second->setY(y);
      it->second->setDirection(convertToDirection(cmd[4]));
      _map.addPlayer(num, it->second, x, y);
      if (_lastSelectedX == x && _lastSelectedY == y)
	this->showCaseContent(x, y);
    }
}

void		Viewer::receiveCmdPlv(std::vector<std::string> &cmd)
{
  if (cmd.size() != 3)
    throw Error::Communication("Received bad answer from server (plv)");
  std::map<int, Player *>::iterator it = _players.find(Converter::toInt<int>(this->takeOffSharp(cmd[1])));

  if (it != _players.end())
    {
      it->second->setLevel(Converter::toInt<int>(cmd[2]));
      this->refreshLevelWindow();
    }
}

void		Viewer::receiveCmdPin(std::vector<std::string> &cmd)
{
  if (cmd.size() != 11)
    throw Error::Communication("Received bad answer from server (pin)");
  std::map<int, Player *>::iterator it = _players.find(Converter::toInt<int>(this->takeOffSharp(cmd[1])));

  if (it != _players.end())
    {
      it->second->setX(Converter::toInt<int>(cmd[2]));
      it->second->setY(Converter::toInt<int>(cmd[3]));
      (*it->second)["food"] = Converter::toInt<int>(cmd[4]);
      (*it->second)["linemate"] = Converter::toInt<int>(cmd[5]);
      (*it->second)["deraumere"] = Converter::toInt<int>(cmd[6]);
      (*it->second)["sibur"] = Converter::toInt<int>(cmd[7]);
      (*it->second)["mendiane"] = Converter::toInt<int>(cmd[8]);
      (*it->second)["phiras"] = Converter::toInt<int>(cmd[9]);
      (*it->second)["thystame"] = Converter::toInt<int>(cmd[10]);
    }
}

void		Viewer::receiveCmdPex(std::vector<std::string> &cmd)
{
  if (cmd.size() != 2)
    throw Error::Communication("Received bad answer from server (pex)");
}

void		Viewer::receiveCmdPbc(std::vector<std::string> &cmd)
{
  std::map<int, Player *>::iterator it = _players.find(Converter::toInt<int>(this->takeOffSharp(cmd[1])));
  if (it != _players.end())
    {
      (*it->second).setPosture(STRAIGHT);
    }
}

void		Viewer::receiveCmdPic(std::vector<std::string> &cmd)
{
  unsigned int	x;
  unsigned int	y;

  std::map<int, Player *>::iterator it = _players.find(Converter::toInt<int>(this->takeOffSharp(cmd[4])));
  if (it != _players.end())
    it->second->setPosture(STRAIGHT);

  x = Converter::toInt<unsigned int>(cmd[1]);
  y = Converter::toInt<unsigned int>(cmd[2]);
  if (x > (unsigned int)this->_map.getWidth() || y > (unsigned int)this->_map.getHeight())
    throw Error::Communication("Received bad answer from server (pic)");
  this->_animations.push_back(new Animation(x, y,
					    INCANTATION_FRAMES,
					    INCANTATION_PADDING,
					    INCANTATION_HEIGHT,
					    this->_incantation[Converter::toInt<int>(cmd[3]) - 1],
					    INCANTATION_PADDING_X,
					    INCANTATION_PADDING_Y));

}

void		Viewer::receiveCmdPie(std::vector<std::string> &cmd)
{
  if (cmd.size() != 4)
    throw Error::Communication("Received bad answer from server (pie)");
}

void		Viewer::receiveCmdPfk(std::vector<std::string> &cmd)
{
  if (cmd.size() != 2)
    throw Error::Communication("Received bad answer from server (pfk)");

  std::map<int, Player *>::iterator it = _players.find(Converter::toInt<int>(this->takeOffSharp(cmd[1])));
  if (it != _players.end())
    {
      (*it->second).setPosture(SAT);
    }
}

void		Viewer::receiveCmdPdr(std::vector<std::string> &cmd)
{
  if (cmd.size() != 3)
    throw Error::Communication("Received bad answer from server (pdr)");
  std::map<int, Player *>::iterator it = _players.find(Converter::toInt<int>(this->takeOffSharp(cmd[1])));

  if (it != _players.end())
    {
      Case		*obj = _map.find(it->second->getX(), it->second->getY());

      if (obj)
	{
	  std::string const	&resource = _resourceTranslator[cmd[2]];

	  (*it->second)[resource] = (*it->second)[resource] - 1;
	  (*obj)[resource] = (*obj)[resource] + 1;
	}
    }
}

void		Viewer::receiveCmdPgt(std::vector<std::string> &cmd)
{
  if (cmd.size() != 3)
    throw Error::Communication("Received bad answer from server (pgt)");
  std::map<int, Player *>::iterator it = _players.find(Converter::toInt<int>(this->takeOffSharp(cmd[1])));

  if (it != _players.end())
    {
      Case		*obj = _map.find(it->second->getX(), it->second->getY());

      if (obj)
	{
	  std::string const	&resource = _resourceTranslator[cmd[2]];

	  (*it->second)[resource] = (*it->second)[resource] + 1;
	  (*obj)[resource] = (*obj)[resource] - 1;
	  if (_map.isCaseEmpty(obj))
	    {
	      _map.pop(obj);
	      delete obj;
	    }
	}
      it->second->setPosture(BENT);
    }
}

void		Viewer::receiveCmdPdi(std::vector<std::string> &cmd)
{
  if (cmd.size() != 2)
    throw Error::Communication("Received bad answer from server (pdi)");

  int num = Converter::toInt<int>(this->takeOffSharp(cmd[1]));
  std::map<int, Player *>::iterator it = _players.find(num);

  if (it != _players.end())
    {
      _map.erasePlayer(it->first, it->second->getX(), it->second->getY());
      if (_lastSelectedX == _players[num]->getX() && _lastSelectedY == _players[num]->getY())
	this->showCaseContent(_players[num]->getX(), _players[num]->getY());
      _players.erase(num);
      this->refreshLevelWindow();
      _target = -1;
    }
}

void		Viewer::receiveCmdEnw(std::vector<std::string> &cmd)
{
  if (cmd.size() != 5)
    throw Error::Communication("Received bad answer from server (enw)");
  std::map<int, Player *>::iterator it = _players.find(Converter::toInt<int>(this->takeOffSharp(cmd[2])));

  if (it != _players.end())
    {
      int			x = it->second->getX();
      int			y = it->second->getY();
      float			f = Converter::toInt<int>(takeOffSharp(cmd[1]));
      Egg			*egg = new Egg(x, y);
      Case			*obj = _map.find(x, y);

      if (x < 0 || y < 0 || x >= this->_map.getWidth() || y >= this->_map.getHeight())
	throw Error::Communication("Invalid position (enw)");
      _eggs[Converter::toInt<int>(this->takeOffSharp(cmd[1]))] = egg;
      if (obj)
	(*obj)[f] = egg;
      else
	{
	  obj = new Case(x, y);

	  (*obj)[f] = egg;
	  _map.push(obj);
	}
    }
}

void		Viewer::receiveCmdEht(std::vector<std::string> &cmd)
{
  if (cmd.size() != 2)
    throw Error::Communication("Received bad answer from server (eht)");
}

void		Viewer::receiveCmdEbo(std::vector<std::string> &cmd)
{
  if (cmd.size() != 2)
    throw Error::Communication("Received bad answer from server (ebo)");

  int		num = Converter::toInt<int>(this->takeOffSharp(cmd[1]));
  std::map<int, Egg *>::iterator it = _eggs.find(num);

  if (it != _eggs.end())
    {
      Egg		*egg = it->second;

      _map.eraseEgg(num, egg->getX(), egg->getY());
      _eggs.erase(num);
      delete egg;
    }
}

void		Viewer::receiveCmdEdi(std::vector<std::string> &cmd)
{
  if (cmd.size() != 2)
    throw Error::Communication("Received bad answer from server (edi)");

  int		num = Converter::toInt<int>(this->takeOffSharp(cmd[1]));

  std::map<int, Egg *>::iterator it = _eggs.find(num);
  if (it != _eggs.end())
    {
      Egg		*egg = it->second;

      _map.eraseEgg(num, it->second->getX(), it->second->getY());
      _eggs.erase(num);
      delete egg;
    }
}

void		Viewer::receiveCmdSgt(std::vector<std::string> &cmd)
{
  if (cmd.size() != 2)
    throw Error::Communication("Received bad answer from server (sgt)");
  int		time = Converter::toInt<int>(cmd[1]);

  if (time > 0)
    {
      _t = time;
      _pause = false;
    }
  else
    _pause = true;
}

void		Viewer::receiveCmdSeg(std::vector<std::string> &cmd)
{
  if (cmd.size() != 2)
    throw Error::Communication("Received bad answer from server (seg)");
  _end = true;
  _winner = cmd[1];
}

void		Viewer::receiveCmdSmg(std::vector<std::string> &cmd)
{
  std::string	total = "Server: ";
  std::vector<std::string>::iterator	it;

  it = cmd.begin();
  it++;
  for (; it != cmd.end() ; ++it)
    {
      total += " " + *it;
    }
  this->showMsg(total);
}

void		Viewer::receiveCmdSuc(std::vector<std::string> &/*cmd*/)
{
  throw Error::Communication("The impossible happened ! (received suc cmd)");
}

void		Viewer::receiveCmdSbp(std::vector<std::string> &/*cmd*/)
{
  throw Error::Communication("The impossible happened ! (received sbp cmd)");
}

void		Viewer::updateInformations()
{
  std::list<std::string>::iterator	it;
  std::map<std::string, void (Viewer::*)(std::vector<std::string> &)>::const_iterator	call;
  std::auto_ptr<std::vector<std::string> > cmd;
  bool		update = false;

  _mutex.lock();
  update = !_cmds.empty();
  it = _cmds.begin();
  while (it != _cmds.end())
    {
      cmd = Converter::explode(*it, ' ');
      call = _receivedCmds.find((*cmd)[0]);
      if (call != _receivedCmds.end())
	{
	  try
	    {
	      (this->*(call->second))(*cmd);
	    }
	  catch (std::exception const &e)
	    {
	      std::cerr << e.what() << std::endl;
	      exit(EXIT_FAILURE);
	    }
	}
      it = _cmds.erase(it);
    }
  _mutex.unlock();
  if (update && !_end)
    this->showMap();
  if (!_end && _timer.GetElapsedTime() > 1 / (_t > 0 ? _t : 1))
    {
      this->checkAnimations();
      _timer.Reset();
    }
}

void		*Viewer::run(void */*arg*/)
{
  std::string	res;
  bool		retry = false;

  this->getNextResponse(res);
  _mutex.lock();
  if (!res.empty())
    _cmds.push_back(res);
  _mutex.unlock();
  _wait.signal();
  while (1)
    {
      try
	{
	  this->getNextResponse(res);
	}
      catch (const std::exception &e)
	{
	  std::cerr << e.what() << std::endl;
	  retry = true;
	  //_end = true;
	  //_winner = "Trying to reconnect";
	}
      if (retry)
      {
	this->_teamNames.clear();
	this->_receivedCmds.clear();
	this->_players.clear();
	this->_eggs.clear();
	try
       	{
  	  connect();
          this->writeServer("GRAPHIC\n");
	  retry = false;
	  //_end = false;
	}
	catch (const std::exception &e)
	{
	  sleep(1);
	}
      }
      _mutex.lock();
      if (!res.empty())
	_cmds.push_back(res);
      _mutex.unlock();
    }
  return (NULL);
}

void		Viewer::sendCmdMsz()
{
  writeServer("msz\n");
}

void		Viewer::sendCmdBct()
{
  writeServer("bct\n");
}

void		Viewer::sendCmdMct()
{
  writeServer("mct\n");
}

void		Viewer::sendCmdTna()
{
  writeServer("tna\n");
}

void		Viewer::sendCmdPpo(int num)
{
  writeServer("ppo " + Converter::toString<int>(num) + "\n");
}

void		Viewer::sendCmdPlv(int num)
{
  writeServer("plv " + Converter::toString<int>(num) + "\n");
}

void		Viewer::sendCmdPin(int num)
{
  writeServer("pin " + Converter::toString<int>(num) + "\n");
}

void		Viewer::sendCmdSgt()
{
  writeServer("sgt\n");
}

void		Viewer::sendCmdSst(int t)
{
  writeServer("sst " + Converter::toString<int>(t) + "\n");
}

e_direction	Viewer::convertToDirection(const std::string &ref)
{
  if (ref == "1")
    return (RIGHTUP);
  else if (ref == "2")
    return (RIGHTBOTTOM);
  else if (ref == "3")
    return (LEFTBOTTOM);
  else
    return (LEFTUP);
}

std::string	&Viewer::takeOffSharp(std::string &src) const
{
  if (src[0] == '#')
    src.erase(0, 1);
  if (src.empty())
    throw Error::Communication("Server send a fake number");
  return (src);
}
