/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectdata.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:22:33 by jvermeer          #+#    #+#             */
/*   Updated: 2022/05/25 16:47:34 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	get_floor_ceiling(char *l, int tab[])
{
	while (*l && ft_isspace(*l))
		l++;
	tab[0] = ft_atoi(l);
	while (*l && ft_isspace(*l))
		l++;
	l = l + 1;
	tab[1] = ft_atoi(l);
	while (*l && ft_isspace(*l))
		l++;
	l = l + 1;
	tab[2] = ft_atoi(l);
}

static void	get_sprites(t_cube *s, char *l)
{
	if (buffcomp("NO", l))
		s->no = get_filename(l + 2);
	else if (buffcomp("SO", l))
		s->so = get_filename(l + 2);
	else if (buffcomp("WE", l))
		s->we = get_filename(l + 2);
	else if (buffcomp("EA", l))
		s->ea = get_filename(l + 2);
	else if (buffcomp("F", l))
		get_floor_ceiling(l + 2, s->floor);
	else if (buffcomp("C", l))
		get_floor_ceiling(l + 2, s->ceiling);
}

static int	fd_exist(char *file)
{
	int		fd;
	char	dir;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (1);
	if (read(fd, &dir, 0) == -1)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static int	sprites_exists(t_cube *s)
{
	if (fd_exist(s->no))
		return (1);
	if (fd_exist(s->so))
		return (1);
	if (fd_exist(s->we))
		return (1);
	if (fd_exist(s->ea))
		return (1);
	return (0);
}

int	data_collect(t_cube *s)
{
	int		i;
	int		j;
	int		numb;

	i = 0;
	numb = 0;
	s->mnm_pix = (int)(400 / s->map_len);
	if (s->map_len < s->map_height)
		s->mnm_pix = (int)(400 / s->map_height);
	while (s->file[i] && numb < 6)
	{
		j = 0;
		while (s->file[i][j] && ft_isspace(s->file[i][j]))
			j++;
		if (s->file[i][j])
			get_sprites(s, &s->file[i][j]);
		i++;
	}
	if (!s->no || !s->so || !s->we || !s->ea)
		return (write_error("malloc: memory allocation failed\n"));
	if (sprites_exists(s))
		return (write_error("sprite file(s) invalid\n"));
	return (1);
}
