# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chduong <chduong@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/05 18:48:08 by kennyduong        #+#    #+#              #
#    Updated: 2022/05/30 15:39:56 by chduong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#########################################
#				PROGRAMS				#
#########################################
C3D			=	cub3D

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

INC			= 	-I inc $(INC_MLX) $(INC_LFT)
INC_LFT		=	-I inc/libft/inc
INC_MLX		=	-I /usr/inc -I inc/mlx

LINK		=	-lm $(LINK_MLX) $(LINK_LFT)
LINK_LFT	=	-L ./inc/libft -lft
LINK_MLX	=	-L ./inc/mlx -lmlx -lXext -lX11

#########################################
#			DIRECTORIES					#
#########################################
OBJ_DIR		=	obj/
SRC_DIR		=	srcs/
LFT_DIR		=	inc/libft/
MLX_DIR		=	inc/mlx/

#########################################
#			SOURCES	FILES				#
#########################################
LFT			=	$(LFT_DIR)libft.a
MLX			= 	$(MLX_DIR)libmlx.a

C3D_SRC		=	main.c		key_control.c\
				${addprefix parsing/,\
					parsing.c			collectdata.c		create_map.c\
					check_each_elem.c	check_elems.c		check_map.c\
					valid_char.c		player_position.c}\
				${addprefix utils/,\
					intersections.c		getnextline.c		utils.c}\
				${addprefix raycasting/,\
					raycasting.c}\
				${addprefix display/,\
					player_view.c		minimap.c		pixel_utils.c}

#########################################
#            OBJECT FILES    	        #
#########################################
C3D_OBJ		=	$(C3D_SRC:.c=.o)
C3D_OBJ		:=	$(addprefix $(OBJ_DIR), $(C3D_OBJ))

#########################################
#			MAKE	RULES				#
#########################################
$(C3D): $(MLX) $(LFT) $(OBJ_DIR) $(C3D_OBJ)
	@echo "> $(CYAN)Generate objects$(END) : \t\t[$(GREEN)OK$(END)]"
	@$(CC) -o $@ $(C3D_OBJ) $(LIBFT) $(MLX) $(LINK)
	@echo "> $(WHITE)$(BOLD)Cube3D Compilation$(END) : \t\t[$(YELLOW)COMPLETE$(END)]"

$(LFT):
	@make -s -C $(LFT_DIR)
	@echo "> $(CYAN)Libft Compilation$(END) : \t\t[$(GREEN)OK$(END)]"
	
$(MLX):
	@make -s -C $(MLX_DIR) all
	@echo "> $(CYAN)Create MiniLibX$(END) : \t\t[$(GREEN)OK$(END)]"

${OBJ_DIR}%.o:	${SRC_DIR}%.c
	@${MKDIR} ${@D}
	@${CC} ${CFLAGS} ${INC} -c -o $@ $<

$(OBJ_DIR):
	@$(MKDIR) $(OBJ_DIR)
	
all: $(C3D)

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
	@$(RM) $(C3D)
	@echo "> $(PURPLE)Delete Program$(END) : \t\t[$(GREEN)OK$(END)]"
	
re: fclean all 

norm:
	@norminette ${SRC_DIR} ${INC_DIR} ${LFT_DIR} | grep 'Error' ; true

leak:
	valgrind ./${C3D}

.PHONY: all clean fclean re
