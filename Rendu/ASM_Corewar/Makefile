# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2017/12/08 18:11:02 by clcreuso     #+#   ##    ##    #+#        #
#    Updated: 2018/06/18 11:19:37 by nbettach    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re

CC = gcc

NAME = ../asm
		
C_FLAGS =  -Wall -Wextra -Werror

DIR_LIB = ../Libft/

DIR_SRC = Sources/

DIR_TOOLS = $(addprefix $(DIR_SRC), Tools/)

DIR_PARSER = $(addprefix $(DIR_SRC), Parser/)

DIR_INC = Includes/

NAME_SRC = main_asm.c print_error.c op.c

TOOLS_SRC = asm_tools.c token_tools.c print_tools.c free_tools.c

PARSER_SRC = parser_header.c parser_label.c parser_asm.c parser_elem.c \
			parser_tools.c label_error.c convert_binary.c

NAME_INC = main_asm.h op.h

INC = $(addprefix $(DIR_INC), $(NAME_INC))

SRC = $(addprefix $(DIR_SRC), $(NAME_SRC)) \
	  $(addprefix $(DIR_TOOLS), $(TOOLS_SRC)) \
	  $(addprefix $(DIR_PARSER), $(PARSER_SRC))

OBJ = $(SRC:.c=.o)

CURSOR = 0

NB_FILES = $(words $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(C_FLAGS) $(OBJ) -L $(DIR_LIB) -lft -o $(NAME)
	@printf "\r\033[0;32m✅️   make asm 100%%\033[0m\033[K\n"

./%.o: ./%.c $(INC)
	@$(eval CURSOR=$(shell echo $$(($(CURSOR)+1))))
	@$(eval PERCENT=$(shell echo $$(($(CURSOR)*100/$(NB_FILES)))))
	@printf "\033[0;32m⌛️   make asm $(PERCENT)%%\033[0m\033[K\r"
	@$(CC) $(C_FLAGS) -I $(DIR_INC) -o $@ -c $< 

clean:
	@if [ -e Sources/main_asm.o ]; then \
		printf "\r\033[38;5;202m🗑️   clean asm\033[0m\033[K\n";\
	fi;
	@rm -rf $(OBJ)

fclean: clean
	@if [ -e $(NAME) ]; then \
		printf "\r\033[38;5;196m🗑️   fclean asm\033[0m\033[K\n"; \
	fi;
	@rm -rf $(NAME)

re: fclean all
