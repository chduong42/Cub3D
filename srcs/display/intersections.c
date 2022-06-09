/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 09:46:00 by jvermeer          #+#    #+#             */
/*   Updated: 2022/06/09 19:07:02 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	wall_above(t_cube *s, float y, float x)
{
	int	posy;
	int	posx;

	posy = (int)(y - 0.5);
	posx = (int)(x);
	if (posy < 0 || posx >= s->map_l)
		return (1);
	if (s->map[posy][posx] == '1')
		return (1);
	return (0);
}

float	hori_zero_ninety(t_cube *s, float radian, float *pos)
{
	float	y1;
	float	x1;
	float	xa;

	y1 = pos[1] - (int)pos[1];
	x1 = y1 / tanf(radian);
	xa = 1 / tanf(radian);
	while (wall_above(s, (pos[1] - y1), (pos[0]) + x1) == 0)
	{
		y1 = y1 + 1;
		x1 = x1 + xa;
	}
	s->hitpoint[0] = pos[0] + x1;
	s->hitpoint[1] = pos[1] - y1;
	return (x1 / cos(radian));
}

int	wall_right(t_cube *s, float y, float x)
{
	int	posy;
	int	posx;

	posy = (int)y;
	posx = (int)(x + 0.5);
	if (posy < 0 || posx >= s->map_l)
		return (1);
	if (s->map[posy][posx] == '1')
		return (1);
	return (0);
}

float	verti_zero_ninety(t_cube *s, float radian, float *pos, float *hit2)
{
	float	x1;
	float	y1;
	float	ya;

	x1 = 1 - (pos[0] - (int)pos[0]);
	y1 = x1 * tanf(radian);
	ya = tanf(radian);
	while (wall_right(s, (pos[1] - y1), (pos[0]) + x1) == 0)
	{
		y1 = y1 + ya;
		x1 = x1 + 1;
	}
	*hit2 = pos[0] + x1;
	*(hit2 + 1) = pos[1] - y1;
	return (x1 / cos(radian));
}

float	zero_ninety(t_cube*s, float radian, float *pos)
{
	float	len;
	float	len2;
	float	hit2[2];

	if (radian == rad(90))
	{
		s->walldir = 1;
		return (hori_zero_ninety(s, radian, pos));
	}
	len = hori_zero_ninety(s, radian, pos);
	len2 = verti_zero_ninety(s, radian, pos, hit2);
	if (len < len2)
	{
		s->walldir = 1;
		return (len);
	}
	s->hitpoint[0] = hit2[0];
	s->hitpoint[1] = hit2[1];
	s->walldir = 3;
	return (len2);
}
/////////////////////////////////////////////////////////////////////////

int	wall_above_noe(t_cube *s, float y, float x)
{
	int	posy;
	int	posx;

	posy = (int)(y - 0.5);
	posx = (int)x;
	if (posy < 0 || posx < 0)
		return (1);
	if (s->map[posy][posx] == '1')
		return (1);
	return (0);
}

float	hori_noe(t_cube *s, float radian, float *pos, float *hit2)
{
	float	y1;
	float	x1;
	float	xa;

	y1 = pos[1] - (int)pos[1];
	x1 = tanf(radian) * y1;
	xa = tanf(radian) * 1;
	while (wall_above_noe(s, pos[1] - y1, pos[0] - x1) == 0)
	{
		y1 = y1 + 1;
		x1 = x1 + xa;
	}
	*hit2 = pos[0] - x1;
	*(hit2 + 1) = pos[1] - y1;
	return (y1 / cos(radian));
}

int	wall_left_noe(t_cube *s, float y, float x)
{
	int	posy;
	int	posx;

	posy = (int)y;
	posx = (int)(x - 0.5);
	if (posy < 0 || posx < 0)
		return (1);
	if (s->map[posy][posx] == '1')
		return (1);
	return (0);
}

float	verti_noe(t_cube *s, float radian, float *pos)
{
	float	x1;
	float	y1;
	float	ya;

	x1 = pos[0] - (int)pos[0];
	y1 = x1 / tanf(radian);
	ya = 1 / tanf(radian);
	while (wall_left_noe(s, pos[1] - y1, pos[0] - x1) == 0)
	{
		y1 = y1 + ya;
		x1 = x1 + 1;
	}
	s->hitpoint[0] = pos[0] - x1;
	s->hitpoint[1] = pos[1] - y1;
	return (y1 / cos(radian));
}

float	ninety_one_eighty(t_cube*s, float radian, float *pos)
{
	float	len;
	float	len2;
	float	hit2[2];

	if (radian == rad(90))
	{
		s->walldir = 4;
		return (verti_noe(s, radian, pos));
	}
	len = hori_noe(s, radian, pos, hit2);
	len2 = verti_noe(s, radian, pos);
	if (len < len2)
	{
		s->hitpoint[0] = hit2[0];
		s->hitpoint[1] = hit2[1];
		s->walldir = 1;
		return (len);
	}
	s->walldir = 4;
	return (len2);
}

//////////////////////////////////////////////////////////////////

int	wall_under_oets(t_cube *s, float y, float x)
{
	int	posy;
	int	posx;

	posy = (int)(y + 0.5);
	posx = (int)x;
	if (posy >= s->map_h || posx < 0)
		return (1);
	if (s->map[posy][posx] == '1')
		return (1);
	return (0);
}

float	hori_oets(t_cube *s, float radian, float *pos)
{
	float	y1;
	float	x1;
	float	xa;

	y1 = 1 - (pos[1] - (int)pos[1]);
	x1 = y1 / tanf(radian);
	xa = 1 / tanf(radian);
	while (wall_under_oets(s, pos[1] + y1, pos[0] - x1) == 0)
	{
		y1 = y1 + 1;
		x1 = x1 + xa;
	}
	s->hitpoint[0] = pos[0] - x1;
	s->hitpoint[1] = pos[1] + y1;
	return (x1 / cos(radian));
}

int	wall_left_oets(t_cube *s, float y, float x)
{
	int	posy;
	int	posx;

	posy = (int)y;
	posx = (int)(x - 0.5);
	if (posy >= s->map_h || posx < 0)
		return (1);
	if (s->map[posy][posx] == '1')
		return (1);
	return (0);
}

float	verti_oets(t_cube *s, float radian, float *pos, float *hit2)
{
	float	x1;
	float	y1;
	float	ya;

	x1 = pos[0] - (int)pos[0];
	y1 = x1 * tanf(radian);
	ya = 1 * tanf(radian);
	while (wall_left_oets(s, pos[1] + y1, pos[0] - x1) == 0)
	{
		y1 = y1 + ya;
		x1 = x1 + 1;
	}
	*hit2 = pos[0] - x1;
	*(hit2 + 1) = pos[1] + y1;
	return (x1 / cos(radian));
}

float	one_eighty_two_seventy(t_cube*s, float radian, float *pos)
{
	float	len;
	float	len2;
	float	hit2[2];

	if (radian == rad(90))
	{
		s->walldir = 2;
		return (hori_oets(s, radian, pos));
	}
	len = hori_oets(s, radian, pos);
	len2 = verti_oets(s, radian, pos, hit2);
	if (len < len2)
	{
		s->walldir = 2;
		return (len);
	}
	s->hitpoint[0] = hit2[0];
	s->hitpoint[1] = hit2[1];
	s->walldir = 4;
	return (len2);
}

//////////////////////////////////////////////////////////////////

int	wall_right_tsts(t_cube *s, float y, float x)
{
	int	posy;
	int	posx;

	posy = (int)y;
	posx = (int)(x + 0.5);
	if (posy >= s->map_h || posx >= s->map_l)
		return (1);
	if (s->map[posy][posx] == '1')
		return (1);
	return (0);
}

float	verti_tsts(t_cube *s, float radian, float *pos)
{
	float	x1;
	float	y1;
	float	ya;

	x1 = 1 - (pos[0] - (int)pos[0]);
	y1 = x1 / tanf(radian);
	ya = 1 / tanf(radian);
	while (wall_right_tsts(s, pos[1] + y1, pos[0] + x1) == 0)
	{
		y1 = y1 + ya;
		x1 = x1 + 1;
	}
	s->hitpoint[0] = pos[0] + x1;
	s->hitpoint[1] = pos[1] + y1;
	return (y1 / cos(radian));
}

int	wall_under_tsts(t_cube *s, float y, float x)
{
	int	posy;
	int	posx;

	posy = (int)(y + 0.5);
	posx = (int)x;
	if (posy >= s->map_h || posx >= s->map_l)
		return (1);
	if (s->map[posy][posx] == '1')
		return (1);
	return (0);
}

float	hori_tsts(t_cube *s, float radian, float *pos, float *hit2)
{
	float	y1;
	float	x1;
	float	xa;

	y1 = 1 - (pos[1] - (int)pos[1]);
	x1 = y1 * tanf(radian);
	xa = tanf(radian);
	while (wall_under_tsts(s, pos[1] + y1, pos[0] + x1) == 0)
	{
		y1 = y1 + 1;
		x1 = x1 + xa;
	}
	*hit2 = pos[0] + x1;
	*(hit2 + 1) = pos[1] + y1;
	return (y1 / cos(radian));
}

float	two_seventy_three_sixty(t_cube*s, float radian, float *pos)
{
	float	len;
	float	len2;
	float	hit2[2];

	if (radian == rad(0))
	{
		s->walldir = 3;
		return (verti_tsts(s, radian, pos));
	}
	len = hori_tsts(s, radian, pos, hit2);
	len2 = verti_tsts(s, radian, pos);
	if (len < len2)
	{
		s->hitpoint[0] = hit2[0];
		s->hitpoint[1] = hit2[1];
		s->walldir = 2;
		return (len);
	}
	s->walldir = 3;
	return (len2);
}

//////////////////////////////////////////////////////////////////

float	wall_intersections(t_cube *s, float deg)
{
	float	len;

	len = 0;
	if (deg > 0 && deg <= 90)
		len = zero_ninety(s, rad(deg), s->pos);
	else if (deg > 90 && deg <= 180)
		len = ninety_one_eighty(s, rad(deg - 90), s->pos);
	else if (deg > 180 && deg <= 270)
		len = one_eighty_two_seventy(s, rad(deg - 180), s->pos);
	else
		len = two_seventy_three_sixty(s, rad(deg - 270), s->pos);
	return (len);
}

int		get_pixel_bitmap(t_cube *s, int y)
{
	int		x;
	char	*dst;
	int		bpp;
	int		sizeline;

	if (s->walldir == 1 || s->walldir == 2)
		x = (int)(s->hitpoint[0] * 64) % 64;
	else
		x = (int)(s->hitpoint[1] * 64) % 64;
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

void	raycasting(t_cube *s, int column)
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
		if (!(y >= 10 && y < (s->mnm_pix * s->map_h + 10)
				&& column >= 10 && column < (s->mnm_pix * s->map_l + 10)))
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
