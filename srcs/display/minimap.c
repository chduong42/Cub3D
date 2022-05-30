/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:42:47 by jvermeer          #+#    #+#             */
/*   Updated: 2022/05/30 13:22:31 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_background(t_cube *s)
{
	int	x;	
	int	y;	

	y = 0;
	while (y < s->map_h)
	{
		x = 0;
		while (x < s->map_l)
		{
			if (s->map[y][x] == '1')
				write_big_pixel(s, 10 + x * s->mnm_pix,
					10 + y * s->mnm_pix, 0x00278727);
			else if (!ft_isspace(s->map[y][x]))
				write_big_pixel(s, 10 + x * s->mnm_pix,
					10 + y * s->mnm_pix, 0x00A7C553);
			x++;
		}
		y++;
	}
}

static void	draw_player(t_cube *s)
{
	int	px;
	int	py;
	int	i;
	int	j;
	int	size;

	size = 10;
	if (s->map_l > 30 || s->map_h > 30)
		size = 5;
	px = 10 + s->pos[0] * s->mnm_pix;
	py = 10 + s->pos[1] * s->mnm_pix;
	i = px - (s->mnm_pix / size);
	while (i <= px + (s->mnm_pix / size))
	{
		j = py - (s->mnm_pix / size);
		while (j <= py + (s->mnm_pix / size))
		{
			my_mlx_pixel_put(s, i, j, 0x000000FF);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_cube *s)
{
	draw_background(s);
	draw_player(s);
}
