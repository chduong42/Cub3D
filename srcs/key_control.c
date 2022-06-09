/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 17:47:25 by jvermeer          #+#    #+#             */
/*   Updated: 2022/06/09 18:53:01 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	choose_pos(t_cube *s, t_point new, float dist)
{
	if (s->maps[(int)new.y][(int)(new.x + dist)] != '1'
		&& s->maps[(int)new.y][(int)(new.x - dist)] != '1')
		s->pos.x = new.x;
	if (s->maps[(int)(new.y + dist)][(int)new.x] != '1'
		&& s->maps[(int)(new.y - dist)][(int)new.x] != '1')
		s->pos.y = new.y;
}

static void	wasd_keys(t_cube *s, t_point pos, float speed, float dist)
{
	if (s->k.keys == 1)
	{
		pos.x -= cos(rad(s->pov)) * speed;
		pos.y += sin(rad(s->pov)) * speed;
		choose_pos(s, pos, dist);
	}
	if (s->k.keyw == 1)
	{
		pos.x -= cos(rad(modulo_2pi(s->pov + 180))) * speed;
		pos.y += sin(rad(modulo_2pi(s->pov + 180))) * speed;
		choose_pos(s, pos, dist);
	}
	if (s->k.keya == 1)
	{
		pos.x += cos(rad(modulo_2pi(s->pov + 90))) * speed;
		pos.y -= sin(rad(modulo_2pi(s->pov + 90))) * speed;
		choose_pos(s, pos, dist);
	}
	if (s->k.keyd == 1)
	{
		pos.x += cos(rad(modulo_2pi(s->pov - 90))) * speed;
		pos.y -= sin(rad(modulo_2pi(s->pov - 90))) * speed;
		choose_pos(s, pos, dist);
	}
}

void	keys_effects(t_cube *s)
{
	float	speed;
	float	dist;

	speed = 0.2;
	dist = 0.15;
	wasd_keys(s, s->pos, speed, dist);
	if (s->k.keyl == 1)
		s->pov = modulo_2pi(s->pov + 3);
	if (s->k.keyr == 1)
		s->pov = modulo_2pi(s->pov - 3);
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
	return (0);
}
