/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 23:44:44 by chduong           #+#    #+#             */
/*   Updated: 2022/05/30 13:09:16 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	is_empty(char *l)
{
	while (*l && *l == ' ')
		l++;
	if (*l)
		return (0);
	return (1);
}

static int	what_len_max(t_cube *s, int i)
{
	int	lenmax;
	int	lentemp;

	lenmax = 0;
	while (s->file[i])
	{
		lentemp = ft_strlen(s->file[i]);
		if (lentemp > lenmax)
			lenmax = lentemp;
		i++;
	}
	return (lenmax);
}

static int	hm_lines(t_cube *s, int i)
{
	int	j;

	j = 0;
	while (s->file[i])
	{
		j++;
		i++;
	}
	return (j);
}

static char	*dup_with_space(const char *str, int lenmax)
{
	char	*dest;
	int		x;

	x = 0;
	dest = malloc(sizeof(char) * lenmax + 1);
	if (!dest)
		return (NULL);
	while (str[x])
	{
		dest[x] = str[x];
		x++;
	}
	while (x < lenmax)
		dest[x++] = ' ';
	dest[x] = '\0';
	return (dest);
}

int	create_map(t_cube *s, int i)
{
	int	y;

	y = 0;
	while (s->file[i] && is_empty(s->file[i]))
		i++;
	s->map_l = what_len_max(s, i);
	s->map_h = hm_lines(s, i);
	if (s->map_l > 50 || s->map_h > 50)
		return (write_error("maximum map size : 50x50\n"));
	s->map = malloc(sizeof(char *) * (s->map_h + 1));
	if (!s->map)
		return (write_error("malloc: memory allocation failed\n"));
	while (y < s->map_h)
	{
		s->map[y] = dup_with_space(s->file[i++], s->map_l);
		if (!s->map[y])
			return (write_error("malloc: memory allocation failed\n"));
		y++;
	}
	s->map[y] = NULL;
	return (1);
}
