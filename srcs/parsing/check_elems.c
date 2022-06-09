/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elems.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 06:36:48 by chduong           #+#    #+#             */
/*   Updated: 2022/06/09 23:35:36 by chduong          ###   ########.fr       */
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
	int	nb_player;

	y = 0;
	nb_player = 0;
	while (s->maps[y])
	{
		x = 0;
		while (s->maps[y][x])
		{
			if (is_valid_char(s->maps[y][x]))
				return (write_error("Invalid character(s) in the maps\n"));
			if (s->maps[y][x] == 'N' || s->maps[y][x] == 'S'
					|| s->maps[y][x] == 'E' || s->maps[y][x] == 'W')
				++nb_player;
			x++;
		}
		y++;
	}
	if (nb_player != 1)
		return (write_error("Missing or too many players in the maps\n"));
	return (1);
}

static int	all_elems(int *tab)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (tab[i] > 1)
			return (write_error("One or several elements appear twice\n"));
		else if (tab[i] == 0)
			return (write_error("Missing element(s)\n"));
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
			return (write_error("Input file start with invalid element(s)\n"));
		i++;
	}
	if (!create_map(s, i) || !all_elems(tab))
		return (0);
	return (1);
}
