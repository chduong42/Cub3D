/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 09:56:08 by jvermeer          #+#    #+#             */
/*   Updated: 2022/05/18 16:42:55 by chduong          ###   ########.fr       */
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
	void	*m_ptr;
	void	*w_ptr;
	int		nblines;
	int		maplen;
	int		mapwid;

	void	*cube_win;
	void	*cube_ptr;

//	void	*image;
	int		scope;
	void	*miniw;
	void	*minig;
	void	*minip;
	float	mnmpos[2];
	int		pov;
}				t_cube;
typedef struct s_gnl
{
	int		ret;
	int		bean;
	int		size;
	char	c;
}				t_gnl;
char			**get_all_file(t_cube *s, char **av, int *fd);
int				write_error(char *message);
void			free_all(t_cube *s);
void			free_array(char **str);
char			*get_file_name(char *l);
int				parsing(t_cube *s, int ac, char **av);
int				buffcomp(char *str, char *l);
int				data_collect(t_cube *s);
float			wall_intersections(t_cube *s, int deg);

#endif
