NAME = ft_ping

SRCS =

OBJDIR = obj
OBJS = $(addprefix $(OBJDIR)/,$(SRCS:.s=.o))

GCC = gcc
GCCFLAGS = -Wall -Werror -Wextra -g

all: $(NAME)

$(NAME): $(OBJS) $(GCCFLAGS) $(NAME) $(OBJS)

$(OBJDIR)/%.o: src/%.s | $(OBJDIR) $(GCC) $(GCCFLAGS) $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
