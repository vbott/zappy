#include <iostream>
#include <string.h>
#include "AI.hpp"
#include "Converter.hpp"
#include "Error_Arguments.hpp"
#include "Error_Connection.hpp"
#include "Error_Parsing.hpp"

extern size_t ressourcesNeeded[8][7];

bool		AI::enoughRessources()
{
  std::map<std::string, int>::const_iterator it;

  for (it = joinMap.begin(); it != joinMap.end(); ++it)
    {
      if ((*it).first != PLAYER && (*it).first != FOOD && this->inventory[(*it).first] < ressourcesNeeded[this->level - 1][(*it).second])
	return (false);
    }
  return (true);
}

void		AI::popRessources()
{
  std::map<std::string, int>::const_iterator it;

  for (it = joinMap.begin(); it != joinMap.end(); ++it)
    {
      if ((*it).first != PLAYER && (*it).first != FOOD)
	{
	  while (this->inventory[(*it).first] > ressourcesNeeded[this->level - 1][(*it).second])
	    {
	      if (sendCmdToServer(std::string("pose ") + (*it).first))
		this->inventory[(*it).first] -= 1;
	    }
	}
    }
}

void		AI::prepareIncantationCase()
{
  size_t	posed;
  std::map<std::string, int>::const_iterator it;

  for (it = joinMap.begin(); it != joinMap.end(); ++it)
    if ((*it).first != PLAYER)
      {
	if (voirMap[Pos][(*it).first] < ressourcesNeeded[this->level - 1][(*it).second])
	  {
	    for (posed = voirMap[Pos][(*it).first]; posed != ressourcesNeeded[this->level - 1][(*it).second]; ++posed)
	      if (sendCmdToServer(std::string("pose ") + (*it).first))
		this->inventory[(*it).first] -= 1;
	  }
	else
	  for (posed = voirMap[Pos][(*it).first]; posed != ressourcesNeeded[this->level - 1][(*it).second]; --posed)
	    if (sendCmdToServer(std::string("prend ") + (*it).first))
	      this->inventory[(*it).first] += 1;
      }
}

bool		AI::callForTheOthers()
{
  if (voirMap.find(Pos) == voirMap.end())
    this->voirCmd();
  while (voirMap[Pos][PLAYER] < ressourcesNeeded[this->level - 1][joinMap[PLAYER]])
    {
      this->sendCmdToServer(std::string("broadcast ") + this->team_name +
			    std::string(" incantation ") + Converter::toString<int>(this->level));
      this->voirCmd();
      this->inventoryCmd();
      if (!this->broadcastCoords.empty() || this->inventory[FOOD] < 8)
	return (false);
    }
  if (voirMap[Pos][PLAYER] > ressourcesNeeded[this->level - 1][joinMap[PLAYER]])
    {
      this->sendCmdToServer("broadcast incantationFail");
      return (false);
    }
  return (true);
}

bool		AI::finalizeIncantation()
{
  std::string		fill;
  int			i = 100000;

  this->endIncantation = INCANTATING;
  do {
    this->inventoryCmd();
    if (this->inventory[FOOD] < 6)
      return (false);
    --i;
  } while (this->endIncantation == INCANTATING && i > 0);
  if (this->endIncantation == FAIL)
    return (false);
  return (true);
}

bool		AI::checkForIncantationCase()
{
  std::map<std::string, int>::iterator caseIt;
  bool	isGood;

  isGood = true;
  for (caseIt = joinMap.begin(); caseIt != joinMap.end(); ++caseIt)
    {
      if (voirMap.find(Pos) == voirMap.end())
	voirCmd();
      if ((*caseIt).first == PLAYER && voirMap[Pos][(*caseIt).first] == 0)
	isGood = false;
      else if (ressourcesNeeded[this->level - 1][(*caseIt).second] > voirMap[Pos][(*caseIt).first])
	isGood = false;
    }
  return (isGood);
}

void		AI::addBroadcastCoord(size_t dir, std::string const &cmd)
{
  broadcastInfo		to_add;

  if (this->level == 1)
    return ;
  to_add.direction = dir;
  while (!this->coord.empty())
    this->coord.pop();
  if (dir == 1 || dir == 2 || dir == 8)
    to_add.coord = transCoord(0, 1);
  else if (dir == 3 || dir == 4)
    to_add.coord = transCoord(-1, 0);
  else if (dir == 6 || dir == 7)
    to_add.coord = transCoord(1, 0);
  else if (dir == 5)
    to_add.coord = transCoord(0, -1);
  if (dir == 0)
    {
      onIncantationCase = true;
      if (cmd == "avance")
	{
	  this->urgentCmd.push("left");
	  this->urgentCmd.push("left");
	  this->urgentCmd.push("avance");
	}
      return ;
    }
  else
    onIncantationCase = false;
  if (this->broadcastCoords.empty() || to_add.coord != this->broadcastCoords.front().coord)
    this->broadcastCoords.push(to_add);
  if (this->broadcastCoords.size() > 2)
    this->broadcastCoords.pop();
}

void		AI::followBroadcast()
{
  this->onIncantationCase = false;
  while (!this->broadcastCoords.empty())
    {
      this->goToCoord(this->broadcastCoords.front().coord.first, this->broadcastCoords.front().coord.second);
      this->voirCmd();
      this->takeWhatYouNeed(false);
      if (this->onIncantationCase && this->finalizeIncantation())
	{
	  this->onIncantationCase = false;
	  break ;
	}
      this->onIncantationCase = false;
      this->broadcastCoords.pop();
      this->inventoryCmd();
    }
}

void		AI::lookAtIncantation()
{
  if (this->enoughRessources() && this->broadcastCoords.empty())
    {
      this->inventoryCmd();
      if (this->inventory[FOOD] * 126 >= (size_t)(1000 + ((mapSize.first + mapSize.second) / 2) * 7))
	{
	  this->prepareIncantationCase();
	  if (this->broadcastCoords.empty() && (this->level == 1 || this->callForTheOthers()))
	    while (sendAndLookForSpecialAnswer("incantation", "niveau actuel :") == "ko")
	      {
		voirCmd();
		this->prepareIncantationCase();
		if (!this->broadcastCoords.empty() || !this->callForTheOthers())
		  {
		    this->sendCmdToServer("broadcast incantationFail");
		    break ;
		  }
	      }
	}
    }
}
