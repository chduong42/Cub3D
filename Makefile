# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chduong <chduong@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/05 18:48:08 by kennyduong        #+#    #+#              #
#    Updated: 2022/05/16 19:41:30 by chduong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#########################################
#				PROGRAMS				#
#########################################
C3D			=	cub3d

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

INC			= 	-I inc $(INC_MLX)
INC_MLX		=	-I/usr/inc -I mlx_linux

LINK		=	$(LINK_MLX)
LINK_MLX	=	-L -lmlx -lXext -lX11

#########################################
#			DIRECTORIES					#
#########################################
SRC_DIR		=	srcs/
MLX_DIR		=	mlx_linux/
OBJ_DIR		=	obj/

#########################################
#			SOURCES	FILES				#
#########################################
MLX			= 	$(MLX_DIR)libmlx.a

C3D_SRC		=	main.c

#########################################
#            OBJECT FILES    	        #
#########################################
C3D_OBJ		=	$(C3D_SRC:.c=.o)
C3D_OBJ		:=	$(addprefix $(OBJ_DIR), $(C3D_OBJ))

#########################################
#			MAKE	RULES				#
#########################################
$(C3D): $(MLX) $(OBJ_DIR) $(C3D_OBJ)
	@echo "> $(CYAN)Generate objects$(END) : \t\t[$(GREEN)OK$(END)]"
	@$(CC) -o $@ $(C3D_OBJ) $(LIBFT) $(MLX) $(LINK)
	@echo "> $(WHITE)$(BOLD)So_Long Compilation$(END) : \t[$(YELLOW)COMPLETE$(END)]"

$(MLX):
	@make -s -C $(MLX_DIR) all
	@echo "> $(CYAN)Create MiniLibX$(END) : \t\t[$(GREEN)OK$(END)]"

${OBJ_DIR}%.o:	${SRC_DIR}%.c
# @${MKDIR} ${@D}
	@${CC} ${CFLAGS} ${INC} -c -o $@ $<

$(OBJ_DIR):
	@$(MKDIR) $(OBJ_DIR)
	
all: $(C3D)

bonus :	
	
clean:
	@$(RM) $(OBJ_DIR)
	@echo "> $(PURPLE)Clean objects$(END) : \t\t[$(GREEN)OK$(END)]"
	
fclean: clean
	@make -s -C $(MLX_DIR) clean
	@echo "> $(PURPLE)Delete MiniLibX$(END) : \t\t[$(GREEN)OK$(END)]"
	@$(RM) $(C3D)
	@echo "> $(PURPLE)Delete Program$(END) : \t\t[$(GREEN)OK$(END)]"
	
re: fclean all 

norm:
	@norminette ${SRC_DIR} ${INC_DIR} | grep 'Error' ; true

leak:
	valgrind ./${C3D}

.PHONY: all clean fclean re