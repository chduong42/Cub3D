/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:35:31 by chduong           #+#    #+#             */
/*   Updated: 2022/06/09 23:29:12 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static float	wall_intersections(t_cube *s, float deg)
{
	float	len;

	len = 0;
	if (deg > 0 && deg <= 90)
		len = ft_0_to_90(s, rad(deg), s->pos);
	else if (deg > 90 && deg <= 180)
		len = ft_90_to_180(s, rad(deg - 90), s->pos);
	else if (deg > 180 && deg <= 270)
		len = ft_180_to_270(s, rad(deg - 180), s->pos);
	else
		len = ft_270_to_360(s, rad(deg - 270), s->pos);
	return (len);
}

void	my_mlx_pixel_put(t_cube *s, int x, int y, int color)
{
	char	*dst;

	dst = s->addr + (y * s->sizeline + x * s->bpp / 8);
	*(unsigned int *)dst = color;
}

static int	get_pixel_bitmap(t_cube *s, int y)
{
	int		x;
	char	*dst;
	int		bpp;
	int		sizeline;

	if (s->walldir == 1 || s->walldir == 2)
		x = (int)(s->hit.x * 64) % 64;
	else
		x = (int)(s->hit.y * 64) % 64;
	if (s->walldir == 1)
		dst = mlx_get_data_addr(s->no, &bpp, &sizeline, &s->endian);
	else if (s->walldir == 2)
		dst = mlx_get_data_addr(s->so, &bpp, &sizeline, &s->endian);
	else if (s->walldir == 3)
		dst = mlx_get_data_addr(s->ea, &bpp, &sizeline, &s->endian);
	else
		dst = mlx_get_data_addr(s->we, &bpp, &sizeline, &s->endian);
	dst = dst + (y * sizeline + x * bpp / 8);
	return (*(unsigned int *)dst);
}

static void	raycasting(t_cube *s, int column)
{
	int		size_slice;
	int		color;
	int		begin;
	int		y;

	y = 0;
	size_slice = 64 / (s->dist * 64) * s->dist_project;
	begin = (HEIGHT - size_slice) / 2;
	while (y < HEIGHT)
	{
		if (!(y >= 10 && y < (s->mnm_pix * s->map.h + 10)
				&& column >= 10 && column < (s->mnm_pix * s->map.w + 10)))
		{
			if (y < (HEIGHT - size_slice) / 2)
				my_mlx_pixel_put(s, column, y, s->ceiling);
			else if (y < (HEIGHT + size_slice) / 2)
			{
				color = get_pixel_bitmap(s, ((y - begin) * 64 / size_slice));
				my_mlx_pixel_put(s, column, y, color);
			}
			else
				my_mlx_pixel_put(s, column, y, s->floor);
		}
		y++;
	}
}

void	balayage(t_cube *s, float deg)
{
	int		column;
	float	gap;
	float	ray;

	column = 0;
	gap = (float)60 / (float)WIDTH;
	ray = deg + 30;
	if (ray > 359)
		ray = ray - 360;
	while (column < WIDTH)
	{
		if (ray >= deg)
			s->dist = wall_intersections(s, ray) * cos(rad(ray - deg));
		else
			s->dist = wall_intersections(s, ray) * cos(rad(deg - ray));
		raycasting(s, column);
		ray = ray - gap;
		if (ray < 0)
			ray = ray + 360;
		column++;
	}
	draw_minimap(s);
}
