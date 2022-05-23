/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvermeer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:42:47 by jvermeer          #+#    #+#             */
/*   Updated: 2022/05/20 14:34:19 by jvermeer         ###   ########.fr       */
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
	while (y < s->mapwid)
	{
		x = 0;
		while (x < s->maplen)
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
	if (s->maplen > 30 || s->mapwid > 30)
		size = 5;
	px = 10 + s->mnmpos[0] * s->mnm_pix;
	py = 10 + s->mnmpos[1] * s->mnm_pix;
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
