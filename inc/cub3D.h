/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:10:40 by jvermeer          #+#    #+#             */
/*   Updated: 2022/06/07 12:43:16 by jvermeer         ###   ########.fr       */
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
# include <stdbool.h>
# include <sys/types.h> 
# include <sys/stat.h> 
# include "libft.h"
# include "get_next_line.h"
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>

//	MACRO
# define TITLE "My Cub3D"
# define TILE_SIZE 32
# define HEIGHT 1440
# define WIDTH 2560
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
	int			keyw;
	int			keys;
	int			keya;
	int			keyd;
	int			keyl;
	int			keyr;
}				t_keys;

typedef struct s_point
{
	double		x;
	double		y;
}				t_point;

typedef struct s_ray
{
	float		angle;
	float		dist;
	bool		hit_hor;
	t_point		inter;
}				t_ray;

typedef struct s_cube
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			sizeline;
	int			endian;
	int			width;
	int			height;

	char		**file;
	char		**map;
	void		*no;
	void		*so;
	void		*we;
	void		*ea;
	int			floor;
	int			ceiling;

	int			mnm_pix;
	int			map_l;
	int			map_h;
	int			pov;
	float		pos[2];//position personnage : pos[0] = x   pos[1] = y
	float		dist;
	int			walldir;
	t_keys		k;
	t_ray		rays[FOV];
}				t_cube;

typedef struct s_gnl
{
	int		ret;
	int		bean;
	int		size;
	char	c;
}			t_gnl;

//	PARSING
int		check_each_elem(char *l, int *tab, int *count);
int		check_elems(t_cube *s);
int		check_map(t_cube *s);
int		create_map(t_cube *s, int i);
int		data_collect(t_cube *s);
int		valid_char(t_cube *s);
int		parsing(t_cube *s, int ac, char **av);
void	get_player_position(t_cube *s);

//	KEY CONTROL
int		keypress(int key, t_cube *s);
int		keyrelease(int key, t_cube *s);

//	UTILS
int		cmp(char *str, char *l);
void	free_all(t_cube *s);
void	free_array(char **str);
char	*get_fn(char *l);
int		write_error(char *message);

//	MATHS UTILS
float	rad(float degree);
float	dist_ab(float x1, float y1, float x2, float y2);
float	normalize_angle(float angle);
float	wall_intersections(t_cube *s, float deg);

//	DISPLAY
int		create_trgb(int t, int r, int g, int b);
void	draw_minimap(t_cube *s);
void	draw_player_view(t_cube *s);
void	my_mlx_pixel_put(t_cube *s, int x, int y, int color);
t_uint	get_pixel_color(t_cube *s, int x, int y);

//	RAYCASTING
void	balayage(t_cube *s, float deg);
int		isfacedown(double angle);
int		isfaceup(double angle);
int		isfaceright(double angle);
int		isfaceleft(double angle);

#endif
