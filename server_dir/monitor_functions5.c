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

void		pfk(char *buffer, int *size, t_client *client)
{
  *size = sprintf(buffer, "pfk %u\n", client->id);
}

void		pdr(char *buffer, int *size, t_client *client, void *ressource)
{
  *size = sprintf(buffer, "pdr %u %u\n", client->id, (int)ressource);
}

void		pgt(char *buffer, int *size, t_client *client, void *ressource)
{
  *size = sprintf(buffer, "pgt %u %u\n", client->id, (int)ressource);
}

void		pdi(char *buffer, int *size, t_client *client)
{
  *size = sprintf(buffer, "pdi %u\n", client->id);
}

void		enw(char *buffer, int *size, t_client *client)
{
  *size = sprintf(buffer, "enw %u %u %d %d\n",
		  client->id, client->parent,
		  client->block->x, client->block->y);
}

