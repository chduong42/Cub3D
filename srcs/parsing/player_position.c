/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:09:55 by chduong           #+#    #+#             */
/*   Updated: 2022/06/09 15:54:34 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	get_pov(t_cube *s, char loc)
{
	if (loc == 'N')
		s->pov = 90;
	else if (loc == 'S')
		s->pov = 270;
	else if (loc == 'E')
		s->pov = 0;
	else if (loc == 'W')
		s->pov = 180;
}

void	get_player_position(t_cube *s)
{
	int		x;
	int		y;

	y = 0;
	while (y < s->map.h)
	{
		x = 0;
		while (x < s->map.w)
		{
			if (s->maps[y][x] == 'N' || s->maps[y][x] == 'S'
				|| s->maps[y][x] == 'E' || s->maps[y][x] == 'W')
			{
				get_pov(s, s->maps[y][x]);
				s->pos.x = (float)x + 0.5;
				s->pos.y = (float)y + 0.5;
				return ;
			}
			x++;
		}
		y++;
	}
}
