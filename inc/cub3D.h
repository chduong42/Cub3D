/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:10:40 by jvermeer          #+#    #+#             */
/*   Updated: 2022/05/24 18:53:46 by chduong          ###   ########.fr       */
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
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define TITLE "My Cub3D"
# define LENGTH 1000
# define HEIGHT 800
# define FOV 60

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

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}			t_color;

typedef struct s_data
{
	int		bpp;
	int		width;
	int		height;
	int		endian;
	int		size_line;
	int		img_size;
	char	*img_data;
	void	*img_ptr;
}			t_data;

typedef struct s_cube
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;

	char	**file;
	char	**map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor[3];
	int		ceiling[3];

	int		bpp;
	int		sizeline;
	int		endian;
	int		mnm_pix;

	int		map_len;
	int		map_height;
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
int		buffcomp(char *str, char *l);
int		check_each_elem(char *l, int *tab);
int		check_elems(t_cube *s);
int		check_map(t_cube *s);
int		create_map(t_cube *s, int i);
int		data_collect(t_cube *s);// apres parsing : pour collecter donnees
int		valid_char(t_cube *s);
int		parsing(t_cube *s, int ac, char **av);

//	KEY CONTROL
//int	all_keys(int key, t_cube *s);
int		keypress(int key, t_cube *s);
int		keyrelease(int key, t_cube *s);

//	UTILS
void	free_all(t_cube *s);
void	free_array(char **str);
char	**get_file(char **av, int *fd);
char	*get_file_name(char *l);
int		get_next_line(int fd, char **line);
int		write_error(char *message);
float	wall_intersections(t_cube *s, int deg);//dist en fonct du degree et pos

//	DISPLAY
void	draw_minimap(t_cube *s);

//	PIXEL UTILS
void	my_mlx_pixel_put(t_cube *s, int x, int y, int color);
void	write_big_pixel(t_cube *s, int x, int y, int color);
int		create_trgb(int t, int r, int g, int b);
t_uint	get_pixel_color(t_data *text, int x, int y);

#endif
