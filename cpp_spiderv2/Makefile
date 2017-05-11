##
## Makefile for makefile in /home/page_e/rendu/cpp_spider
##
## Made by Elie Page
## Login   <page_e@epitech.net>
##
## Started on  Mon Nov  7 15:26:19 2016 Elie Page
## Last update Wed Nov  9 14:56:33 2016 Elie Page
##

GCC	= clang++

RM	= rm -rf

NAME	= server

NAMEB	= server_ssl

SRCS	= main.cpp \
		Server.cpp

SRCSB	= main_ssl.cpp \
		OSServer.cpp

OBJS	= $(SRCS:.cpp=.o)

OBJSB	= $(SRCSB:.cpp=.o)

LDFLAGS	+= -lboost_thread -lboost_system -lpthread

LDFLAGSB += -lssl -lcrypto

CXXFLAGS += -std=c++11

$(NAME):
	$(GCC) -o $(NAME) $(SRCS) $(LDFLAGS) $(CXXFLAGS)

all:	$(NAME)

ssl:
	$(GCC) -o $(NAMEB) $(SRCSB) $(LDFLAGSB) $(CXXFLAGS)

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJSB)

fclean:	clean
	$(RM) $(NAME)
	$(RM) $(NAMEB)

re:	fclean all
