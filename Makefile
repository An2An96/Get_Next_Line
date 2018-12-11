NAME = a.out

FLAGS = -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME):
	gcc $(FLAGS) -Llibft -lft -Ilibft/includes main.c get_next_line.c -o $(NAME)

fclean:
	rm -f $(NAME)

re: fclean all

