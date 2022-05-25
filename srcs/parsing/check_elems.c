/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elems.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 06:36:48 by chduong           #+#    #+#             */
/*   Updated: 2022/05/25 15:55:51 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

static int	is_elem(char *l)
{
	if (buffcomp("NO", l) || buffcomp("SO", l) || buffcomp("WE", l)
		|| buffcomp("EA", l) || buffcomp("F", l) || buffcomp("C", l))
		return (1);
	return (0);
}

static int	help_check_elem(char *ptr, int tab[], int *numb)
{
	if (!is_elem(ptr))
		return (1);
	if (!check_each_elem(ptr, tab))
		return (1);
	(*numb)++;
	return (0);
}

int	check_elems(t_cube *s)
{
	int		tab[6];
	int		numb;
	int		i;
	int		j;

	ft_bzero(tab, sizeof(tab));
	numb = 0;
	i = 0;
	while (s->file[i] && numb < 6)
	{
		j = 0;
		while (s->file[i][j] && ft_isspace(s->file[i][j]))
			j++;
		if (s->file[i][j])
			if (help_check_elem(&s->file[i][j], tab, &numb))
				return (write_error("invalid element(s)\n"));
		i++;
	}
	if (!create_map(s, i))
		return (0);
	if (all_elems(tab))
		return (1);
	return (0);
}
