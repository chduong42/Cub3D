/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elems.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 06:36:48 by chduong           #+#    #+#             */
/*   Updated: 2022/06/02 17:57:50 by chduong          ###   ########.fr       */
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

static int	all_elems(int *tab)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (tab[i] == 0)
			return (0);
		i++;
	}
	return (1);
}


int	check_elems(t_cube *s)
{
	int		tab[6];
	int		count;
	int		i;
	int		j;

	ft_bzero(tab, sizeof(tab));
	count = 0;
	i = 0;
	while (s->file[i] && count < 6)
	{
		j = 0;
		while (s->file[i][j] && ft_isspace(s->file[i][j]))
			j++;
		if (s->file[i][j] && !check_each_elem(&s->file[i][j], tab, &count))
			return (write_error("invalid element(s)\n"));
		i++;
	}
	if (!create_map(s, i))
		return (0);
	if (!all_elems(tab))
		return (write_error("missing element(s)\n"));
	return (1);
}
