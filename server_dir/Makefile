##
## Makefile for zappy in /home/chambi_r//proj/zappy/client_dir
##
## Made by raphael chambily
## Login   <chambi_r@epitech.net>
##
## Started on  Mon Jun 13 17:53:54 2011 raphael chambily
## Last update Tue Jun 14 14:44:48 2011 raphael chambily
##

NAME		= ../server

SRCS		= main.c			\
		  add_packet.c			\
		  args.c			\
		  args_2.c			\
		  buffer_pool.c			\
		  build_map.c			\
		  broadcast_monitor.c		\
		  case_pool.c			\
		  change_position.c		\
		  client.c			\
		  handle_player_action.c	\
		  list.c			\
		  utils.c			\
		  monitor_functions.c		\
		  monitor_network.c		\
		  monitor_notify.c		\
		  monitor_functions2.c		\
		  monitor_functions3.c		\
		  monitor_functions4.c		\
		  monitor_functions5.c		\
		  monitor_functions6.c		\
		  network_loop.c		\
		  octree.c			\
		  octree_node.c			\
		  find_octree.c			\
		  free_player.c			\
		  packet_pool.c			\
		  player_action.c		\
		  player_broadcast.c		\
		  player_connect_nbr.c		\
		  player_fork.c			\
		  player_incantation.c		\
		  player_move.c			\
		  player_object.c		\
		  player_verif_incantation.c	\
		  player_voir.c			\
		  pool.c			\
		  pop_octree.c			\
		  push_octree.c			\
		  reset_zappy.c			\
		  interface.c			\
		  init.c			\
		  handle_args.c			\
		  circular_buffer.c		\
		  push_actions.c		\
		  system_actions.c		\
		  packet.c			\
		  rb_tree/change_parent.c	\
		  rb_tree/delete.c		\
		  rb_tree/delete_case.c		\
		  rb_tree/delete_swap.c		\
		  rb_tree/insert.c		\
		  rb_tree/rotate.c		\
		  rb_tree/utils_functions.c	\
		  smg.c				\
		  xmalloc.c			\
		  xnet.c			\
		  xnet2.c

OBJS		= $(SRCS:.c=.o)

RM		= rm -f

CC		= gcc

CFLAGS		+= -W -Wall -Wextra -O2 -pipe

LDFLAGS		= -lm

$(NAME)		: $(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

all		: $(NAME)

clean		:
		$(RM) $(OBJS)

fclean		: clean
		$(RM) $(NAME)

re		: fclean all

.PHONY		: all clean fclean re
