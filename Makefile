FILES_C = src/main.c src/error.c src/link.c src/room.c src/utils.c src/utils2.c src/read.c src/solve.c src/pathing.c src/print.c src/fixpath.c src/utils3.c src/commentaries.c src/alternate.c
FILES_O = main.o error.o link.o room.o utils.o read.o solve.o pathing.o utils2.o print.o fixpath.o utils3.o commentaries.o alternate.o
NAME = lem-in
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@make -C libft/ all
	@cp libft/libft.a ./
	@cp libft.a Bonus/
	@echo "\033[0;5;33mCompiling and building\033[0m"
	@gcc -c $(FLAGS) $(FILES_C) -I ./includes
	@gcc -o $(NAME) $(FLAGS) $(FILES_O) -I ./includes -L . -lft
	@echo "\033[0;32mFinished building \033[40;97m$(NAME)\033[0m"
	@make -C Bonus/ all
	@cp lem-in visualizer maps/

clean:
	@/bin/rm -f $(FILES_O)
	@make -C libft/ clean
	@make -C Bonus/ clean

fclean:
	@/bin/rm -f $(FILES_O)
	@/bin/rm -f $(NAME) visualizer
	@/bin/rm -f maps/$(NAME) maps/visualizer
	@/bin/rm -f libft.a
	@make -C libft/ fclean
	@make -C Bonus/ fclean

re:	fclean all

retest:
	@make -C Bonus/ retest
	@echo "\033[0;34mRemaking for test\033[0m"
	@rm lem-in
	@gcc -c $(FLAGS) $(FILES_C) -I ./includes
	@gcc -o $(NAME) $(FLAGS) $(FILES_O) -I ./includes -L . -lft
	@cp lem-in maps/

bonus:
	@make -C Bonus/ re
	@cp lem-in visualizer map/
