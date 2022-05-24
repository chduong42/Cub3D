/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 08:58:22 by jvermeer          #+#    #+#             */
/*   Updated: 2022/05/24 21:34:33 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_pos_player(t_cube *s)
{
	int		x;
	int		y;

	y = 0;
	while (y < s->map_height)
	{
		x = 0;
		while (x < s->map_len)
		{
			if (s->map[y][x] == 'N' || s->map[y][x] == 'S'
				|| s->map[y][x] == 'E' || s->map[y][x] == 'W')
			{
				s->pos[0] = (float)x + 0.5;
				s->pos[1] = (float)y + 0.5;
				return ;
			}
			x++;
		}
		y++;
	}
}

int	main(int ac, char **av)
{
	t_cube	s;

	ft_memset(&s, 0, sizeof(t_cube));
	if (!parsing(&s, ac, av) || !data_collect(&s))
	{
		free_all(&s);
		return (1);
	}
	s.mlx = mlx_init();
	s.win = mlx_new_window(s.mlx, LENGTH, HEIGHT, TITLE);
	s.img = mlx_new_image(s.mlx, LENGTH, HEIGHT);
	s.addr = mlx_get_data_addr(s.img, &s.bpp, &s.sizeline, &s.endian);
	get_pos_player(&s);
	draw_minimap(&s);
	mlx_put_image_to_window(s.mlx, s.win, s.img, 0, 0);
	mlx_hook(s.win, 2, (1L << 0), keypress, (void *)&s);
	mlx_hook(s.win, 3, (1L << 1), keyrelease, (void *)&s);
	mlx_hook(s.win, 17, (1L << 17), mlx_loop_end, s.mlx);
	mlx_loop(s.mlx);
	free_all(&s);
	return (0);
}
