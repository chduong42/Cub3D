/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_270_to_360.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 23:10:03 by chduong           #+#    #+#             */
/*   Updated: 2022/06/09 23:16:03 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	wall_right_tsts(t_cube *s, float y, float x)
{
	int	posy;
	int	posx;

	posy = (int)y;
	posx = (int)(x + 0.5);
	if (posy >= s->map.h || posx >= s->map.w)
		return (1);
	if (s->maps[posy][posx] == '1')
		return (1);
	return (0);
}

static float	verti_tsts(t_cube *s, float radian, t_point pos)
{
	float	x1;
	float	y1;
	float	ya;

	x1 = 1 - (pos.x - (int)pos.x);
	y1 = x1 / tanf(radian);
	ya = 1 / tanf(radian);
	while (wall_right_tsts(s, pos.y + y1, pos.x + x1) == 0)
	{
		y1 = y1 + ya;
		x1 = x1 + 1;
	}
	s->hit.x = pos.x + x1;
	s->hit.y = pos.y + y1;
	return (y1 / cos(radian));
}

static int	wall_under_tsts(t_cube *s, float y, float x)
{
	int	posy;
	int	posx;

	posy = (int)(y + 0.5);
	posx = (int)x;
	if (posy >= s->map.h || posx >= s->map.w)
		return (1);
	if (s->maps[posy][posx] == '1')
		return (1);
	return (0);
}

static float	hori_tsts(t_cube *s, float radian, t_point pos, t_point *hit)
{
	float	y1;
	float	x1;
	float	xa;

	y1 = 1 - (pos.y - (int)pos.y);
	x1 = y1 * tanf(radian);
	xa = tanf(radian);
	while (wall_under_tsts(s, pos.y + y1, pos.x + x1) == 0)
	{
		y1 = y1 + 1;
		x1 = x1 + xa;
	}
	hit->x = pos.x + x1;
	hit->y = pos.y + y1;
	return (y1 / cos(radian));
}

float	ft_270_to_360(t_cube*s, float radian, t_point pos)
{
	float	len;
	float	len2;
	t_point	hit;

	if (radian == rad(0))
	{
		s->walldir = 3;
		return (verti_tsts(s, radian, pos));
	}
	len = hori_tsts(s, radian, pos, &hit);
	len2 = verti_tsts(s, radian, pos);
	if (len < len2)
	{
		s->hit.x = hit.x;
		s->hit.y = hit.y;
		s->walldir = 2;
		return (len);
	}
	s->walldir = 3;
	return (len2);
}
