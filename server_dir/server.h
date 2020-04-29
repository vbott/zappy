/*
** server for zappy in /home/snap/projects/zappy/server_dir
**
** Made by botton vivien
** Login   <botton_v@epitech.net>
**
** Started on  Mon 13 Jun 2011 04:01:16 PM CEST botton vivien
** Last update Mon 13 Jun 2011 04:01:16 PM CEST botton vivien
*/

#ifndef		_SERVER_H_
# define 	_SERVER_H_

# include <unistd.h>
# include "net.h"
# include "octree.h"
# include "rb_tree/tree.h"

# define BUFFER_SIZE 	8192
# define OK 		"ok\n"
# define KO		"ko\n"

# define EAT		126
# define HATCHING	600

typedef struct		s_list
{
  void			*value;
  struct s_list		*next;
}			t_list;

typedef struct		s_dlist
{
  void			*value;
  struct s_dlist	*next;
  struct s_dlist	*prev;
}			t_dlist;

typedef struct
{
  size_t		stock[7];
  t_dlist		*players;
  int			x;
  int			y;
}			t_case;

typedef	struct		s_interface
{
  void			(*read)(struct s_interface *);
  void			(*write)(struct s_interface *);
  void			(*hangup)(struct s_interface *);
  void			*userdata;
  int			socket;
  int			epoll_fd;
  char			*buffer;
  int			index;
  int			incorrect;
  t_list		*packet_to_send;
  t_list		*last_packet;
  void			*arg;
  int 			(*parsing)(char *line, void *arg);
}			t_interface;

typedef struct
{
 char			*port;
 int			epoll_fd;
 int			server_socket;
 int			nb_team;
 int			t;
 int			x;
 int			y;
 int			limit;
 size_t			nbclients;
 size_t			nbplayers;
 size_t			threshold;
 t_interface		*accept_interface;
 long unsigned int	cycle;
 t_octree		*map;
 t_list			*teams;
 t_tree			clients;
 t_list			*monitors;
 t_list			*actions;
 size_t			bread;
}			t_zappy;

typedef struct
{
  int			nb_player;
  int			nb_max;
  t_list		*egg;
  t_list		*client;
  t_list		*lastegg;
  t_list		*lastclient;
  size_t		nbhl;
  char			*name;
}			t_team;

typedef struct
{
  t_zappy		*zappy;
  t_interface		*interface;
}			t_network;

typedef struct
{
  t_network		*network;
  size_t		parent;
  size_t		id;
  size_t		level;
  t_team		*team;
  size_t		inventory[7];
  int			direction;
  t_list		*actions;
  t_dlist		node;
  long unsigned int	cycle;
  t_case		*block;
}			t_client;

typedef struct
{
  t_network     	*network;
}			t_monitor;

typedef struct
{
  long unsigned int	cycle;
  int			system;
  void			*client;
  char			*buffer;
  void			(*func)(t_list*);
}			t_action;

typedef struct
{
  char			option;
  int			(*func)(int ac, char **av, t_zappy *zappy);
}			t_arg;

typedef struct
{
  t_list		*list;
  t_list		*used;
  size_t		current;
  size_t		max;
  size_t		nb;
  size_t		cycle;
}			t_pool;

typedef struct
{
  size_t		size;
  size_t		index;
  char			*buffer;
}			t_packet;

typedef struct
{
  char			*buffer;
  size_t		size;
  size_t		nb;
}			t_buffer;

int		x_arg(int ac, char **av, t_zappy *zappy);
int		y_arg(int ac, char **av, t_zappy *zappy);
int		port(int ac, char **av, t_zappy *zappy);
int		limit(int ac, char **av, t_zappy *zappy);
int		timevalue(int ac, char **av, t_zappy *zappy);
int		teams(int ac, char **av, t_zappy *zappy);

void		add_team(char *, t_zappy *);

/* add_packet.c */
void		add_packet(t_interface *interface, char *content);
void		add_packet_buffer(t_interface *interface, char *content);
void		add_packet_size(t_interface *interface, char *content,
				size_t size);
void		add_packet_buffer_size(t_interface *interface, char *content,
				       size_t size);

/* buffer_pool.c */
char		*get_buffer(size_t size);
void		release_buffer(char *buffer);
void		get_same_buffer(char *buffer);

/* packet_pool.c */
t_list		*get_packet();
void		release_packet(t_list *packet);

/* build_map.c */
t_case		*get_case_map(t_zappy *zappy, size_t x, size_t y);
void		release_ressources(t_zappy *zappy, size_t inventory[7]);
void		build_map(t_zappy *zappy);

/* case_pool.c */
t_case		*get_case();
void		release_case(t_case *block);

/* change_position.c */
void		change_position(t_client *client, int x, int y);

/* free_player.c */
void		free_player(t_client *client);

/* client.c */
void		client_read(t_interface *interface);
void		close_client(t_interface *interface);
t_client	*create_client(t_team *team, t_zappy *zappy);
void		add_client(t_zappy *zappy, t_team *team,
			   t_interface *interface);

/* handle_player_action.c */
void		handle_player_action(t_zappy *zappy);
int		client_parse(char *line, void *arg);

/* list.c */
void		push_front(t_list **list, void *value);
void		sorted_insert(t_list **list, t_list *node,
			      int (*func)(void*, void*));
void		push_front_node(t_list **list, t_list *node);

/* network_loop.c */
void		determine_type(t_interface *);
void		network_loop(t_zappy *zappy);

/* packet.c */
void		mod_epoll(t_interface *interface, int flags);
void		remove_packet(t_interface *interface);
void		send_packet(t_interface *interface);

/* player_action.c */
void		player_inventaire(t_list*);
void		player_expulse(t_list*);

/* player_broadcast.c */
void		player_broadcast(t_list*);

/* player_connect_nbr.c */
void		connect_nbr(t_client *client);
void		player_connect(t_list*);
void		send_map_info(t_client *client);

/* player_fork.c */
void		player_fork(t_list*);

/* player_invocation.c */
void		player_incantation(t_list*);

/* player_move.c */
void		player_avance(t_list*);
void		player_droite(t_list*);
void		player_gauche(t_list*);

/* player_object.c */
void		player_prend(t_list*);
void		player_pose(t_list*);
void		player_incantation(t_list*);

/* player_verif_incantation.c */
int		verif_incantation(t_client *client, t_case *block, int end);

/* player_voir.c */
void		player_voir(t_list*);

/* pool.c */
t_list		*get_elem_pool(t_pool *pool, int used);
void		release_elem_pool(t_pool *pool, void *value, int used);

/* xmalloc.c */
void		*xmalloc(size_t);

/* */
void		send_packet(t_interface *);

/* interface.c */
void		add_interface(t_zappy *zappy, t_interface *interface,
			      int socket, int flags);
void		remove_interface(t_interface *interface);

/* utils.c */
int		min(int a, int b);
int		listen_to(char *port);

/* reset_zappy.c */
void		reset_zappy(t_team *team, t_zappy *zappy);

/* init.c */
void		set_non_blocking(int sock);
void		default_value(t_zappy *zappy);
int		init(t_zappy *zappy);
void            close_interface(t_interface *);

/* handle_args.c */
int		handle_args(int ac, char **av, t_zappy *zappy);

/* circular_buffer.c */
void		circular_buffer(t_interface *interface);

/* network_loop.c */
int             choose_type(char *line, void *arg);

/* network_monitor.c */
void		add_monitor(t_zappy *zappy,
			    t_interface *interface);

/* init_stdin */
void 		init_stdin(t_zappy *zappy);

/* push_actions.c */
int		cmp_action(void *value1, void *value2);
void		push_system_action(t_client *client, int cycle,
				   void (*func)(t_list *), char *arg);
void		push_system_action_2(t_zappy *zappy, int cycle,
				     void (*func)(t_list *), char *arg);
void		push_action(t_client *client, int cycle,
			    void (*func)(t_list *), char *arg);

/* system_actions.c */
void		hungry(t_list *node);
void		restore_food(t_list *node);

/* monitor_functions.c */
void		msz(t_interface *interface, char *arg);
void		bct(t_interface *interface, char *arg);
void		mct(t_interface *interface, char *arg);
void		tna(t_interface *interface, char *arg);
void		ppo(t_interface *interface, char *arg);
void		plv(t_interface *interface, char *arg);
void		pin(t_interface *interface, char *arg);
void		sgt(t_interface *interface, char *arg);
void		sst(t_interface *interface, char *arg);

/* broadcast_monitor_msg.c */
void		broadcast_monitor(t_zappy *zappy, t_client *client,
	       	void (*func)(char *, int *, t_client *));
void		broadcast_monitor_value(t_zappy *zappy, t_client *client,
	       	void *value, void (*func)(char *, int *, t_client *, void *));
void		broadcast_monitor_msg(t_zappy *zappy, t_client *client,
	       	char *msg, void (*func)(char *, int *, t_client *, char *));

void		pnw(char *buffer, int *size, t_client *client);
void		pnw2(t_interface *interface, t_client *client);
void		pex(char *buffer, int *size, t_client *client);
void		pbc(char *buffer, int *size, t_client *client, char *);
void		pin2(char *buffer, int *size, t_client *client);
void		bct2(char *buffer, int *size, t_client *client, void *);
void		pic(char *buffer, int *size, t_client *client, void *);
void		pie(char *buffer, int *size, t_client *client, void *);
void		pfk(char *buffer, int *size, t_client *client);
void		pdr(char *buffer, int *size, t_client *client, void *);
void		pgt(char *buffer, int *size, t_client *client, void *);
void		pdi(char *buffer, int *size, t_client *client);
void		enw(char *buffer, int *size, t_client *client);
void		enw2(t_interface *interface, t_client *client);
void		eht(char *buffer, int *size, t_client *client);
void		ebo(char *buffer, int *size, t_client *client);
void		edi(char *buffer, int *size, t_client *client);
void		ppo2(char *buffer, int *size, t_client *client);
void		plv2(char *buffer, int *size, t_client *client);
void		seg(char *buffer, int *size, t_client *client, char *);
void		smg(char *buffer, int *size, t_client *client, char *);
void		sgt2(char *buffer, int *size, t_client *client, void *);

#endif /* _SERVER_H_ */
