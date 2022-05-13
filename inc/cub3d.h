/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 13:55:28 by chduong           #+#    #+#             */
/*   Updated: 2022/05/13 16:39:40 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <stdbool.h>

//	MACRO
# define TITLE "My Cub3D"
# define PIX 80
# define UP -1
# define DOWN 1
# define LEFT -1
# define RIGHT 1

//	Key Code
# define A 97
# define D 100
# define S 115
# define W 119
# define ARROW_UP 65362
# define ARROW_DOWN 65364
# define ARROW_LEFT 65361
# define ARROW_RIGHT 65363

typedef struct s_dim
{
	int		x;
	int		y;
}			t_dim;

typedef struct s_map
{
	char	**tab;
	int		exit;
	int		player;
	int		collect;
	t_dim	dim;
	t_dim	ploc;
	t_dim	cloc;
}			t_map;

typedef struct s_data
{
	int		width;
	int		height;
	void	*mlx;
	void	*win;
	char	*move_display;
	t_map	map;
}			t_data;

#endif