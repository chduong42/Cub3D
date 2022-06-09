/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_90_to_180.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 23:08:27 by chduong           #+#    #+#             */
/*   Updated: 2022/06/09 23:36:17 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	wall_above_noe(t_cube *s, float y, float x)
{
	int	posy;
	int	posx;

	posy = (int)(y - 0.5);
	posx = (int)x;
	if (posy < 0 || posx < 0)
		return (1);
	if (s->maps[posy][posx] == '1')
		return (1);
	return (0);
}

static float	hori_noe(t_cube *s, float radian, t_point pos, t_point *hit)
{
	float	y1;
	float	x1;
	float	xa;

	y1 = pos.y - (int)pos.y;
	x1 = tanf(radian) * y1;
	xa = tanf(radian) * 1;
	while (wall_above_noe(s, pos.y - y1, pos.x - x1) == 0)
	{
		y1 = y1 + 1;
		x1 = x1 + xa;
	}
	hit->x = pos.x - x1;
	hit->y = pos.y - y1;
	return (y1 / cos(radian));
}

static int	wall_left_noe(t_cube *s, float y, float x)
{
	int	posy;
	int	posx;

	posy = (int)y;
	posx = (int)(x - 0.5);
	if (posy < 0 || posx < 0)
		return (1);
	if (s->maps[posy][posx] == '1')
		return (1);
	return (0);
}

static float	verti_noe(t_cube *s, float radian, t_point pos)
{
	float	x1;
	float	y1;
	float	ya;

	x1 = pos.x - (int)pos.x;
	y1 = x1 / tanf(radian);
	ya = 1 / tanf(radian);
	while (wall_left_noe(s, pos.y - y1, pos.x - x1) == 0)
	{
		y1 = y1 + ya;
		x1 = x1 + 1;
	}
	s->hit.x = pos.x - x1;
	s->hit.y = pos.y - y1;
	return (y1 / cos(radian));
}

float	ft_90_to_180(t_cube*s, float radian, t_point pos)
{
	float	len;
	float	len2;
	t_point	hit;

	if (radian == rad(90))
	{
		s->walldir = 4;
		return (verti_noe(s, radian, pos));
	}
	len = hori_noe(s, radian, pos, &hit);
	len2 = verti_noe(s, radian, pos);
	if (len < len2)
	{
		s->hit.x = hit.x;
		s->hit.y = hit.y;
		s->walldir = 1;
		return (len);
	}
	s->walldir = 4;
	return (len2);
}
