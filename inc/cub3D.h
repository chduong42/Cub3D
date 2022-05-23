/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 16:10:40 by jvermeer          #+#    #+#             */
/*   Updated: 2022/05/23 14:33:15 by chduong          ###   ########.fr       */
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
# define WIDTH 800
# define LENGTH 800

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
	char	**file;
	char	**map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor[3];
	int		ceiling[3];
	int		nblines;
	int		maplen;
	int		mapwid;
	t_keys	k;
	int		bpp;
	int		sizeline;
	int		endian;
	void	*cube_win;
	void	*cube_ptr;
	void	*image;
	char	*addr;
	int		mnm_pix;

	float	mnmpos[2];//position personnage : pos[0] = x   pos[1] = y
	int		pov;
	float	dist;
}				t_cube;

typedef struct s_gnl
{
	int		ret;
	int		bean;
	int		size;
	char	c;
}				t_gnl;

//	FUNCTIONS
int			buffcomp(char *str, char *l);//
int			data_collect(t_cube *s);// apres parsing : pour collecter donnees
int			parsing(t_cube *s, int ac, char **av);
int			write_error(char *message);
//int		all_keys(int key, t_cube *s);
int			keypress(int key, t_cube *s);
int			keyrelease(int key, t_cube *s);
int			get_next_line(int fd, char **line);

char		**get_all_file(t_cube *s, char **av, int *fd);
char		*get_file_name(char *l);// avec gnl, pour recup contenue fichier

void		draw_player(t_cube *s);
void		draw_background(t_cube *s);
void		free_all(t_cube *s);
void		free_array(char **str);
void		my_mlx_pixel_put(t_cube *s, int x, int y, int color);
void		write_big_pixel(t_cube *s, int x, int y, int color);

float		wall_intersections(t_cube *s, int deg);//renvoie une distance en fonction du degree et position du joueur

#endif
