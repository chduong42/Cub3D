/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 10:40:24 by jvermeer          #+#    #+#             */
/*   Updated: 2022/05/18 16:18:57 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

///////////////////////////////////// CHECK EACH ELEM

int	check_color(char **l)
{
	int	color;

	color = ft_atoi(*l);
	while (**l && **l == ' ')
		(*l)++;
	if (!ft_isdigit(**l))
		return (0);
	while (**l && ft_isdigit(**l))
		(*l)++;
	while (**l && **l == ' ')
		(*l)++;
	if (color < 0 || color > 255)
		return (0);
	return (1);
}

int	color_line(char *l)
{
	l++;
	if (!check_color(&l) || *l != ',')
		return (0);
	l++;
	if (!check_color(&l) || *l != ',')
		return (0);
	l++;
	if (!check_color(&l) || *l)
		return (0);
	return (1);
}

int	buffcomp(char *str, char *l)
{
	while (*l && *str && *str == *l)
	{
		str++;
		l++;
	}
	if (*l && *str == '\0' && *l == ' ')
		return (1);
	return (0);
}

int	direction_line(char *l)
{
	char	*filename;

	l = l + 2;
	while (*l && *l == ' ')
		l++;
	filename = get_file_name(l);
	if (!filename)
		return (0);
	while (*l && *l != ' ')
		l++;
	while (*l && *l == ' ')
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

/////////////////////////////////////////// CREATE MAP

int	is_empty(char *l)
{
	while (*l && *l == ' ')
		l++;
	if (*l)
		return (0);
	return (1);
}

int	what_len_max(t_cube *s, int i)
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

int	hm_lines(t_cube *s, int i)
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

char	*dup_with_space(const char *str, int lenmax)
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
	s->maplen = what_len_max(s, i);
	s->mapwid = hm_lines(s, i);
	s->map = malloc(sizeof(char *) * (s->mapwid + 1));
	if (!s->map)
		return (write_error("malloc: memory allocation failed\n"));
	while (y < s->mapwid)
	{
		s->map[y] = dup_with_space(s->file[i++], s->maplen);
		if (!s->map[y])
			return (write_error("malloc: memory allocation failed\n"));
		y++;
	}
	s->map[y] = NULL;
	return (1);
}

//////////////////////////////////////////////// CHECK ELEMS

void	initializetab(int *tab)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		tab[i] = 0;
		i++;
	}
}

int	all_elems(int *tab)
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

int	is_elem(char *l)
{
	if (buffcomp("NO", l) || buffcomp("SO", l) || buffcomp("WE", l)
		|| buffcomp("EA", l) || buffcomp("F", l) || buffcomp("C", l))
		return (1);
	return (0);
}

int	help_check_elem(char *ptr, int tab[], int *numb)
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

	initializetab(tab);
	numb = 0;
	i = 0;
	while (s->file[i] && numb < 6)
	{
		j = 0;
		while (s->file[i][j] && s->file[i][j] == ' ')
			j++;
		if (s->file[i][j])
			if (help_check_elem(&s->file[i][j], tab, &numb))
				return (write_error("invalid element(s)\n"));
		i++;
	}
	if (!create_map(s, i))
		return (write_error("malloc: memory allocation failed\n"));
	if (all_elems(tab))
		return (1);
	return (0);
}

////////////////////////////////////////////   CHECK MAP

/*
int	check_lines(t_cube *s)
{
	int	diver;
	int	x;
	int	y;

	y = 0;
	diver = 1;
	while (s->map[y])
	{
		x = 0;
		while (s->map[y][x])
		{
			if (diver == 1 && s->map[y][x] == '1' && s->map[y][x + 1]
				&& s->map[y][x + 1] != ' ' && s->map[y][x + 1] !='1')
				diver = -diver;
			if (diver == -1 && s->map[y][x] == '1' && s->map[y][x + 1] && s->map[y][x + 1] == ' ')
				diver = -diver;
			else if (diver == -1 && s->map[y][x] == '1' && s->map[y][x + 1] == '\0')
				diver = -diver;
			x++;
		}
		if (diver == -1)
			return (0);
		y++;
	}
	return (1);
}
*/

int	one_or_space(char c)
{
	if (c == '1' || c == ' ')
		return (0);
	return (1);
}

int	around_space_ok(t_cube *s, int x, int y)
{
	int	res;

	res = 0;
	if (x > 0)
		res = res + one_or_space(s->map[y][x - 1]);
	if (x < s->maplen - 1)
		res = res + one_or_space(s->map[y][x + 1]);
	if (y > 0)
		res = res + one_or_space(s->map[y - 1][x]);
	if (y < s->mapwid - 1)
		res = res + one_or_space(s->map[y + 1][x]);
	// Diags:
	if (x > 0 && y > 0)
		res = res + one_or_space(s->map[y - 1][x - 1]);
	if (x < s->maplen - 1 && y > 0)
		res = res + one_or_space(s->map[y - 1][x + 1]);
	if (x > 0 && y < s->mapwid - 1)
		res = res + one_or_space(s->map[y + 1][x - 1]);
	if (x < s->maplen - 1 && y < s->mapwid - 1)
		res = res + one_or_space(s->map[y + 1][x + 1]);
	if (res > 0)
		return (0);
	return (1);
}

int	check_space(t_cube *s)
{
	int	x;
	int	y;

	y = 0;
	while (s->map[y])
	{
		x = 0;
		while (s->map[y][x])
		{
			if (s->map[y][x] == ' ')
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

int	check_tab_edge(t_cube *s)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (s->map[y])
	{
		x = 0;
		while (s->map[y][x])
		{
			if (y == 0)
				if (one_or_space(s->map[y][x]))
					return (0);
			if (x == 0 || x == (s->maplen - 1))
				if (one_or_space(s->map[y][x]))
					return (0);
			if (y == (s->mapwid - 1))
				if (one_or_space(s->map[y][x]))
					return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	is_valid_char(char c)
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

int	check_map(t_cube *s)
{
	if (!valid_char(s))
		return (write_error("invalid character in the map\n"));
	if (!check_space(s))
		return (write_error("all map not surrounded by wall\n"));
//	if (!check_lines(s))
//		return (write_error("all map not surrounded by wall\n"));
	if (!check_tab_edge(s))
		return (write_error("all map not surrounded by wall\n"));
	return (1);
}

//////////////////////////////////////// Parsing

int	f_form(char *file, int fd)
{
	int		n;
	char	dir;

	n = 0;
	if (read(fd, &dir, 0) == -1)
		return (0);
	while (file[n])
		n++;
	if (file[--n] == 'b' && file[--n] == 'u'
		&& file[--n] == 'c' && file[--n] == '.')
		return (1);
	return (0);
}

int	file_empty(char **av, int *fd)
{
	int		ret;
	char	tmp[1];

	ret = read(*fd, tmp, 1);
	if (ret == -1 || ret == 0)
		return (0);
	close(*fd);
	*fd = open(av[1], O_RDONLY);
	if (*fd == -1)
		return (0);
	return (1);
}

int	parsing(t_cube *s, int ac, char **av)
{
	int	fd;

	if (ac != 2)
		return (write_error("usage: ./cub3D file.cub\n"));
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (write_error("file don't exist or you don't have permission\n"));
	if (!f_form(av[1], fd) || !file_empty(av, &fd))
		return (write_error("wrong file format or file empty\n"));
	s->file = get_all_file(s, av, &fd);
	if (!s->file)
		return (write_error("malloc: memory allocation failed\n"));
	close(fd);
	if (!check_elems(s))
		return (0);
	if (!check_map(s))
		return (0);
	return (1);
}
