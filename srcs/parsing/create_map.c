/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 23:44:44 by chduong           #+#    #+#             */
/*   Updated: 2022/06/09 15:54:34 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	is_empty(char *l)
{
	while (*l && ft_isspace(*l))
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
	s->map.w = what_len_max(s, i);
	s->map.h = hm_lines(s, i);
	if (!s->map.h)
		return (write_error("No maps\n"));
	if (s->map.w > 50 || s->map.h > 50)
		return (write_error("Maximum maps size : 50x50\n"));
	s->maps = malloc(sizeof(char *) * (s->map.h + 1));
	if (!s->maps)
		return (write_error("Malloc: memory allocation failed\n"));
	while (y < s->map.h)
	{
		s->maps[y] = dup_with_space(s->file[i++], s->map.w);
		if (!s->maps[y])
			return (write_error("Malloc: memory allocation failed\n"));
		y++;
	}
	s->maps[y] = NULL;
	return (1);
}
