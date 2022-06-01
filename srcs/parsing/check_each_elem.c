/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_each_elem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 06:40:21 by chduong           #+#    #+#             */
/*   Updated: 2022/06/01 16:05:22 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	buffcomp(char *str, char *l)
{
	while (*l && *str && *str == *l)
	{
		str++;
		l++;
	}
	if (*l && *str == '\0' && ft_isspace(*l))
		return (1);
	return (0);
}

static int	check_color(char **l)
{
	int	color;

	color = ft_atoi(*l);
	while (**l && ft_isspace(**l))
		(*l)++;
	if (!ft_isdigit(**l))
		return (0);
	while (**l && ft_isdigit(**l))
		(*l)++;
	if (color < 0 || color > 255)
		return (0);
	return (1);
}

static int	color_line(char *l)
{
	++l;
	if (!check_color(&l) || *l != ',')
		return (0);
	++l;
	if (!check_color(&l) || *l != ',')
		return (0);
	++l;
	if (!check_color(&l) || *l)
		return (0);
	return (1);
}

static int	direction_line(char *l)
{
	char	*filename;

	l = l + 2;
	while (*l && ft_isspace(*l))
		l++;
	filename = get_filename(l);
	if (!filename)
		return (0);
	while (*l && !ft_isspace(*l))
		l++;
	while (*l && ft_isspace(*l))
		l++;
	if (*l)
	{
		free(filename);
		return (0);
	}
	free(filename);
	return (1);
}

int	check_each_elem(char *l, int *tab)
{
	int	count;

	count = 0;
	if (buffcomp("NO", l) || buffcomp("SO", l)
		|| buffcomp("WE", l) || buffcomp("EA", l))
	{
		if (buffcomp("NO", l))
			tab[0] = 1;
		else if (buffcomp("SO", l))
			tab[1] = 1;
		else if (buffcomp("WE", l))
			tab[2] = 1;
		else if (buffcomp("EA", l))
			tab[3] = 1;
		if (!direction_line(l))
			return (0);
	}
	else
	{
		if (buffcomp("F", l))
			tab[4] = 1;
		else if (buffcomp("C", l))
			tab[5] = 1;
		if (!color_line(l))
			return (0);
	}
	return (1);
}
