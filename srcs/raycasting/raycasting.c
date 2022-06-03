/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:18:43 by chduong           #+#    #+#             */
/*   Updated: 2022/06/03 17:37:44 by chduong          ###   ########.fr       */
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

t_ray	new_ray(float angle, t_point inter, double dist, bool hor)
{
	t_ray	ray;

	ray.angle = angle;
	ray.inter = inter;
	ray.dist = dist;
	ray.hit_hor = hor;
	return (ray);
}

t_ray	raycast(t_cube *s, double angle)
{
	t_point		hor_inter;
	t_point		ver_inter;
	double		hor_dist;
	double		ver_dist;

	hor_inter = horiz_inter(s, angle);
	ver_inter = vert_inter(s, angle);
	hor_dist = dist_ab(s->pos[0], s->pos[1], hor_inter.x, hor_inter.y);
	ver_dist = dist_ab(s->pos[0], s->pos[1], ver_inter.x, ver_inter.y);
	if (hor_dist < ver_dist)
		return (new_ray(angle, hor_inter, hor_dist, 1));
	else
		return (new_ray(angle, ver_inter, ver_dist, 0));
}
