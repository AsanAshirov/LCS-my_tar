NAME = my_tar

SRCS =	*.c

SANITIZE = -g -fsanitize=address
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME) :
	gcc $(SANITIZE) $(SRCS) -o $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all
