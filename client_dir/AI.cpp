#include <iostream>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "AI.hpp"
#include "Converter.hpp"
#include "Error_Arguments.hpp"
#include "Error_Connection.hpp"
#include "Error_Parsing.hpp"

size_t ressourcesNeeded[8][7] = {
  {1,1,0,0,0,0,0},
  {2,1,1,1,0,0,0},
  {2,2,0,1,0,2,0},
  {4,1,1,2,0,1,0},
  {4,1,2,1,3,0,0},
  {6,1,2,3,0,1,0},
  {6,2,2,2,2,2,1},
  {1,9,8,10,5,6,1}
};

void	AI::initCase(Case &myCase) const
{
  myCase[PLAYER] = 0;
  myCase[LINEMATE] = 0;
  myCase[DERAUMERE] = 0;
  myCase[SIBUR] = 0;
  myCase[MENDIANE] = 0;
  myCase[PHIRAS] = 0;
  myCase[THYSTAME] = 0;
  myCase[FOOD] = 0;
}

AI::AI(int ac, char **av)
  : Client(), team_name(""), id(0), nb_players(1), isLast(true), hasLaid(false), hasFork(false)
{
  this->joinMap[PLAYER] = 0;
  this->joinMap[LINEMATE] = 1;
  this->joinMap[DERAUMERE] = 2;
  this->joinMap[SIBUR] = 3;
  this->joinMap[MENDIANE] = 4;
  this->joinMap[PHIRAS] = 5;
  this->joinMap[THYSTAME] = 6;
  this->inventory[LINEMATE] = 0;
  this->inventory[DERAUMERE] = 0;
  this->inventory[SIBUR] = 0;
  this->inventory[MENDIANE] = 0;
  this->inventory[PHIRAS] = 0;
  this->inventory[THYSTAME] = 0;
  this->inventory[FOOD] = 0;
  this->level = 1;
  this->onIncantationCase = false;
  this->endIncantation = INCANTATING;
  this->getConnectionInfos(ac, av);
  this->connect();
  this->recupFirstInfos();

  struct sigaction      act;

  memset(&act, 0, sizeof(act));
  act.sa_handler = SIG_IGN;
  act.sa_flags = SA_NOCLDWAIT | SA_RESTART;
  sigemptyset(&act.sa_mask);
  sigaction(SIGCHLD, &act, NULL);
}

AI::~AI()
{
}

void	AI::recupFirstInfos()
{
  std::auto_ptr<std::vector<std::string> >	tab;
  std::string		fill;

  if (this->team_name == "GRAPHIC")
    throw Error::Arguments("name GRAPHIC forbidden");
  this->getNextResponse(fill);
  this->writeServer(this->team_name + "\n");
  this->getNextResponse(fill);
  if (fill == "ko")
    throw Error::Connection("There's no places in my team on the server");
  this->getNextResponse(fill);
  tab = Converter::explode(fill, ' ');
  if (tab->size() < 2)
    throw Error::Parsing("Bad answer from server");
  this->mapSize.first = Converter::toInt<int>((*tab)[0]);
  this->mapSize.second = Converter::toInt<int>((*tab)[1]);
}

void	AI::getConnectionInfos(int ac, char **av)
{
  std::string	tmp;

  if (ac < 5)
    throw Error::Arguments("Usage : ./client -n team_name -p port [-h host]");
  for (int i = 0; i < ac; ++i)
    {
      tmp = av[i];
      if (tmp == "-n" && ac > i + 1)
	this->team_name = av[i + 1];
      else if (tmp == "-p" && ac > i + 1)
	this->port = av[i + 1];
      else if (tmp == "-h" && ac > i + 1)
	this->host = av[i + 1];
    }
  if (this->host == "")
    this->host = "localhost";
  if (this->team_name == "" || this->port == "")
    throw Error::Arguments("Usage : ./client -n team_name -p port [-h host] :\nBad Argument");
}

bool		AI::inventoryCmd()
{
  std::auto_ptr<std::vector<std::string> >	cases;
  std::auto_ptr<std::vector<std::string> >	objs;
  std::vector<std::string>::iterator		it;
  std::string					fill;

  fill = this->sendAndLookForSpecialAnswer("inventaire", "{");
  if (fill == "ko")
    return (false);
  fill = fill.substr(1, fill.size() - 2);
  cases = Converter::explode(fill, ',');
  for (it = (*cases).begin(); it != (*cases).end(); ++it)
    {
      objs = Converter::explode((*it), ' ');
      if ((*objs).size() >= 2 && (*objs)[0] != "")
	this->inventory[(*objs)[0]] = Converter::toInt<int>((*objs)[1]);
      else if ((*objs).size() >= 3 && (*objs)[1] != "")
	this->inventory[(*objs)[1]] = Converter::toInt<int>((*objs)[2]);
    }
  return (true);
}

void		AI::voirCmd()
{
  std::auto_ptr<std::vector<std::string> >	cases;
  std::auto_ptr<std::vector<std::string> >	objs;
  std::vector<std::string>::iterator		it;
  std::vector<std::string>::iterator		it2;
  Case						list;
  std::string					fill;
  int					x = 0;
  int					y = 0;

  this->voirMap.clear();
  fill = this->sendAndLookForSpecialAnswer("voir", "{");
  fill = fill.substr(1, fill.size() - 2);
  cases = Converter::explode(fill, ',');
  for (it = (*cases).begin(); it != (*cases).end(); ++it)
    {
      initCase(list);
      objs = Converter::explode((*it), ' ');
      for (it2 = (*objs).begin(); it2 != (*objs).end(); ++it2)
	if ((*it2).size())
	  list[*it2] += 1;
      this->voirMap[transCoord(x, y)] = list;
      if (x == y)
	{
	  ++y;
	  x = -y;
	}
      else
	++x;
    }
  this->level = (y > 2 ? y - 1 : 1);
}

void		AI::treatDeath()
{
  throw Error::Arguments("You're dead"); // to change to Exception Death
}

std::string		AI::sendAndLookForSpecialAnswer(std::string const &to_send, std::string const &to_check)
{
  std::string	fill;
  std::string	urgent;

  this->writeServer(to_send + "\n");
  do {
    this->getNextResponse(fill);
    if (fill == "mort")
      this->treatDeath();
    else if (fill.find("message") == 0)
      this->treatMsg(fill, "");
    else if (fill.find("niveau actuel :") == 0)
      this->endIncantation = SUCCESS;
  } while (fill.find(to_check) != 0 && fill != "ko");
  if (!this->urgentCmd.empty())
    {
      urgent = this->urgentCmd.front();
      this->urgentCmd.pop();
      this->sendCmdToServer(urgent);
    }
  return (fill);
}

bool		AI::sendCmdToServer(std::string const & to_send)
{
  std::string	fill;
  std::string	urgent;

  this->writeServer(to_send + "\n");
  do {
    this->getNextResponse(fill);
    if (fill == "mort")
      this->treatDeath();
    else if (fill.find("message") == 0)
      this->treatMsg(fill, to_send);
    else if (fill.find("niveau actuel :") == 0)
      this->endIncantation = SUCCESS;
  } while (fill != "ok" && fill != "ko");
  if (!this->urgentCmd.empty())
    {
      urgent = this->urgentCmd.front();
      this->urgentCmd.pop();
      this->sendCmdToServer(urgent);
    }
  if (fill == "ok")
    return (true);
  return (false);
}

int		AI::connectNbrCmd()
{
  std::string	fill;
  std::string	urgent;

  this->writeServer("connect_nbr\n");
  do {
    this->getNextResponse(fill);
    if (fill == "mort")
      this->treatDeath();
    else if (fill.find("message") == 0)
      this->treatMsg(fill, "");
  } while (fill[0] < '0' || fill[0] > '9');
  if (!this->urgentCmd.empty())
    {
      urgent = this->urgentCmd.front();
      this->urgentCmd.pop();
      this->sendCmdToServer(urgent);
    }
  return (Converter::toInt<int>(fill));
}

void		AI::getId()
{
  std::string const str = "broadcast " + this->team_name + " new_player";
  this->sendCmdToServer(str);
}

Coord		AI::transCoord(int x, int y) const
{
  if (this->direction == UP)
    return (std::make_pair(this->Pos.first + x, this->Pos.second + y));
  if (this->direction == LEFT)
    return (std::make_pair(this->Pos.first - y, this->Pos.second + x));
  if (this->direction == RIGHT)
    return (std::make_pair(this->Pos.first + y, this->Pos.second - x));
  return (std::make_pair(this->Pos.first - x, this->Pos.second - y));
}

void		AI::createAI(char **av)
{
  Coord		prevPos;

  prevPos = this->Pos;
  this->voirCmd();
  this->findCoords(false);
  this->inventoryCmd();
  if (this->inventory[FOOD] > 10)
    {
      int nbrConnect = this->connectNbrCmd();
      if (nbrConnect > 0 && !this->hasFork)
  	{
  	  if (::fork() == 0)
	    ::execv(av[0], av);
	  this->hasFork = true;
	  this->hasLaid = true;
  	}
      else if (!this->hasLaid)
  	{
  	  this->sendCmdToServer("fork");
	  this->hasLaid = true;
  	}
    }
  if (prevPos == this->Pos && this->broadcastCoords.empty())
    this->sendCmdToServer("avance");
}

void		AI::runAI(char **av)
{
  Coord		prevPos;

  this->getId();
  this->Pos = std::make_pair(0,0);
  this->direction = UP;
  while (this->nb_players < 30)
    {
      this->createAI(av);
      if (this->id + 1 < ((this->nb_players / 10) * 10))
	break;
    }
  while (1)
    {
      prevPos = this->Pos;
      if (this->level < 8)
	this->lookAtIncantation();
      this->popRessources();
      this->voirCmd();
      this->findCoords(this->level < 8 && !enoughRessources());
      if (prevPos == this->Pos && this->broadcastCoords.empty())
	this->sendCmdToServer("avance");
    }
}
