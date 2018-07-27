# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2017/12/08 18:11:02 by clcreuso     #+#   ##    ##    #+#        #
#    Updated: 2018/07/27 18:28:49 by jjanin-r    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re

CC = gcc

NAME = ../corewar

C_FLAGS =  -Wall -Wextra -Werror

DIR_LIB = ../Libft/

DIR_SRC = Sources/

DIR_INC = Includes/

DIR_INSTRUCTIONS = $(addprefix $(DIR_SRC), Instructions/)

DIR_TOOLS = $(addprefix $(DIR_SRC), Tools/)

NAME_SRC = main_vm.c parser.c init.c init_champs.c read_champs.c \
 cycle.c dump.c read.c exec.c process.c move.c

INSTRUCTIONS_SRC = add.c aff.c and.c check_register.c fork.c ld.c ldi.c \
 lfork.c live.c lld.c lldi.c or.c st.c sti.c sub.c xor.c zjmp.c

TOOLS_SRC = tools_error.c tools_free.c tools_instructions.c tools_op.c \
 tools_vm.c tools_lst.c tools_ocp.c

NAME_INC = main_vm.h

INC = $(addprefix $(DIR_INC), $(NAME_INC))

SRC = $(addprefix $(DIR_SRC), $(NAME_SRC)) \
	  $(addprefix $(DIR_INSTRUCTIONS), $(INSTRUCTIONS_SRC)) \
	  $(addprefix $(DIR_TOOLS), $(TOOLS_SRC))

OBJ = $(SRC:.c=.o)

CURSOR = 0

NB_FILES = $(words $(SRC))

all: $(NAME)

$(NAME): $(OBJ) $(INC)
	@$(CC) $(C_FLAGS) $(OBJ) -L $(DIR_LIB) -lft -o $(NAME)
	@printf "\r\033[0;32m✅️   make VM_Corewar 100%%\033[0m\033[K\n"

./%.o: ./%.c $(INC)
	@$(eval CURSOR=$(shell echo $$(($(CURSOR)+1))))
	@$(eval PERCENT=$(shell echo $$(($(CURSOR)*100/$(NB_FILES)))))
	@printf "\033[0;32m⌛️   make VM_Corewar $(PERCENT)%%\033[0m\033[K\r"
	@$(CC) $(C_FLAGS) -I $(DIR_INC) -o $@ -c $< 

clean:
	@if [ -e Sources/main_vm.o ]; then \
		printf "\r\033[38;5;202m🗑️   clean VM_Corewar\033[0m\033[K\n";\
	fi;
	@make -C ../Libft clean
	@rm -rf $(OBJ)

fclean: clean
	@if [ -e $(NAME) ]; then \
		printf "\r\033[38;5;196m🗑️   fclean VM_Corewar\033[0m\033[K\n"; \
	fi;
	@make -C ../Libft fclean
	@rm -rf $(NAME)

re: fclean all
