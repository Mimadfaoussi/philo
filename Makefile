NAME	:= philosophers

CC		:=	cc
CFLAGS	:=	-Wextra -Wall -Werror

SRCS	:=	$(wildcard *.c) $(wildcard */*.c)

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