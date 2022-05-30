/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 12:59:37 by chduong           #+#    #+#             */
/*   Updated: 2022/05/30 13:00:05 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	is_valid_char(char c)
{
	if (c == ' ' || c == '1' || c == '0' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W')
		return (0);
	return (1);
}

int	valid_char(t_cube *s)
{
	int	x;
	int	y;
	int	sum;

	y = 0;
	sum = 0;
	while (s->map[y])
	{
		x = 0;
		while (s->map[y][x])
		{
			if (is_valid_char(s->map[y][x]))
				return (0);
			if (s->map[y][x] == 'N' || s->map[y][x] == 'S'
					|| s->map[y][x] == 'E' || s->map[y][x] == 'W')
				++sum;
			x++;
		}
		y++;
	}
	if (sum != 1)
		return (0);
	return (1);
}
