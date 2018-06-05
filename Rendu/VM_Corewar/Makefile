# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2017/12/08 18:11:02 by clcreuso     #+#   ##    ##    #+#        #
#    Updated: 2018/06/05 18:44:07 by dguelpa     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re

CC = gcc

NAME = ./corewar

C_FLAGS = -Wall -Wextra -Werror

DIR_LIB = ../Libft/

DIR_SRC = Sources/

DIR_INC = Includes/

NAME_SRC = main_vm.c parse_args_vm.c utils_vm.c init.c

NAME_INC = main_vm.h

INC = $(addprefix $(DIR_INC), $(NAME_INC))

SRC = $(addprefix $(DIR_SRC), $(NAME_SRC))

OBJ = $(SRC:.c=.o)

CURSOR = 0

NB_FILES = $(words $(SRC))

all: $(NAME)

$(NAME): $(OBJ) $(INC)
	@make -C ../Libft
	@$(CC) $(C_FLAGS) $(OBJ) -L $(DIR_LIB) -lft -o $(NAME)
	@printf "\r\033[0;32m✅️   make corewar 100%%\033[0m\033[K\n"

./%.o: ./%.c $(INC)
	@$(eval CURSOR=$(shell echo $$(($(CURSOR)+1))))
	@$(eval PERCENT=$(shell echo $$(($(CURSOR)*100/$(NB_FILES)))))
	@printf "\033[0;32m⌛️   make $(NAME) $(PERCENT)%%\033[0m\033[K\r"
	@$(CC) $(C_FLAGS) -I $(DIR_INC) -o $@ -c $< 

clean:
	@if [ -e Sources/main_vm.o ]; then \
		printf "\r\033[38;5;202m🗑️   clean corewar\033[0m\033[K\n";\
	fi;
	@make -C ../Libft clean
	@rm -rf $(OBJ)

fclean: clean
	@if [ -e $(NAME) ]; then \
		printf "\r\033[38;5;196m🗑️   fclean corewar\033[0m\033[K\n"; \
	fi;
	@make -C ../Libft fclean
	@rm -rf $(NAME)

re: fclean all
