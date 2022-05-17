/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 13:55:28 by chduong           #+#    #+#             */
/*   Updated: 2022/05/17 16:14:55 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <stdbool.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif 

//	MACRO
# define TITLE "My Cub3D"
# define PIX 32
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

typedef struct s_xy
{
	int		x;
	int		y;
}			t_xy;

typedef struct s_map
{
	char	**tab;
	t_xy	dim;
	t_xy	p_loc;
}			t_map;

typedef struct s_data
{
	int		width;
	int		height;
	int		floor[3];
	int		ceiling[3];
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	void	*mlx;
	void	*win;
	t_map	map;
}			t_data;

//	UTILS
double	deg_to_rad(double degrees);
double	rad_to_deg(double radians);
void	print_error(t_data *data, const char *msg);
void	check_ptr(void *ptr, t_data *data);

//	HANDLERS
int		cross_btn(t_data *data);
int		handle_display(t_data *data);
int		handle_keypress(int keysym, t_data *data);

#endif