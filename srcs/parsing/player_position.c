/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 15:09:55 by chduong           #+#    #+#             */
/*   Updated: 2022/05/30 13:09:16 by chduong          ###   ########.fr       */
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
	while (y < s->map_h)
	{
		x = 0;
		while (x < s->map_l)
		{
			if (s->map[y][x] == 'N' || s->map[y][x] == 'S'
				|| s->map[y][x] == 'E' || s->map[y][x] == 'W')
			{
				get_pov(s, s->map[y][x]);
				s->pos[0] = (float)x + 0.5;
				s->pos[1] = (float)y + 0.5;
				return ;
			}
			x++;
		}
		y++;
	}
}
