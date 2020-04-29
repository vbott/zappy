#include <iostream>
#include <string.h>
#include "AI.hpp"
#include "Converter.hpp"
#include "Error_Arguments.hpp"
#include "Error_Connection.hpp"
#include "Error_Parsing.hpp"

extern size_t ressourcesNeeded[8][7];

void		AI::treatNewPlayer()
{
  ++this->nb_players;
  if (this->isLast)
    {
      std::string nbPlayers = Converter::toString<int>(this->nb_players);
      this->urgentCmd.push("broadcast " + this->team_name + " nb_players " + nbPlayers);
      this->isLast = false;
    }
}

void		AI::treatMsg(std::string const & msg, std::string const &cmd)
{
  std::auto_ptr<std::vector<std::string> >	content;
  int	songDirection;

  content = Converter::explode(msg, ',');
  if ((*content).size() >= 2 && (*content)[1].find(this->team_name) == 0)
    {
      songDirection = Converter::toInt<int>((*Converter::explode((*content)[0], ' '))[1]);
      content = Converter::explode((*content)[1], ' ');
      if ((*content).size() >= 3 && (*content)[1] == "incantation" &&
	  Converter::toInt<size_t>((*content)[2]) == this->level)
	addBroadcastCoord(songDirection, cmd);
      else if ((*content).size() == 2 && (*content)[1] == "new_player")
	treatNewPlayer();
      else if ((*content).size() == 3 && (*content)[1] == "nb_players" && this->isLast)
	{
	  this->nb_players = Converter::toInt<int>((*content)[2]);
	  this->id = this->nb_players - 1;
	}
    }
  else if (msg.find("message 0,incantationFail") == 0)
    this->endIncantation = FAIL;
}
