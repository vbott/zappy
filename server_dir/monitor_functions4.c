/*
** monitor_functions4 for zappy in /home/snap/projects/zappy/server_dir
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Wed 22 Jun 2011 05:50:00 PM CEST botton vivien
** Last update Wed 22 Jun 2011 05:50:00 PM CEST botton vivien
*/

#include <stdio.h>
#include "server.h"

void		eht(char *buffer, int *size, t_client *egg)
{
  *size = sprintf(buffer, "eht %u\n", egg->id);
}

void		ebo(char *buffer, int *size, t_client *egg)
{
  *size = sprintf(buffer, "ebo %u\n", egg->id);
}

void		edi(char *buffer, int *size, t_client *egg)
{
  *size = sprintf(buffer, "edi %u\n", egg->id);
}

void		ppo2(char *buffer, int *size, t_client *client)
{
  *size = sprintf(buffer, "ppo %u %d %d %u\n",
	 client->id, client->block->x, client->block->y, client->direction);
}

void		plv2(char *buffer, int *size, t_client *client)
{
  *size = sprintf(buffer, "plv %u %u\n", client->id, client->level);
}
