/*
** monitor_notify for zappy in /home/snap/projects/zappy/server_dir
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Mon 20 Jun 2011 10:33:00 PM CEST botton vivien
** Last update Mon 20 Jun 2011 10:33:00 PM CEST botton vivien
*/

#include <stdio.h>
#include "server.h"

void		pbc(char *buffer, int *size, t_client *client, char *msg)
{
  *size = sprintf(buffer, "pbc %u %s\n", client->id, msg);
}

void		pic(char *buffer, int *size, t_client *client, void *value)
{
 t_case		*block;
 t_dlist	*list;

 block = (t_case*)value;
 if (!block)
   return ;
 *size = sprintf(buffer, "pic %u %u %u", client->block->x,
		 client->block->y, client->level);
 for (list = block->players; list; list = list->next)
 {
   *size += sprintf(&buffer[*size], (list->next) ? " %u" : " %u\n",
		   ((t_client*)list->value)->id);
 }
}

void		pie(char *buffer, int *size, t_client *client, void *res)
{
  *size = sprintf(buffer, "pie %u %u %u\n", client->block->x,
		  client->block->y, (int)res);
}

