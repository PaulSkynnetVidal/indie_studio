##
## Makefile for bombertrash in /home/david/dev/cpp_indie_studio/
##
## Made by David Calo
## Login   <calo_d@epitech.eu>
##
## Started on  Wed May  4 19:20:00 2016 David Calo
## Last update Fri Jun 10 03:49:34 2016 debrab_t
##

NAME	= bombertrash

SRCS	= main.cpp		\
	  fileManager.cpp	\
	  map.cpp		\
	  Player.cpp		\
	  Core.cpp		\
	  MenuCore.cpp		\
	  Bombe.cpp		\
	  tools.cpp		\
	  Son.cpp		\

CXX		= g++

RM		= rm -f

BIN_NAME	= $(addprefix bin/, $(NAME))

LIB_DIR		= irrlicht

CPPFLAGS	= -std=c++11 -I$(LIB_DIR)/include -Iinclude -std=c++11 -g3

CXXFLAGS	= -W -Wall -Werror -Wextra -g3 -fPIC
#-I./src/ -I./src/SFML -I./src/SFML/System
#CXXFLAGS	+= -03 -ffast-math

LDFLAGS		+= -L$(LIB_DIR)/ -lIrrlicht
LDFLAGS		+= -lGL -lXxf86vm -lXext -lX11 -lXcursor

SRCS_DIR	= src

OBJS_DIR	= bin

SRCS_BIN	= $(addprefix $(SRCS_DIR)/, $(SRCS))

OBJS_BIN	= $(addsuffix .o, $(basename $(subst $(SRCS_DIR), $(OBJS_DIR), $(SRCS_BIN))))

DEPS_BIN	= $(addsuffix .d, $(basename $(subst $(SRCS_DIR), $(OBJS_DIR), $(SRCS_BIN))))

# addprefix <prefix>, <source> : add <prefix> before <source>	| main.c -> src/main.c
# subst <a>, <b>, <source> : replace <a> by <b> in <source>		| src/main.c -> bin/main.c
# basename <source> : remove extension from <source>			| bin/main.c -> bin/main
# addsuffix <suffix>, <source> : add <suffix> behind <source>	| bin/main -> bin/main.o

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
	$(warning Building ...)
	$(shell mkdir -p $(OBJS_DIR))
	$(CXX) $(CPPFLAGS) -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"

$(NAME): $(OBJS_BIN)
	$(CXX) $(OBJS_BIN) $(LDFLAGS) -o $(NAME) -L./irrlicht/include/lib ./irrlicht/include/libsfml-audio.so ./irrlicht/include/libsfml-system.so
	export LD_LIBRARY_PATH="./irrlicht/include/"

all: $(NAME)

clean:
	$(warning Cleaning ...)
	$(RM) $(OBJS_BIN) $(DEPS_BIN)

fclean: clean
	$(RM) $(BIN_NAME) $(NAME)

re: fclean all

.PHONY: all clean fclean re
