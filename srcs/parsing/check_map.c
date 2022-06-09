/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 06:43:35 by chduong           #+#    #+#             */
/*   Updated: 2022/06/09 23:35:46 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	one_or_space(char c)
{
	if (c == '1' || ft_isspace(c))
		return (0);
	return (1);
}

static int	around_space_ok(t_cube *s, int x, int y)
{
	int	res;

	res = 0;
	if (x > 0)
		res = res + one_or_space(s->maps[y][x - 1]);
	if (x < s->map.w - 1)
		res = res + one_or_space(s->maps[y][x + 1]);
	if (y > 0)
		res = res + one_or_space(s->maps[y - 1][x]);
	if (y < s->map.h - 1)
		res = res + one_or_space(s->maps[y + 1][x]);
	if (x > 0 && y > 0)
		res = res + one_or_space(s->maps[y - 1][x - 1]);
	if (x < s->map.w - 1 && y > 0)
		res = res + one_or_space(s->maps[y - 1][x + 1]);
	if (x > 0 && y < s->map.h - 1)
		res = res + one_or_space(s->maps[y + 1][x - 1]);
	if (x < s->map.w - 1 && y < s->map.h - 1)
		res = res + one_or_space(s->maps[y + 1][x + 1]);
	if (res > 0)
		return (0);
	return (1);
}

static int	check_space(t_cube *s)
{
	int	x;
	int	y;

	y = 0;
	while (s->maps[y])
	{
		x = 0;
		while (s->maps[y][x])
		{
			if (ft_isspace(s->maps[y][x]))
			{
				if (!around_space_ok(s, x, y))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

static int	check_tab_edge(t_cube *s)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (s->maps[y])
	{
		x = 0;
		while (s->maps[y][x])
		{
			if (y == 0)
				if (one_or_space(s->maps[y][x]))
					return (0);
			if (x == 0 || x == (s->map.w - 1))
				if (one_or_space(s->maps[y][x]))
					return (0);
			if (y == (s->map.h - 1))
				if (one_or_space(s->maps[y][x]))
					return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	check_map(t_cube *s)
{
	if (!valid_char(s))
		return (0);
	if (!check_space(s) || !check_tab_edge(s))
		return (write_error("All maps not surrounded by wall\n"));
	return (1);
}
