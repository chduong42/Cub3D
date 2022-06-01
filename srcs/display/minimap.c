/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:42:47 by jvermeer          #+#    #+#             */
/*   Updated: 2022/06/01 14:56:21 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	put_big_pixel(t_cube *s, int x, int y, int color)
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
				put_big_pixel(s, 10 + x * s->mnm_pix,
					10 + y * s->mnm_pix, 0x00278727);
			else if (!ft_isspace(s->map[y][x]))
				put_big_pixel(s, 10 + x * s->mnm_pix,
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

static void	draw_pov(t_cube *s, float px, float py)
{
	int	i;
	int	j;

	i = px - 2;
	while (i <= px + 2)
	{
		j = py - 2;
		while (j <= py + 2)
		{
			if (px < 5 + s->map_l * s->mnm_pix && px > 15
				&& py < s->map_h * s->mnm_pix && py > 15)
			{
				if (s->map[(j - 10) / s->mnm_pix][(i - 10) / s->mnm_pix] != ' ')
					my_mlx_pixel_put(s, i, j, 0x00FF0000);
			}
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_cube *s)
{
	float	radian;
	float	dst;
	float	px;
	float	py;

	dst = 30;
	radian = rad(s->pov);
	px = 10 + s->pos[0] * s->mnm_pix;
	py = 10 + s->pos[1] * s->mnm_pix;
	draw_background(s);
	draw_player(s);
	draw_pov(s, px + dst * cos(radian), py - dst * sin(radian));
}
