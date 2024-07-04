NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRCS = main.c init.c utils.c utils2.c routine.c routine_utils.c sen_one.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
			@$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean :
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all