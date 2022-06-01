/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:35:31 by chduong           #+#    #+#             */
/*   Updated: 2022/06/01 15:39:27 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_background(t_cube *s)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < LENGTH)
		{
			if (y < HEIGHT / 2)
				my_mlx_pixel_put(s, x, y, s->ceiling);
			else
				my_mlx_pixel_put(s, x, y, s->floor);
			++x;
		}
		++y;
	}
}

// void	draw_wall(t_cube *s)
// {
	
// }

void	draw_player_view(t_cube *s)
{
	draw_background(s);
}
