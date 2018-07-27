# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2017/12/08 18:11:02 by clcreuso     #+#   ##    ##    #+#        #
#    Updated: 2018/07/27 19:23:18 by jjanin-r    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all libft clean fclean re

CC = gcc

NAME = ../corewar

C_FLAGS =  -Wall -Wextra -Werror -g

DIR_LIB = ../Libft/

DIR_SRC = Sources/

DIR_INC = Includes/

DIR_EXEC = $(addprefix $(DIR_SRC), Exec/)

DIR_TOOLS = $(addprefix $(DIR_SRC), Tools/)

DIR_COMMANDS = $(addprefix $(DIR_SRC), Commands/)

MAIN_SRC = main_vm.c

EXEC_SRC = parser.c init.c init_champs.c read_champs.c \
 cycle.c dump.c read.c exec.c process.c move.c

COMMANDS_SRC = add.c aff.c and.c fork.c ld.c ldi.c \
 lfork.c live.c lld.c lldi.c or.c st.c sti.c sub.c xor.c zjmp.c

TOOLS_SRC = tools_error.c tools_free.c tools_instructions.c tools_op.c \
 tools_vm.c tools_lst.c tools_ocp.c

NAME_INC = main_vm.h vm_defines.h vm_functions.h vm_structs.h

INC = $(addprefix $(DIR_INC), $(NAME_INC))

SRC = $(addprefix $(DIR_SRC), $(MAIN_SRC)) \
	  $(addprefix $(DIR_COMMANDS), $(COMMANDS_SRC)) \
	  $(addprefix $(DIR_TOOLS), $(TOOLS_SRC)) \
	  $(addprefix $(DIR_EXEC), $(EXEC_SRC))

OBJ = $(SRC:.c=.o)

CURSOR = 0

NB_FILES = $(words $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
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
	@rm -rf $(OBJ)

fclean: clean
	@if [ -e $(NAME) ]; then \
		printf "\r\033[38;5;196m🗑️   fclean VM_Corewar\033[0m\033[K\n"; \
	fi;
	@rm -rf $(NAME)

re: fclean all
