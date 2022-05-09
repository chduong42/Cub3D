# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chduong <chduong@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/05 18:48:08 by kennyduong        #+#    #+#              #
#    Updated: 2021/12/24 13:46:29 by chduong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#########################################
#				PROGRAMS				#
#########################################
SL			=	so_long

#########################################
#				COMMANDS				#
#########################################
CC			=	clang
MKDIR		=	mkdir -p
AR			=	ar rcs
RM			= 	rm -rf

#########################################
#				COLORS					#
#########################################
GREY       =   $'\033[0;30m
RED        =   $'\033[0;31m
GREEN      =   $'\033[0;92m
YELLOW     =   $'\033[0;33m
BLUE       =   $'\033[0;34m
U_BLUE     =   $'\033[4;34m
PURPLE     =   $'\033[0;35m
CYAN       =   $'\033[0;96m
WHITE      =   $'\033[0;37m
END        =   $'\033[0;m
BOLD       =   $'\e[1m

#########################################
#			FLAGS COMPILATION			#
#########################################
CFLAGS		=	-Wall -Wextra -Werror
DEBUG		=	-fsanitize=address -g3

INC			= 	-I includes $(INC_MLX) $(INC_LFT)
INC_LFT		=	-I libft/inc
INC_MLX		=	-I/usr/include -I mlx_linux

LINK		=	$(LINK_LFT) $(LINK_MLX)
LINK_LFT	=	-L ./libft -lft
LINK_MLX	=	-L -lmlx -lXext -lX11

#########################################
#			DIRECTORIES					#
#########################################
SRC_DIR		=	srcs/
MLX_DIR		=	mlx_linux/
LFT_DIR		=	libft/
OBJ_DIR		=	obj/

#########################################
#			SOURCES	FILES				#
#########################################
LIBFT		=	$(LFT_DIR)libft.a
MLX			= 	$(MLX_DIR)libmlx.a

SL_SRC		=	main.c				get_map.c		checker_map.c\
				error_utils.c		handlers.c		parse_display.c\
				data_init.c			clear_data.c	load_img.c\
				player_move.c		display.c

#########################################
#            OBJECT FILES    	        #
#########################################
SL_OBJ		=	$(SL_SRC:.c=.o)
SL_OBJ		:=	$(addprefix $(OBJ_DIR), $(SL_OBJ))

#########################################
#			MAKE	RULES				#
#########################################
$(SL): $(MLX) $(LIBFT) $(OBJ_DIR) $(SL_OBJ)
	@echo "> $(CYAN)Generate objects$(END) : \t\t[$(GREEN)OK$(END)]"
	@$(CC) -o $@ $(SL_OBJ) $(LIBFT) $(MLX) $(LINK)
	@echo "> $(WHITE)$(BOLD)So_Long Compilation$(END) : \t[$(YELLOW)COMPLETE$(END)]"

$(LIBFT):
	@make -s -C $(LFT_DIR)
	@echo "> $(CYAN)Create LIBFT$(END) : \t\t[$(GREEN)OK$(END)]"

$(MLX):
	@make -s -C $(MLX_DIR) all
	@echo "> $(CYAN)Create MiniLibX$(END) : \t\t[$(GREEN)OK$(END)]"

${OBJ_DIR}%.o:	${SRC_DIR}%.c
# @${MKDIR} ${@D}
	@${CC} ${CFLAGS} ${INC} -c -o $@ $<

$(OBJ_DIR):
	@$(MKDIR) $(OBJ_DIR)
	
all: $(SL)

bonus :	
	
clean:
	@$(RM) $(OBJ_DIR)
	@make -s -C $(LFT_DIR) clean
	@echo "> $(PURPLE)Clean objects$(END) : \t\t[$(GREEN)OK$(END)]"
	
fclean: clean
	@make -s -C $(MLX_DIR) clean
	@echo "> $(PURPLE)Delete MiniLibX$(END) : \t\t[$(GREEN)OK$(END)]"
	@make -s -C $(LFT_DIR) fclean
	@echo "> $(PURPLE)Delete LIBFT$(END) : \t\t[$(GREEN)OK$(END)]"
	@$(RM) $(SL)
	@echo "> $(PURPLE)Delete Program$(END) : \t\t[$(GREEN)OK$(END)]"
	
re: fclean all 

norm:
	@norminette ${SRC_DIR} ${INC_DIR} | grep 'Error' ; true

leak:
	valgrind ./${SL}

.PHONY: all clean fclean re