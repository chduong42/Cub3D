/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_each_elem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 06:40:21 by chduong           #+#    #+#             */
/*   Updated: 2022/06/06 16:52:33 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	cmp(char *str, char *l)
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

static int	check_rgb(char **l)
{
	int	color;

	color = ft_atoi(*l);
	while (**l && ft_isspace(**l))
		(*l)++;
	if (!ft_isdigit(**l))
		return (0);
	while (**l && ft_isdigit(**l))
		(*l)++;
	while (**l && ft_isspace(**l))
		(*l)++;
	if (color < 0 || color > 255)
		return (0);
	return (1);
}

static int	isrgb_line(char *l)
{
	l++;
	if (!check_rgb(&l) || *l != ',')
		return (0);
	l++;
	if (!check_rgb(&l) || *l != ',')
		return (0);
	l++;
	if (!check_rgb(&l) || *l)
		return (0);
	return (1);
}

static int	ispath_line(char *l)
{
	l = l + 2;
	while (*l && ft_isspace(*l))
		l++;
	while (*l && !ft_isspace(*l))
		l++;
	while (*l && ft_isspace(*l))
		l++;
	if (*l)
		return (0);
	return (1);
}

int	check_each_elem(char *l, int *tab, int *count)
{
	*count += 1;
	if (cmp("NO", l) || cmp("SO", l) || cmp("WE", l) || cmp("EA", l))
	{
		if (cmp("NO", l))
			tab[0] += 1;
		else if (cmp("SO", l))
			tab[1] += 1;
		else if (cmp("WE", l))
			tab[2] += 1;
		else if (cmp("EA", l))
			tab[3] += 1;
		if (!ispath_line(l))
			return (0);
	}
	else
	{
		if (cmp("F", l))
			tab[4] += 1;
		else if (cmp("C", l))
			tab[5] += 1;
		if (!isrgb_line(l))
			return (0);
	}
	return (1);
}
