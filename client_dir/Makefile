##
## Makefile for zappy_client in /home/chambi_r//proj/zappy/client_dir
## 
## Made by raphael chambily
## Login   <chambi_r@epitech.net>
## 
## Started on  Mon Jun 13 17:53:54 2011 raphael chambily
## Last update Sat Jul  9 17:53:26 2011 gianni castellani
##

NAME		=	../client

SRCS		=	main.cpp		\
			Error_Arguments.cpp	\
			Error_Parsing.cpp	\
			Error_Connection.cpp	\
			Converter.cpp		\
			AI.cpp			\
			AI_movements.cpp	\
			AI_incantation.cpp	\
			AI_messages.cpp		\
			Client.cpp

OBJS		=	$(SRCS:.cpp=.o)

RM		=	rm -f

CXX		= g++

CXXFLAGS	+=	-Wall -Wextra -O2

LDFLAGS 	+= -lstdc++ -lm

$(NAME)		: $(OBJS)
		$(CXX) -o $(NAME) $(OBJS) $(LDFLAGS)

all		: $(NAME)

clean		:
		$(RM) $(OBJS)
fclean		:	clean
		$(RM) $(NAME)
re		:	fclean all

.PHONY		:	all clean fclean re

.cpp.o		:
		$(CXX) $(CXXFLAGS) -c $< -o $(<:.cpp=.o)
