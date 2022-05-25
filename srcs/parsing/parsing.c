/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 10:40:24 by jvermeer          #+#    #+#             */
/*   Updated: 2022/05/25 16:43:56 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/******************** CHECK MAP UTILS **************************/
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

/******************** PARSING **************************/
static int	f_form(char *file, int fd)
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

static int	file_empty(char **av, int *fd)
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

static char	**get_file(char **av, int *fd)
{
	char			**dest;
	char			*tmp;
	int				i;
	unsigned int	n;

	i = 0;
	n = 0;
	while (get_next_line(*fd, &tmp) > 0)
	{
		++n;
		free(tmp);
	}
	close(*fd);
	*fd = open(av[1], O_RDONLY);
	if (*fd == -1)
		return (NULL);
	dest = malloc(sizeof(char *) * (n + 1));
	if (!dest)
		return (NULL);
	while (get_next_line(*fd, &tmp) > 0)
		dest[i++] = tmp;
	free(tmp);
	dest[i] = NULL;
	return (dest);
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
	s->file = get_file(av, &fd);
	if (!s->file)
		return (write_error("malloc: memory allocation failed\n"));
	close(fd);
	if (!check_elems(s))
		return (0);
	if (!check_map(s))
		return (0);
	return (1);
}
