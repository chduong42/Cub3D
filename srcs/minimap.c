/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:42:47 by jvermeer          #+#    #+#             */
/*   Updated: 2022/05/23 21:21:22 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put(t_cube *s, int x, int y, int color)
{
	char	*dst;

	dst = s->addr + (y * s->sizeline + x * s->bpp / 8);
	*(unsigned int *)dst = color;
}

void	write_big_pixel(t_cube *s, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < s->mnm_pix)
	{
		j = 0;
		while (j < s->mnm_pix)
		{
			my_mlx_pixel_put(s, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_background(t_cube *s)
{
	int	x;	
	int	y;	

	y = 0;
	while (y < s->map_height)
	{
		x = 0;
		while (x < s->map_len)
		{
			if (s->map[y][x] == '1')
				write_big_pixel(s, 10 + x * s->mnm_pix,
					10 + y * s->mnm_pix, 0x00278727);
			else if (s->map[y][x] != ' ')
				write_big_pixel(s, 10 + x * s->mnm_pix,
					10 + y * s->mnm_pix, 0x00A7C553);
			x++;
		}
		y++;
	}
}

void	draw_player(t_cube *s)
{
	int	px;
	int	py;
	int	i;
	int	j;
	int	size;

	size = 10;
	if (s->map_len > 30 || s->map_height > 30)
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
