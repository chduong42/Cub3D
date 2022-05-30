/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectdata.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:22:33 by jvermeer          #+#    #+#             */
/*   Updated: 2022/05/30 16:44:39 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	get_rgb(char *l, int tab[])
{
	char	**rgb;

	rgb = ft_split(l, ',');
	tab[0] = ft_atoi(rgb[0]);
	tab[1] = ft_atoi(rgb[1]);
	tab[2] = ft_atoi(rgb[2]);
	free_array(rgb);
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
		get_rgb(l + 1, s->floor);
	else if (buffcomp("C", l))
		get_rgb(l + 1, s->ceiling);
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
	s->mnm_pix = (int)(400 / s->map_l);
	if (s->map_l < s->map_h)
		s->mnm_pix = (int)(400 / s->map_h);
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
		return (write_error("input data missing\n"));
	if (sprites_exists(s))
		return (write_error("sprite file(s) invalid\n"));
	return (1);
}
