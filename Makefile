NAME	:= philo

CC		:=	cc
CFLAGS	:=	-Wextra -Wall -Werror -pthread -g

SRCS	:=	./errors/check_input.c \
				./helper_functions/ft_atoi.c ./helper_functions/get_time.c \
				./init_destroy/destroy.c ./init_destroy/init.c \
				./threads/actions.c ./threads/checker_routine.c \
				./threads/philo_routine.c ./threads/thread_start.c \
				philosophers.c

OBJS	:=	${SRCS:.c=.o}

all: $(NAME)


$(NAME): $(OBJS)
	@echo "Compiling philosophers ..."
	@$(CC) $(OBJS) -o $(NAME)

clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJS)

fclean: clean
	@echo "Cleaning philosophers"
	@rm -f $(NAME)

re: clean all

.PHONY: all, clean, fclean, re