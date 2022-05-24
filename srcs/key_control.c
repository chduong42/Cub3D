/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:47:25 by jvermeer          #+#    #+#             */
/*   Updated: 2022/05/24 18:54:10 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	wasd_keys(t_cube *s, float speed, float dist)
{
	if (s->k.keyw == 1)
	{
		s->pos[1] = s->pos[1] - speed;
		if (s->map[(int)(s->pos[1] - dist / 2)][(int)s->pos[0]] == '1')
			s->pos[1] = s->pos[1] + speed;
	}
	if (s->k.keys == 1)
	{
		s->pos[1] = s->pos[1] + speed;
		if (s->map[(int)(s->pos[1] + dist / 2)][(int)s->pos[0]] == '1')
			s->pos[1] = s->pos[1] - speed;
	}
	if (s->k.keya == 1)
	{
		s->pos[0] = s->pos[0] - speed;
		if (s->map[(int)s->pos[1]][(int)(s->pos[0] - dist / 2)] == '1')
			s->pos[0] = s->pos[0] + speed;
	}
	if (s->k.keyd == 1)
	{
		s->pos[0] = s->pos[0] + speed;
		if (s->map[(int)s->pos[1]][(int)(s->pos[0] + dist / 2)] == '1')
			s->pos[0] = s->pos[0] - speed;
	}
}

void	keys_effects(t_cube *s)
{
	float	speed;
	float	dist;

	speed = 0.1;
	dist = 0.1;
	if (s->k.keyw == 1 || s->k.keya == 1 || s->k.keys == 1 || s->k.keyd == 1)
		wasd_keys(s, speed, dist);
	if (s->k.keyl == 1)
		s->pov = s->pov + 3;
	if (s->k.keyr == 1)
		s->pov = s->pov - 3;
	if (s->pov < 0)
		s->pov = 360 + s->pov;
	if (s->pov > 359)
		s->pov = s->pov - 360;
}

int	keyrelease(int key, t_cube *s)
{
	if (key == W)
		s->k.keyw = 0;
	if (key == A)
		s->k.keya = 0;
	if (key == S)
		s->k.keys = 0;
	if (key == D)
		s->k.keyd = 0;
	if (key == LEFT)
		s->k.keyl = 0;
	if (key == RIGHT)
		s->k.keyr = 0;
	return (0);
}

int	keypress(int key, t_cube *s)
{
	if (key == ESC)
		mlx_loop_end(s->mlx);
	if (key == W)
		s->k.keyw = 1;
	if (key == A)
		s->k.keya = 1;
	if (key == S)
		s->k.keys = 1;
	if (key == D)
		s->k.keyd = 1;
	if (key == LEFT)
		s->k.keyl = 1;
	if (key == RIGHT)
		s->k.keyr = 1;
	keys_effects(s);
	draw_minimap(s);
	printf("POV:%d\n", s->pov);
	s->dist = wall_intersections(s, s->pov);
	printf("DIST:%f\n", s->dist);
	mlx_put_image_to_window(s->mlx, s->win, s->img, 0, 0);
	return (0);
}
