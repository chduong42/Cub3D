/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:10:40 by jvermeer          #+#    #+#             */
/*   Updated: 2022/05/31 18:35:10 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h> 
# include <sys/stat.h> 
# include "libft.h"
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>

//	MACRO
# define TITLE "My Cub3D"
# define TILE_SIZE 32
# define LENGTH 1280
# define HEIGHT 1024
# define FOV 60
# define PI 3.14159265358979323846

//	Key Code
# define A 97
# define D 100
# define S 115
# define W 119
# define ESC 65307
# define LEFT 65361
# define RIGHT 65363

//	TYPE DEF
typedef unsigned int	t_uint;

typedef struct s_keys
{
	int		keyw;
	int		keys;
	int		keya;
	int		keyd;
	int		keyl;
	int		keyr;
}			t_keys;

typedef struct s_ray
{
	float	ray_angle;
	float	wall_hitx;
	float	wall_hity;
	float	dist;
	int		hit_vert;
	int		ray_up;
	int		ray_down;
	int		ray_left;
	int		ray_right;
	int		wall_hits;
}			t_ray;

typedef struct s_cube
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		sizeline;
	int		endian;
	int		mnm_pix;
	int		map_l;
	int		map_h;

	char	**file;
	char	**map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor[3];
	int		ceiling[3];

	int		pov;
	float	dist;
	float	pos[2];//position personnage : pos[0] = x   pos[1] = y
	t_keys	k;
}			t_cube;

typedef struct s_gnl
{
	int		ret;
	int		bean;
	int		size;
	char	c;
}			t_gnl;

//	PARSING
int		check_each_elem(char *l, int *tab);
int		check_elems(t_cube *s);
int		check_map(t_cube *s);
int		create_map(t_cube *s, int i);
int		data_collect(t_cube *s);
int		valid_char(t_cube *s);
void	get_player_position(t_cube *s);
int		parsing(t_cube *s, int ac, char **av);

//	KEY CONTROL
int		keypress(int key, t_cube *s);
int		keyrelease(int key, t_cube *s);

//	UTILS
int		buffcomp(char *str, char *l);
void	free_all(t_cube *s);
void	free_array(char **str);
char	*get_filename(char *l);
int		get_next_line(int fd, char **line);
int		write_error(char *message);

// MATHS UTILS
float	rad(float degree);
float	dist_ab(float x1, float y1, float x2, float y2);
float	wall_intersections(t_cube *s, int deg);

//	DISPLAY
int		create_trgb(int t, int r, int g, int b);
void	draw_minimap(t_cube *s);
void	draw_player_view(t_cube *s);
void	my_mlx_pixel_put(t_cube *s, int x, int y, int color);
t_uint	get_pixel_color(t_cube *s, int x, int y);

#endif
