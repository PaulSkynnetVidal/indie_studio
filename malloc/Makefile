
# CC		= gcc

# LN		= ln -s

# RM		= rm -f

# NAME		= libmy_malloc_$(HOSTTYPE).so

# LNAME		= libmy_malloc.so

# SRCS		= malloc.c    \
# 		manage_struct.c

# OBJS		= $(SRCS:.c=.o)

# LDFLAGS		= -W -Wall -Werror

# $(NAME):
# 		$(CC) -c $(SRCS) -fPIC $(LDFLAGS)
# 		$(CC) -shared -o $(NAME) $(OBJS)
# 		$(LN) $(NAME) $(LNAME)

# all:		$(NAME)

# clean:
# 		$(RM) $(OBJS)

# fclean:		clean
# 		$(RM) $(NAME) $(LNAME)

# re:		fclean all

# .PHONY:		all clean fclean re

NAME = libasm.so

SRCS = strlen.S \

OBJS = $(SRCS:.S=.o)

CC = gcc

CFLAGS = -shared -fPIC -W -Wall -Werror -Wextra

AS = nasm -f elf64

RM = rm -f

$(NAME) : $(AS) $(SRCS) $(OBJS)
	  $(CC) $(CFLAGS) -o $(NAME) $(OBJS)

all	: $(NAME)

clean	:
	  $(RM) $(OBJS)

fclean	: clean
	  $(RM) $(NAME)

re	: fclean all
