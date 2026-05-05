NAME = ft_ping

SRCS = main.c 					\
			 parsing.c				\
			 get_ipv4.c				\
			 set_socket.c			\
			 manage_packet.c	\
			 icmp_loop.c

OBJDIR = obj
OBJS = $(addprefix $(OBJDIR)/,$(SRCS:.c=.o))

COMPILER = gcc
FLAGS = -Wall -Werror -Wextra -g

all: $(NAME)

$(NAME):  $(OBJS)
	$(COMPILER) $(FLAGS) -o $(NAME) $(OBJS)

$(OBJDIR)/%.o: src/%.c | $(OBJDIR) 
	$(COMPILER) $(FLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
