FILES_C = src/main.c src/error.c src/link.c src/room.c src/utils.c src/utils2.c src/read.c src/solve.c src/pathing.c src/print.c src/fixpath.c src/utils3.c src/commentaries.c src/alternate.c
FILES_O = main.o error.o link.o room.o utils.o read.o solve.o pathing.o utils2.o print.o fixpath.o utils3.o commentaries.o alternate.o
NAME = lem-in
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@make -C libft/ all
	@cp libft/libft.a ./
	@echo "\033[0;5;33mCompiling and building\033[0m"
	@gcc -c $(FLAGS) $(FILES_C) src/kane_alloc_wrap.c -I ./includes
	@gcc -o $(NAME) $(FLAGS) $(FILES_O) -I ./includes -L . -lft
	@gcc -o $(NAME)2 $(FLAGS) $(FILES_O) kane_alloc_wrap.o -I ./includes -L . -lft
	@echo "\033[0;32mFinished building \033[40;97m$(NAME)\033[0m"

clean:
	@/bin/rm -f $(FILES_O) kane_alloc_wrap.o
	@make -C libft/ clean

fclean:
	@/bin/rm -f $(FILES_O) kane_alloc_wrap.o
	@/bin/rm -f $(NAME)
	@/bin/rm -f $(NAME)2
	@/bin/rm -f libft.a
	@make -C libft/ fclean

re:	fclean all

retest:
	@echo "\033[0;34mRemaking for test\033[0m"
	@rm lem-in
	@gcc -c $(FLAGS) $(FILES_C) src/kane_alloc_wrap.c -I ./includes
	@gcc -o $(NAME) $(FLAGS) $(FILES_O) -I ./includes -L . -lft
	@cp lem-in maps/
