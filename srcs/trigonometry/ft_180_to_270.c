/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_180_to_270.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 23:09:29 by chduong           #+#    #+#             */
/*   Updated: 2022/06/09 23:16:44 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	wall_under_oets(t_cube *s, float y, float x)
{
	int	posy;
	int	posx;

	posy = (int)(y + 0.5);
	posx = (int)x;
	if (posy >= s->map.h || posx < 0)
		return (1);
	if (s->maps[posy][posx] == '1')
		return (1);
	return (0);
}

static float	hori_oets(t_cube *s, float radian, t_point pos)
{
	float	y1;
	float	x1;
	float	xa;

	y1 = 1 - (pos.y - (int)pos.y);
	x1 = y1 / tanf(radian);
	xa = 1 / tanf(radian);
	while (wall_under_oets(s, pos.y + y1, pos.x - x1) == 0)
	{
		y1 = y1 + 1;
		x1 = x1 + xa;
	}
	s->hit.x = pos.x - x1;
	s->hit.y = pos.y + y1;
	return (x1 / cos(radian));
}

static int	wall_left_oets(t_cube *s, float y, float x)
{
	int	posy;
	int	posx;

	posy = (int)y;
	posx = (int)(x - 0.5);
	if (posy >= s->map.h || posx < 0)
		return (1);
	if (s->maps[posy][posx] == '1')
		return (1);
	return (0);
}

static float	verti_oets(t_cube *s, float radian, t_point pos, t_point *hit)
{
	float	x1;
	float	y1;
	float	ya;

	x1 = pos.x - (int)pos.x;
	y1 = x1 * tanf(radian);
	ya = 1 * tanf(radian);
	while (wall_left_oets(s, pos.y + y1, pos.x - x1) == 0)
	{
		y1 = y1 + ya;
		x1 = x1 + 1;
	}
	hit->x = pos.x - x1;
	hit->y = pos.y + y1;
	return (x1 / cos(radian));
}

float	ft_180_to_270(t_cube*s, float radian, t_point pos)
{
	float	len;
	float	len2;
	t_point	hit;

	if (radian == rad(90))
	{
		s->walldir = 2;
		return (hori_oets(s, radian, pos));
	}
	len = hori_oets(s, radian, pos);
	len2 = verti_oets(s, radian, pos, &hit);
	if (len < len2)
	{
		s->walldir = 2;
		return (len);
	}
	s->hit.x = hit.x;
	s->hit.y = hit.y;
	s->walldir = 4;
	return (len2);
}
