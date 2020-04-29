#include <iostream>
#include <string.h>
#include "AI.hpp"
#include "Converter.hpp"
#include "Error_Arguments.hpp"
#include "Error_Connection.hpp"
#include "Error_Parsing.hpp"

extern size_t ressourcesNeeded[8][7];

bool		distanceComparison(Coord const &case1, Coord const &case2)
{
  if (case1.second < case2.second)
    return (true);
  else if (case1.second > case2.second)
    return (false);
  else if (case1.second % 2 == 0)
    {
      if (case1.first < case2.first)
	return (true);
      return (false);
    }
  else
    {
      if (case1.first < case2.first)
        return (false);
    }
  return (true);
}

bool		AI::somethingInteresting(Case &list, bool all)
{
  Case::iterator	it;

  if (list[PLAYER] > 0)
    return (false);
  for (it = list.begin(); it != list.end(); ++it)
    {
      if ((*it).second > 0)
	{
	  if ((*it).first == FOOD)
	    {
	      if (this->inventory[FOOD] < FOODLIMIT)
		return (true);
	    }
	  else if (all)
	    {
	      int totalNeed = ressourcesNeeded[this->level - 1][joinMap[(*it).first]];
	      totalNeed -= this->inventory[(*it).first];
	      if (totalNeed > 0)
		return (true);
	    }
	}
    }
  return (false);
}

void		AI::takeWhatYouNeed(bool all)
{
  Case::iterator	it;
  std::string		tmp;

  tmp = "prend ";
  if (voirMap.find(Pos) != voirMap.end())
    for (it = voirMap[Pos].begin(); it != voirMap[Pos].end(); ++it)
      {
	if ((*it).second > 0)
	  {
	    if ((*it).first == FOOD)
	      {
		for (size_t i = 0; i != (*it).second && this->inventory[(*it).first] < FOODLIMIT; ++i)
		  {
		    if (sendCmdToServer(tmp + (*it).first))
		      this->inventory[(*it).first] += 1;
		  }
	      }
	    else if (all)
	      {
		for (size_t i = 0; i != (*it).second; ++i)
		  {
		    int totalNeed = ressourcesNeeded[this->level - 1][joinMap[(*it).first]];
		    totalNeed -= this->inventory[(*it).first];
		    if (totalNeed > 0)
		      {
			if (sendCmdToServer(tmp + (*it).first))
			  this->inventory[(*it).first] += 1;
		      }
		  }
	      }
	  }
      }
}

void		changeDirection(enum e_direction &to_inc, int inc)
{
  if (to_inc + inc > 3)
    to_inc = LEFT;
  else if (to_inc + inc < 0)
    to_inc = DOWN;
  else
    to_inc = static_cast<enum e_direction>(to_inc + inc);
}

void		AI::turn(enum e_direction to_go)
{
  if (to_go == this->direction)
    return ;
  if (this->direction + 1 == to_go || (this->direction == DOWN && to_go == LEFT))
    {
      if (this->sendCmdToServer("droite"))
	changeDirection(this->direction, 1);
    }
  else if (this->direction - 1 == to_go || (this->direction == LEFT && to_go == DOWN))
    {
      if (this->sendCmdToServer("gauche"))
	changeDirection(this->direction, -1);
    }
  else
    {
      if (this->sendCmdToServer("gauche"))
	changeDirection(this->direction, -1);
      if (this->sendCmdToServer("gauche"))
	changeDirection(this->direction, -1);
    }
}

void		AI::goToCoord(int x, int y)
{
  while (this->Pos.second != y)
    {
      if (y > this->Pos.second)
	{
	  this->turn(UP);
	  if (this->sendCmdToServer("avance"))
	    ++this->Pos.second;
	}
      else if (y < this->Pos.second)
	{
	  this->turn(DOWN);
	  if (this->sendCmdToServer("avance"))
	    --this->Pos.second;
	}
    }
  while (this->Pos.first != x)
    {
      if (x > this->Pos.first)
	{
	  this->turn(RIGHT);
	  if (this->sendCmdToServer("avance"))
	    ++this->Pos.first;
	}
      else if (x < this->Pos.first)
	{
	  this->turn(LEFT);
	  if (this->sendCmdToServer("avance"))
	    --this->Pos.first;
	}
    }
}

void		AI::followCoords(bool all)
{
  while (!this->coord.empty() && this->broadcastCoords.empty())
    {
      this->goToCoord(this->coord.front().first, this->coord.front().second);
      this->takeWhatYouNeed(all);
      if (!this->coord.empty())
	this->coord.pop();
    }
  this->inventoryCmd();
  if (!this->broadcastCoords.empty())
    this->followBroadcast();
}

void		AI::findCoords(bool all)
{
  std::map<Coord, Case>::iterator	it;
  std::list<Coord>		tmp;
  std::list<Coord>::iterator	itTmp;

  for (it = voirMap.begin(); it != voirMap.end(); ++it)
    {
      if (somethingInteresting((*it).second, all))
	tmp.push_back((*it).first);
    }
  if (tmp.size() > 1)
    tmp.sort(distanceComparison);
  for (itTmp = tmp.begin(); itTmp != tmp.end(); ++itTmp)
    this->coord.push(*itTmp);
  this->followCoords(all);
}
