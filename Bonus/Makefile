FILES_C = src/main.c src/link.c src/room.c src/move.c src/utils.c src/read.c src/mlx.c src/draw.c
FILES_O = mlx.o link.o main.o move.o read.o room.o utils.o draw.o
NAME = visualizer
FLAGS = -Wall -Wextra -Werror
FRAMEWORKS = -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): up
	@echo "\033[0;5;33mMaking minilibx\033[0m"
	@make -C minilibx/ all
	@echo "\033[0;32mFinished making \033[97;40mminilibx\033[0m"
	@cp minilibx/libmlx.a ./
	@echo "\033[0;5;33mCompiling and building\033[0m"
	@gcc -c $(FLAGS) $(FILES_C) -I ./includes -I ./minilibx
	@gcc -o $(NAME) $(FLAGS) $(FILES_O) -I ./includes -I ./minilibx $(FRAMEWORKS) -L . -lft -lmlx
	@cp $(NAME) ../
	@echo "\033[0;32mFinished building \033[40;97m$(NAME)\033[0m"

clean:
	@/bin/rm -f $(FILES_O) $(FILES_O)
	@make -C minilibx/ clean

fclean:
	@/bin/rm -f $(FILES_O) $(FILES_O)
	@/bin/rm -f $(NAME)
	@/bin/rm -f libft.a
	@/bin/rm -f libmlx.a
	@make -C minilibx/ clean

re: fclean up all

up:
	@make -C ../libft all
	@cp ../libft/libft.a ../
	@cp ../libft.a ./

test:
	@echo "\033[0;34mRemaking for test\033[0m"
	@rm $(NAME)
	@gcc -c $(FLAGS) $(FILES_C) -I ./includes -I ./minilibx
	@gcc -o $(NAME) $(FLAGS) $(FILES_O) -I ./includes -I ./minilibx $(FRAMEWORKS) -L . -lft -lmlx
	@cp $(NAME) ../

retest: test
