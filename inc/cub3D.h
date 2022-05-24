/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:10:40 by jvermeer          #+#    #+#             */
/*   Updated: 2022/05/23 23:48:41 by chduong          ###   ########.fr       */
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
# define LENGTH 1280
# define HEIGHT 800

//	Key Code
# define A 97
# define D 100
# define S 115
# define W 119
# define ESC 65307
# define LEFT 65361
# define RIGHT 65363

typedef struct s_keys
{
	int	keyw;
	int	keys;
	int	keya;
	int	keyd;
	int	keyl;
	int	keyr;
}				t_keys;

//	TYPE DEF
typedef struct s_cube
{
	void	*win;
	void	*ptr;
	void	*image;
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
}				t_cube;

typedef struct s_gnl
{
	int		ret;
	int		bean;
	int		size;
	char	c;
}				t_gnl;

//	FUNCTIONS
int		buffcomp(char *str, char *l);
int		create_map(t_cube *s, int i);
int		data_collect(t_cube *s);// apres parsing : pour collecter donnees
int		parsing(t_cube *s, int ac, char **av);

//	KEY CONTROL
//int	all_keys(int key, t_cube *s);
int		keypress(int key, t_cube *s);
int		keyrelease(int key, t_cube *s);

//	UTILS
int		get_next_line(int fd, char **line);
char	**get_file(char **av, int *fd);
char	*get_file_name(char *l);
void	free_all(t_cube *s);
void	free_array(char **str);
int		write_error(char *message);
float	wall_intersections(t_cube *s, int deg);//dist en fonct du degree et pos

//	DISPLAY
void	draw_player(t_cube *s);
void	draw_background(t_cube *s);
void	my_mlx_pixel_put(t_cube *s, int x, int y, int color);
void	write_big_pixel(t_cube *s, int x, int y, int color);

#endif
