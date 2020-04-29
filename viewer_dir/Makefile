NAME	= ../viewer

SRCS_DIR = ./srcs
COMMON_DIR = ../client_dir
INCLUDES_DIR = ./includes

SRCS	= $(SRCS_DIR)/main.cpp		\
	  $(SRCS_DIR)/Animation.cpp	\
	  $(SRCS_DIR)/Viewer.cpp	\
	  $(SRCS_DIR)/Map.cpp		\
	  $(COMMON_DIR)/Client.cpp	\
	  $(COMMON_DIR)/Error_Arguments.cpp\
	  $(COMMON_DIR)/Error_Parsing.cpp\
	  $(COMMON_DIR)/Error_Connection.cpp\
	  $(SRCS_DIR)/Error_Communication.cpp\
	  $(SRCS_DIR)/Error_Resource.cpp	\
	  $(SRCS_DIR)/Player.cpp	\
	  $(SRCS_DIR)/Thread.cpp	\
	  $(SRCS_DIR)/Mutex.cpp		\
	  $(COMMON_DIR)/Converter.cpp	\
	  $(SRCS_DIR)/Case.cpp		\
	  $(SRCS_DIR)/ConditionVar.cpp	\
	  $(SRCS_DIR)/Egg.cpp

OBJS	= $(SRCS:.cpp=.o)

CXX	= g++ 
CXXFLAGS = -W -Wall -I $(INCLUDES_DIR) -O2 -I../client_dir/
LDFLAGS += -lpthread -lsfml-graphics1.6 -lsfml-window1.6 -lsfml-system1.6 -lm

RM	= rm -f

$(NAME) : $(OBJS)
	$(CXX) -o $(NAME) $(OBJS) $(LDFLAGS)

all	: $(NAME)

clean	:
	$(RM) $(OBJS) *~

fclean	: clean
	$(RM) $(NAME)

re	: fclean all

%.o	: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
