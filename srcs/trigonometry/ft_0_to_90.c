/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_0_to_90.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 23:07:39 by chduong           #+#    #+#             */
/*   Updated: 2022/06/09 23:36:55 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	wall_above(t_cube *s, float y, float x)
{
	int	posy;
	int	posx;

	posy = (int)(y - 0.5);
	posx = (int)(x);
	if (posy < 0 || posx >= s->map.w)
		return (1);
	if (s->maps[posy][posx] == '1')
		return (1);
	return (0);
}

static float	hori_zero_ninety(t_cube *s, float radian, t_point pos)
{
	float	y1;
	float	x1;
	float	xa;

	y1 = pos.y - (int)pos.y;
	x1 = y1 / tanf(radian);
	xa = 1 / tanf(radian);
	while (wall_above(s, (pos.y - y1), (pos.x) + x1) == 0)
	{
		y1 = y1 + 1;
		x1 = x1 + xa;
	}
	s->hit.x = pos.x + x1;
	s->hit.y = pos.y - y1;
	return (x1 / cos(radian));
}

static int	wall_right(t_cube *s, float y, float x)
{
	int	posy;
	int	posx;

	posy = (int)y;
	posx = (int)(x + 0.5);
	if (posy < 0 || posx >= s->map.w)
		return (1);
	if (s->maps[posy][posx] == '1')
		return (1);
	return (0);
}

static float	ver_0_to_90(t_cube *s, float radian, t_point pos, t_point *hit)
{
	float	x1;
	float	y1;
	float	ya;

	x1 = 1 - (pos.x - (int)pos.x);
	y1 = x1 * tanf(radian);
	ya = tanf(radian);
	while (wall_right(s, (pos.y - y1), (pos.x) + x1) == 0)
	{
		y1 = y1 + ya;
		x1 = x1 + 1;
	}
	hit->x = pos.x + x1;
	hit->y = pos.y - y1;
	return (x1 / cos(radian));
}

float	ft_0_to_90(t_cube*s, float radian, t_point pos)
{
	float	len;
	float	len2;
	t_point	hit;

	if (radian == rad(90))
	{
		s->walldir = 1;
		return (hori_zero_ninety(s, radian, pos));
	}
	len = hori_zero_ninety(s, radian, pos);
	len2 = ver_0_to_90(s, radian, pos, &hit);
	if (len < len2)
	{
		s->walldir = 1;
		return (len);
	}
	s->hit.x = hit.x;
	s->hit.y = hit.y;
	s->walldir = 3;
	return (len2);
}
