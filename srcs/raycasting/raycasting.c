/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:18:43 by chduong           #+#    #+#             */
/*   Updated: 2022/06/06 20:59:01 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	iswall(char **map, double x, double y)
{
	int	grid_x;
	int	grid_y;

	grid_x = floor(x / TILE_SIZE);
	grid_y = floor(y / TILE_SIZE);
	return (map[grid_y][grid_x] == '1');
}

t_point	horiz_inter(t_cube *s, double angle)
{
	t_point	p;
	double	xstep;
	double	ystep;

	p.y = floor(s->pos[1] / TILE_SIZE) * TILE_SIZE;
	p.y += TILE_SIZE * (isfaceup(angle));
	p.x = s->pos[0] + ((p.y - s->pos[1]) / tan(angle));
	ystep = TILE_SIZE;
	if (isfacedown(angle))
		ystep *= -1;
	xstep = TILE_SIZE / (tan(angle));
	if ((isfaceright(angle) && xstep > 0) || (isfaceleft(angle) && xstep < 0))
		xstep *= -1;
	while (p.x >= 0 && p.x < (s->map_l * TILE_SIZE) && p.y >= 0
		&& p.y < (s->map_h * TILE_SIZE))
	{
		if (iswall(s->map, p.x, (p.y - isfacedown(angle) * 0.001)))
			break ;
		p.x += xstep;
		p.y += ystep;
	}
	return (p);
}

t_point	vert_inter(t_cube *s, double angle)
{
	t_point	p;
	double	xstep;
	double	ystep;

	p.x = floor(s->pos[0] / TILE_SIZE) * TILE_SIZE;
	p.x += TILE_SIZE * (isfaceleft(angle));
	p.y = s->pos[1] + ((p.x - s->pos[0]) * tan(angle));
	xstep = TILE_SIZE;
	if (isfaceright(angle))
		xstep *= -1;
	ystep = TILE_SIZE * tan(angle);
	if ((isfacedown(angle) && ystep > 0) || (isfaceup(angle) && ystep < 0))
		ystep *= -1;
	while (p.x >= 0.0 && p.x < (s->map_l * TILE_SIZE) && p.y >= 0.0
		&& p.y < (s->map_h * TILE_SIZE))
	{
		if (iswall(s->map, (p.x - isfaceright(angle) * 0.001), p.y))
			break ;
		p.x += xstep;
		p.y += ystep;
	}
	return (p);
}

t_ray	new_ray(t_cube *s, float angle, t_point inter, bool hor)
{
	t_ray	ray;

	ray.angle = angle;
	ray.inter = inter;
	ray.dist = dist_ab(s->pos[0], s->pos[1], inter.x, inter.y);
	ray.hit_hor = hor;
	if (hor)
	{
		if (isfaceup(angle))
			ray.texture = s->no;
		else
			ray.texture = s->so;
	}
	else
	{
		if (isfaceright(angle))
			ray.texture = s->ea;
		else
			ray.texture = s->we;
	}
	return (ray);
}

t_ray	raycast(t_cube *s, double angle)
{
	t_point		hor_inter;
	t_point		ver_inter;

	hor_inter = horiz_inter(s, angle);
	ver_inter = vert_inter(s, angle);
	if (hor_dist < ver_dist)
		return (new_ray(s, angle, hor_inter, 1));
	else
		return (new_ray(s, angle, ver_inter, 0));
}
