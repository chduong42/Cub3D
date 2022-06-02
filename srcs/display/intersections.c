/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 09:46:00 by jvermeer          #+#    #+#             */
/*   Updated: 2022/06/02 21:10:02 by chduong          ###   ########.fr       */
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
	return (x1 / cos(radian));
}

int	wall_right(t_cube *s, float y, float x)
{
	int	posy;
	int	posx;

	posy = (int)y;
	posx = (int)x;
	if (posy < 0 || posx >= s->map_l)
		return (1);
	if (s->map[posy][posx] == '1')
		return (1);
	return (0);
}

float	verti_zero_ninety(t_cube *s, float radian, float *pos)
{
	float	x1;
	float	y1;
	float	ya;

	x1 = 1 - (pos[0] - (int)pos[0]);
	y1 = x1 * tan(radian);
	ya = 1 * tan(radian);
	while (wall_right(s, (pos[1] - y1), (pos[0]) + x1) == 0)
	{
		y1 = y1 + ya;
		x1 = x1 + 1;
	}
	return (x1 / cos(radian));
}

float	zero_ninety(t_cube*s, int deg, float *pos)
{
	float	len;
	float	len2;

	if (deg == 90)
		return (hori_zero_ninety(s, rad(deg), pos));
	else if (deg == 0)
		return (verti_zero_ninety(s, rad(deg), pos));
	len = hori_zero_ninety(s, rad(deg), pos);
	len2 = verti_zero_ninety(s, rad(deg), pos);
	if (len < len2)
		return (len);
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

float	hori_noe(t_cube *s, float radian, float *pos)
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
	y1 = x1 / tan(radian);
	ya = 1 / tan(radian);
	while (wall_left_noe(s, pos[1] - y1, pos[0] - x1) == 0)
	{
		y1 = y1 + ya;
		x1 = x1 + 1;
	}
	return (y1 / cos(radian));
}

float	ninety_one_eighty(t_cube*s, int deg, float *pos)
{
	float	len;
	float	len2;

	if (deg == 90)
		return (verti_noe(s, rad(deg), pos));
	len = hori_noe(s, rad(deg), pos);
	len2 = verti_noe(s, rad(deg), pos);
	if (len < len2)
		return (len);
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

float	verti_oets(t_cube *s, float radian, float *pos)
{
	float	x1;
	float	y1;
	float	ya;

	x1 = pos[0] - (int)pos[0];
	y1 = x1 * tan(radian);
	ya = 1 * tan(radian);
	while (wall_left_oets(s, pos[1] + y1, pos[0] - x1) == 0)
	{
		y1 = y1 + ya;
		x1 = x1 + 1;
	}
	return (x1 / cos(radian));
}

float	one_eighty_two_seventy(t_cube*s, int deg, float *pos)
{
	float	len;
	float	len2;

	if (deg == 90)
		return (hori_oets(s, rad(deg), pos));
	len = hori_oets(s, rad(deg), pos);
	len2 = verti_oets(s, rad(deg), pos);
	if (len < len2)
		return (len);
	return (len2);
}

//////////////////////////////////////////////////////////////////

int	wall_right_tsts(t_cube *s, float y, float x)
{
	int	posy;
	int	posx;

	posy = (int)y;
	posx = (int)x + 0.5;
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
	y1 = x1 / tan(radian);
	ya = 1 / tan(radian);
	while (wall_right_tsts(s, pos[1] + y1, pos[0] + x1) == 0)
	{
		y1 = y1 + ya;
		x1 = x1 + 1;
	}
	return (y1 / cos(radian));
}

int	wall_under_tsts(t_cube *s, float y, float x)
{
	int	posy;
	int	posx;

	posy = (int)y + 0.5;
	posx = (int)x;
	if (posy >= s->map_h || posx >= s->map_l)
		return (1);
	if (s->map[posy][posx] == '1')
		return (1);
	return (0);
}

float	hori_tsts(t_cube *s, float radian, float *pos)
{
	float	y1;
	float	x1;
	float	xa;

	y1 = 1 - (pos[1] - (int)pos[1]);
	x1 = y1 * tanf(radian);
	xa = 1 * tanf(radian);
	while (wall_under_tsts(s, pos[1] + y1, pos[0] + x1) == 0)
	{
		y1 = y1 + 1;
		x1 = x1 + xa;
	}
	return (y1 / cos(radian));
}

float	two_seventy_three_sixty(t_cube*s, int deg, float *pos)
{
	float	len;
	float	len2;

	len = hori_tsts(s, rad(deg), pos);
	len2 = verti_tsts(s, rad(deg), pos);
	if (len < len2)
		return (len);
	return (len2);
}

//////////////////////////////////////////////////////////////////

float	wall_intersections(t_cube *s, int deg)
{
	float	len;
	float	pos[2];

	len = 0;
	pos[0] = s->pos[0];
	pos[1] = s->pos[1];
	if (deg >= 0 && deg <= 90)
		len = zero_ninety(s, deg, pos);
	else if (deg > 90 && deg <= 180)
		len = ninety_one_eighty(s, deg - 90, pos);
	else if (deg > 180 && deg <= 270)
		len = one_eighty_two_seventy(s, deg - 180, pos);
	else
		len = two_seventy_three_sixty(s, deg - 270, pos);
	return (len);
}
