NAME = libasm.so

SRCS = strlen.S\
	strchr.S\
	memset.S\
	memcpy.S\
	strcmp.S\
	rindex.S\
	strpbrk.S\
	strncmp.S\
	strcspn.S\
	memmove.S

OBJS = $(SRCS:.S=.o)

CC = gcc

CFLAGS = -shared -fPIC -W -Wall -Werror -Wextra

AS = nasm -f elf64

RM = rm -f

$(NAME) :	  $(OBJS)
	          $(CC) $(CFLAGS) -o $(NAME) $(OBJS)

all     : 	  $(NAME)

clean   :
	          $(RM) $(OBJS)

fclean  : clean
	          $(RM) $(NAME)

re      : fclean all

%.o: %.S
	$(AS) $< -o $@
