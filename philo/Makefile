NAME = philo
CC = cc
ifneq ($(CI),)
    CFLAGS = -Wall -Wextra -Werror -g
else
    CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
endif

SRCDIR = .
OBJDIR = .objs
SRCS = main.c init.c utils.c utils2.c routine.c routine_utils.c sen_one.c checking.c
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all
