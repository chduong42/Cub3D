/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 10:40:24 by jvermeer          #+#    #+#             */
/*   Updated: 2022/06/06 17:09:58 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	tmp = NULL;
	while (get_next_line(*fd, &tmp) > 0)
		++n;
	free(tmp);
	tmp = NULL;
	close(*fd);
	*fd = open(av[1], O_RDONLY);
	if (*fd == -1)
		return (NULL);
	dest = malloc(sizeof(char *) * (n + 1));
	if (!dest)
		return (NULL);
	while (get_next_line(*fd, &tmp) > 0)
		dest[i++] = ft_strdup(tmp);
	free(tmp);
	dest[i] = NULL;
	return (dest);
}

int	parsing(t_cube *s, int ac, char **av)
{
	int	fd;

	if (ac != 2)
		return (write_error("Usage: ./cub3D file.cub\n"));
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (write_error("Can't open file\n"));
	if (!f_form(av[1], fd) || !file_empty(av, &fd))
		return (write_error("Wrong file format or file empty\n"));
	s->file = get_file(av, &fd);
	if (!s->file)
		return (write_error("Malloc: memory allocation failed\n"));
	close(fd);
	if (!check_elems(s))
		return (0);
	if (!check_map(s))
		return (0);
	get_player_position(s);
	return (1);
}
