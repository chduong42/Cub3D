/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 08:58:22 by jvermeer          #+#    #+#             */
/*   Updated: 2022/05/23 12:34:26 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	initializekeys(t_cube *s)
{
	s->k.keyw = 0;
	s->k.keys = 0;
	s->k.keya = 0;
	s->k.keyd = 0;
	s->k.keyr = 0;
	s->k.keyl = 0;
}

void	initializestru(t_cube *s)
{
	s->file = NULL;
	s->map = NULL;
	s->no = NULL;
	s->so = NULL;
	s->we = NULL;
	s->ea = NULL;
	s->pov = 10;
	s->image = NULL;
	s->cube_ptr = NULL;
	s->cube_win = NULL;
	initializekeys(s);
}

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
				s->mnmpos[0] = (float)x + 0.5;
				s->mnmpos[1] = (float)y + 0.5;
			}
			x++;
		}
		y++;
	}
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
	get_pos_player(&s);
	s.cube_ptr = mlx_init();
	s.cube_win = mlx_new_window(s.cube_ptr, WIDTH, LENGTH, TITLE);
	s.image = mlx_new_image(s.cube_ptr, WIDTH, LENGTH);
	s.addr = mlx_get_data_addr(s.image, &s.bpp, &s.sizeline, &s.endian);
	draw_background(&s);
	draw_player(&s);
	mlx_put_image_to_window(s.cube_ptr, s.cube_win, s.image, 0, 0);
	mlx_hook(s.cube_win, 2, (1L << 0), keypress, (void *)&s);
	mlx_hook(s.cube_win, 3, (1L << 1), keyrelease, (void *)&s);
	mlx_hook(s.cube_win, 17, (1L << 17), mlx_loop_end, s.cube_ptr);
	mlx_loop(s.cube_ptr);
	free_all(&s);
	return (0);
}
