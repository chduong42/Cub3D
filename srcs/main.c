/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 08:58:22 by jvermeer          #+#    #+#             */
/*   Updated: 2022/05/18 16:22:56 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	initializestru(t_cube *s)
{
	s->file = NULL;
	s->map = NULL;
	s->no = NULL;
	s->so = NULL;
	s->we = NULL;
	s->ea = NULL;

//	s->image = NULL;
	s->pov = 90;

	s->cube_ptr = NULL;
	s->cube_win = NULL;
	s->miniw = NULL;
	s->minig = NULL;
	s->minip = NULL;
}

int	get_mnm_sprites(t_cube *s)
{
	int	a;

	a = 0;
	s->minip = mlx_xpm_file_to_image(s->cube_ptr, "sprites/minimap/minip.xpm", &a, &a);
	s->minig = mlx_xpm_file_to_image(s->cube_ptr, "sprites/minimap/minig.xpm", &a, &a);
	s->miniw = mlx_xpm_file_to_image(s->cube_ptr, "sprites/minimap/miniw.xpm", &a, &a);
	if (!s->minip || !s->minig || !s->miniw)
	{
		free_all(s);
		return (1);
	}
	return (0);
}


/*
int	hm_right(t_cube *s, int x, int y)
{
	int	i;

	i = 0;
	while (s->map[y][++x])
		i++;
	return (i);
}

int	hm_left(t_cube *s, int x, int y)
{
	int	i;

	i = 0;
	while (s->map[y][++x])
		i++;
	return (s->maplen - i - 1);
}

int	hm_bot(t_cube *s, int y)
{
	int	i;

	i = 0;
	while (s->map[++y])
		i++;
	return (i);
}

int	hm_top(t_cube *s, int y)
{
	int	i;

	i = 0;
	while (s->map[++y])
		i++;
	return (s->mapwid - i - 1);
}
void	topleft_two(t_cube *s, char c, int l, int t)
{
	if (c == '1')
		mlx_put_image_to_window(s->cube_ptr, s->cube_win, s->miniw, 500 - (l * 12), 500 - (t * 12));
	else if (c != ' ')
		mlx_put_image_to_window(s->cube_ptr, s->cube_win, s->minig, 500 - (l * 12), 500 - (t * 12));
}

void	print_top_left(t_cube *s, int x, int y, int top, int left)
{
	int	t;
	int	l;
	int	xx;
	
	t = 0;
	while (t < top && t < s->scope)
	{
		xx = x;
		l = 0;
		while (l < left && l < s->scope)
			topleft_two(s, s->map[y][xx--], l++, t);
		y--;
		t++;
	}
}

void	topright_two(t_cube *s, char c, int r, int t)
{
	if (c == '1')
		mlx_put_image_to_window(s->cube_ptr, s->cube_win, s->miniw, 500 + (r * 12), 500 - (t * 12));
	else if (c != ' ')
		mlx_put_image_to_window(s->cube_ptr, s->cube_win, s->minig, 500 + (r * 12), 500 - (t * 12));
}

void	print_top_right(t_cube *s, int x, int y, int top)
{
	int	t;
	int	r;
	int	xx;
	
	t = 0;
	while (t < top && t < s->scope)
	{
		xx = x;
		r = 0;
		while (s->map[y] && r < s->scope)
			topright_two(s, s->map[y][xx--], r++, t);
		y--;
		t++;
	}
}

void	moove_around_player(t_cube *s)
{
	int	x;
	int	y;

	s->scope = 3;
//	s->mnmpos[0] = s->mnmpos[0] + 0.5;
//	s->mnmpos[1] = s->mnmpos[1] + 0.5;
	x = (int)s->mnmpos[0];
	y = (int)s->mnmpos[1];
	printf("X:%d\n", x);
	printf("Y:%d\n", y);
	printf("R:%d\n", hm_right(s, x, y));
	printf("L:%d\n", hm_left(s, x, y));
	printf("B:%d\n", hm_bot(s, y));
	printf("T:%d\n", hm_top(s, y));
	mlx_put_image_to_window(s->cube_ptr, s->cube_win, s->minip, 12 * 12, 12 * 12);
//	print_top_left(s, x - 1, y - 1, hm_top(s, y), hm_left(s, x, y));
//	print_top_right(s, x, y - 1, hm_top(s, y));
//	print_background_mnm(s, hm_right(s, x, y), hm_left(s, x, y), hm_bot(s, y), hm_top(s, y));
}
*/

void	get_pos_player(t_cube *s)
{
	int		x;
	int		y;

	y = 0;
	while (y < s->mapwid)
	{
		x = 0;
		while (x < s->maplen)
		{
			if (s->map[y][x] == 'N' || s->map[y][x] == 'S'
				|| s->map[y][x] == 'E' || s->map[y][x] == 'W')
			{
				s->mnmpos[0] = (float)x;
				s->mnmpos[1] = (float)y;
			}
			x++;
		}
		y++;
	}
}

void	print_player(t_cube *s)
{
	int		x;
	int		y;

	y = 0;
	while (y < s->mapwid)
	{
		x = 0;
		while (x < s->maplen)
		{
			if (s->map[y][x] == 'N' || s->map[y][x] == 'S'
				|| s->map[y][x] == 'E' || s->map[y][x] == 'W')
			mlx_put_image_to_window(s->cube_ptr, s->cube_win, s->minip,
				(s->mnmpos[0] * 12), (s->mnmpos[1] * 12));
			x++;
		}
		y++;
	}
}

void	print_background(t_cube *s)
{
	int		x;
	int		y;

	y = 0;
	while (y < s->mapwid)
	{
		x = 0;
		while (x < s->maplen)
		{
			if (s->map[y][x] == '1')
				mlx_put_image_to_window(s->cube_ptr, s->cube_win, s->miniw,
					(x * 12), (y * 12));
			else if (s->map[y][x] != ' ')
				mlx_put_image_to_window(s->cube_ptr, s->cube_win, s->minig,
					(x * 12), (y * 12));
			x++;
		}
		y++;
	}
}

int	all_keys(int key, t_cube *s)
{
	float	speed;

	speed = 0.1;
	if (key == 65307)
		mlx_loop_end(s->cube_ptr);
	if (key == 119)
	{
		s->mnmpos[1] = s->mnmpos[1] - speed;
		if (s->map[(int)s->mnmpos[1]][(int)s->mnmpos[0]] == '1')
			s->mnmpos[1] = s->mnmpos[1] + speed;
	}
	if (key == 115)
	{
		s->mnmpos[1] = s->mnmpos[1] + speed;
		if (s->map[(int)s->mnmpos[1] + 1][(int)s->mnmpos[0]] == '1')
			s->mnmpos[1] = s->mnmpos[1] - speed;
	}
	if (key == 97)
	{
		s->mnmpos[0] = s->mnmpos[0] - speed;
		if (s->map[(int)s->mnmpos[1]][(int)s->mnmpos[0]] == '1')
			s->mnmpos[0] = s->mnmpos[0] + speed;
	}
	if (key == 100)
	{
		s->mnmpos[0] = s->mnmpos[0] + speed;
		if (s->map[(int)s->mnmpos[1]][(int)s->mnmpos[0] + 1] == '1')
			s->mnmpos[0] = s->mnmpos[0] - speed;
	}
	print_background(s);
	print_player(s);
	return (0);
}

int	point_of_view(int key, t_cube *s)
{
	if (key == 65361)
		s->pov = s->pov + 1;
	if (key == 65363)
		s->pov = s->pov - 1;
	if (s->pov == -1)
		s->pov = 359;
	if (s->pov == 360)
		s->pov = 0;
	printf("POV:%d\n", s->pov);
	printf("LEN:%f\n", wall_intersections(s, s->pov));

	return (0);
}

int	main(int ac, char **av)
{
	t_cube	s;

	initializestru(&s);
	if (!parsing(&s, ac, av) || !data_collect(&s))
	{
		free_all(&s);
		return (1);
	}
	s.cube_ptr = mlx_init();
	s.cube_win = mlx_new_window(s.cube_ptr, 800, 800, "cube3D");
	if (get_mnm_sprites(&s))
	{
		free_all(&s);
		return (1);
	}
	get_pos_player(&s);
//	s.mnmpos[0] = 3;
//	s.mnmpos[1] = 3;
	printf("LEN:%f\n", wall_intersections(&s, s.pov));
//	moove_around_player(&s);
	print_background(&s);
	print_player(&s);

	mlx_key_hook(s.cube_win, point_of_view, (void *)&s);
	mlx_hook(s.cube_win, 2, (1L << 0), all_keys, (void *)&s);
	mlx_hook(s.cube_win, 17, (1L << 17), mlx_loop_end, s.cube_ptr);
	mlx_loop(s.cube_ptr);
	
/*
	
	   s.m_ptr = mlx_init();
	   s.w_ptr = mlx_new_window(s.m_ptr,
	   (s.width * 64), (s.nblines * 64), "MyLove");
	   if (!get_mnm_sprites(&s))
	   return (0);
	   make_map(&s);
	   mlx_key_hook(s.w_ptr, all_keys, (void *)&s);
	   mlx_hook(s.w_ptr, 17, (1L << 17), mlx_loop_end, s.m_ptr);
	   mlx_loop(s.m_ptr);
	   free_and_leave(&s);
	 

	*/
	printf("OK\n");
	free_all(&s);
	return (0);
}
