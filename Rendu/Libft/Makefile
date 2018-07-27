# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/05/25 17:12:33 by clcreuso     #+#   ##    ##    #+#        #
#    Updated: 2018/06/27 17:01:44 by jjanin-r    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all clean fclean re

CC = gcc

C_FLAGS = -Wall -Wextra -Werror

NAME = libft.a

DIR_CHR = Char/

DIR_MATH = Math/

DIR_PUT = Print/

DIR_STR = String/

DIR_MEM = Memory/

DIR_INC = Includes/

DIR_PRTF = Ft_printf/

DIR_LST = Linked_list/

DIR_GNL = Get_next_line/

NAME_INC = libftprintf.h libft.h

GNL =	get_next_line.c

LST =	ft_lstadd.c    ft_lstdelone.c ft_lstmap.c \
		ft_lstdel.c    ft_lstiter.c   ft_lstnew.c

MEM =	ft_bzero.c    ft_memccpy.c  ft_memcmp.c   ft_memdel.c   ft_memset.c \
		ft_memalloc.c ft_memchr.c   ft_memcpy.c   ft_memmove.c  ft_tabdel.c

CHR = 	ft_isalnum.c ft_isascii.c    ft_isprint.c    ft_tolower.c \
		ft_islower.c ft_iscntrl.c    ft_isspace.c    ft_toupper.c \
		ft_isalpha.c ft_isdigit.c    ft_isupper.c    ft_size_wchar.c

PUT =	ft_put_intmax.c       ft_putendl.c          ft_putwchar_fd.c \
		ft_put_intmax_base.c  ft_putendl_fd.c       ft_putwstr.c \
		ft_put_uint.c         ft_putnbr.c           ft_utf8_1.c \
		ft_put_uint_base.c    ft_putnbr_base.c      ft_utf8_2.c \
		ft_put_uintmax.c      ft_putnbr_fd.c        ft_utf8_3.c \
		ft_put_uintmax_base.c ft_putstr.c           ft_utf8_4.c \
		ft_putchar.c          ft_putstr_fd.c \
		ft_putchar_fd.c       ft_putwchar.c	

STR =	ft_count_chars.c  ft_strisdigit.c   ft_strncat.c      ft_strstr.c \
		ft_strcat.c       ft_strispattern.c ft_strncmp.c      ft_strsub.c \
		ft_strchr.c       ft_striter.c      ft_strncpy.c      ft_strtrim.c \
		ft_strclr.c       ft_striteri.c     ft_strnequ.c      ft_wstrlen.c \
		ft_strcmp.c       ft_strjoin.c      ft_strnew.c       ft_wstrncpy.c \
		ft_strcpy.c       ft_strlcat.c      ft_strnstr.c      ft_wstrsub.c \
		ft_strdel.c       ft_strlen.c       ft_strrchr.c \
		ft_strdup.c       ft_strmap.c       ft_strrev.c \
		ft_strequ.c       ft_strmapi.c      ft_strsplit.c

MATH =	ft_atoi.c           ft_imaxlen_base.c   ft_ulen.c \
		ft_atoimax.c        ft_imaxtoa.c        ft_ulen_base.c \
		ft_atou.c           ft_imaxtoa_base.c   ft_umaxlen.c \
		ft_atoumax.c        ft_intlen.c         ft_umaxlen_base.c \
		ft_ceil.c           ft_itoa.c           ft_umaxtoa.c \
		ft_hexatoi.c        ft_itoa_base.c      ft_umaxtoa_base.c \
		ft_ilen.c           ft_next_sqrt.c      ft_utoa.c \
		ft_ilen_base.c      ft_sort_tab_ascii.c ft_utoa_base.c \
		ft_imaxlen.c        ft_sqrt.c

PRTF =	color.c             ft_longitoa.c       ft_typed.c \
		ft_bigu.c           ft_longitoa_base.c  ft_typef.c \
		ft_charstr.c        ft_lsdel.c          ft_typeo.c \
		ft_checkerror.c     ft_lsdelone.c       ft_typep.c \
		ft_compute.c        ft_lstpush.c        ft_types.c \
		ft_doflags.c        ft_mod.c            ft_typeu.c \
		ft_dtoa.c           ft_node.c           ft_typex.c \
		ft_eraseflag.c      ft_prec.c           ft_u.c \
		ft_findflag.c       ft_precstr.c        ft_ulongitoa.c \
		ft_flag0.c          ft_print.c          ft_ulongitoa_base.c \
		ft_flagdiese.c      ft_printf.c         ft_uncap.c \
		ft_getconv.c        ft_printwidth.c     ft_wclen.c \
		ft_getflags.c       ft_putflag.c        ft_whichconv.c \
		ft_getmod.c         ft_putwchar.c       ft_width.c \
		ft_getparams.c      ft_putwstr.c        ft_wprec.c \
		ft_getwidthprec.c   ft_replaceflag.c    ft_wstrlen.c \
		ft_input.c          ft_strjoinfree.c    ft_wstrndup.c \
		ft_inputnode.c      ft_type.c           unicode.c \
		ft_isflag.c         ft_typec.c

SRC = 	$(addprefix $(DIR_CHR), $(CHR)) $(addprefix $(DIR_GNL), $(GNL)) \
		$(addprefix $(DIR_LST), $(LST)) $(addprefix $(DIR_STR), $(STR)) \
		$(addprefix $(DIR_MEM), $(MEM)) $(addprefix $(DIR_PUT), $(PUT)) \
		$(addprefix $(DIR_MATH), $(MATH)) $(addprefix $(DIR_PRTF), $(PRTF))

INC =	$(addprefix $(DIR_INC), $(NAME_INC))

OBJ =	$(SRC:.c=.o)

CURSOR = 0

NB_FILES = $(words $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@printf "\r\033[0;32m✅️   make $(NAME) 100%%\033[0m\033[K\n"

./%.o: ./%.c $(INC)
	@$(eval CURSOR=$(shell echo $$(($(CURSOR)+1))))
	@$(eval PERCENT=$(shell echo $$(($(CURSOR)*100/$(NB_FILES)))))
	@printf "\033[0;32m⌛️   make libft $(PERCENT)%%\033[0m\033[K\r"
	@$(CC) $(C_FLAGS) -I $(DIR_INC) -o $@ -c $< 

clean:
	@if [ -e Char/ft_isspace.o ]; then \
		printf "\r\033[38;5;202m🗑️   clean libft\033[0m\033[K\n"; \
		fi;
	@rm -rf $(OBJ)

fclean: clean
	@if [ -e $(NAME) ]; then \
		printf "\r\033[38;5;196m🗑️   fclean libft\033[0m\033[K\n"; \
		fi;
	@rm -rf $(NAME);

re: fclean all
