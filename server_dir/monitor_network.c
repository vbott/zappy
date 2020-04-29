/*
** monitor_network for zappy in /home/snap/projects/zappy/server_dir
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Thu 16 Jun 2011 06:57:38 PM CEST botton vivien
** Last update Thu 16 Jun 2011 06:57:38 PM CEST botton vivien
*/

#include <stdlib.h>
#include <string.h>
#include "server.h"

typedef struct
{
  char			*cmd;
  void			(*func)(t_interface*, char *);
}		t_func;

static const t_func	gl_func[] = {
	{"msz", &msz},
	{"bct", &bct},
	{"mct", &mct},
	{"tna", &tna},
	{"ppo", &ppo},
	{"plv", &plv},
	{"pin", &pin},
	{"sgt", &sgt},
	{"sst", &sst}
};

static int			monitor_parse(char *line, void *arg)
{
  size_t	i;
  char		*argument;

  argument = NULL;
  strtok_r(line, " ", &argument);
  for (i = 0; i < sizeof(gl_func) / sizeof(t_func); i++)
  {
    if (!strcmp(gl_func[i].cmd, line))
    {
      gl_func[i].func((t_interface*)arg, argument);
      return (0);
    }
  }
 add_packet((t_interface*)arg, "suc\n");
 return (0);
}

static void			monitor_close(t_interface *interface)
{
  t_zappy       		*zappy;
  t_list			*tmp;
  t_list	                *prev;

  prev = NULL;
  zappy = (t_zappy*)interface->userdata;
  for (tmp = zappy->monitors; tmp; tmp = tmp->next)
  {
    if (((t_monitor*)tmp->value)->network->interface == interface)
    {
      if (prev)
	prev->next = tmp->next;
      else
	zappy->monitors = tmp->next;
      free(((t_monitor*)tmp->value)->network);
      free(tmp->value);
      free(tmp);
      break ;
    }
    prev = tmp;
  }
  close_interface(interface);
}

void			add_monitor(t_zappy *zappy, t_interface *interface)
{
  t_monitor		*monitor;
  t_rb_tree		*client;
  t_list		*team;
  t_list		*egg;

  monitor = xmalloc(sizeof(*monitor));
  monitor->network = xmalloc(sizeof(t_network));
  monitor->network->zappy = zappy;
  monitor->network->interface = interface;
  push_front(&zappy->monitors, monitor);
  interface->hangup = &monitor_close;
  interface->parsing = &monitor_parse;
  msz(interface, NULL);
  sgt(interface, NULL);
  mct(interface, NULL);
  tna(interface, NULL);
  for (client = zappy->clients.last; client; client = client->prev)
    pnw2(interface, (t_client*)client->value);
  for (team = zappy->teams; team; team = team->next)
   for (egg = ((t_team*)team->value)->egg; egg; egg = egg->next)
     enw2(interface, (t_client*)egg->value);
}
