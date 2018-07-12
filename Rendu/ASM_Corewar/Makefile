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
		
C_FLAGS = -g

DIR_LIB = ../Libft/

DIR_SRC = Sources/

DIR_TOOLS = $(addprefix $(DIR_SRC), Tools/)

DIR_WRITE = $(addprefix $(DIR_SRC), Write/)

DIR_ERROR = $(addprefix $(DIR_SRC), Error/)

DIR_PARSER = $(addprefix $(DIR_SRC), Parser/)

DIR_BONUS = $(addprefix $(DIR_SRC), Bonus/)

DIR_INC = Includes/

NAME_SRC = main_asm.c

WRITE_SRC = write_file.c write_params.c

ERROR_SRC = error_asm.c error_file.c error_token.c

TOOLS_SRC = tools_byte.c tools_free.c tools_label.c tools_parser.c \
			tools_token.c tools_op.c tools_verbose.c tools_write.c

PARSER_SRC = parser_header.c parser_label.c parser_asm.c parser_elem.c \
			 parser_code.c

BONUS_SRC = verbose_file.c verbose_params.c

NAME_INC = asm_define.h asm_functions.h main_asm.h asm_enum.h asm_struct.h \
			op.h colors_define.h

INC = $(addprefix $(DIR_INC), $(NAME_INC))

SRC = $(addprefix $(DIR_SRC), $(NAME_SRC)) \
	  $(addprefix $(DIR_TOOLS), $(TOOLS_SRC)) \
	  $(addprefix $(DIR_WRITE), $(WRITE_SRC)) \
	  $(addprefix $(DIR_ERROR), $(ERROR_SRC)) \
	  $(addprefix $(DIR_PARSER), $(PARSER_SRC)) \
	  $(addprefix $(DIR_BONUS), $(BONUS_SRC))

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
