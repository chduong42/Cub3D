/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectdata.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:22:33 by jvermeer          #+#    #+#             */
/*   Updated: 2022/06/01 17:41:49 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	get_rgb(char *l)
{
	char	**rgb;
	int		tab[3];

	rgb = ft_split(l, ',');
	tab[0] = ft_atoi(rgb[0]);
	tab[1] = ft_atoi(rgb[1]);
	tab[2] = ft_atoi(rgb[2]);
	free_array(rgb);
	return (create_trgb(0, tab[0], tab[1], tab[2]));
}

static void	get_sprites(t_cube *s, char *l)
{
	if (buffcomp("NO", l))
		s->no = get_fn(l + 2);
		// s->no = mlx_xpm_file_to_image(s->mlx, get_fn(l + 2), &s->w, &s->h);
	else if (buffcomp("SO", l))
		s->so = get_fn(l + 2);
		// s->so = mlx_xpm_file_to_image(s->mlx, get_fn(l + 2), &s->w, &s->h);
	else if (buffcomp("WE", l))
		s->we = get_fn(l + 2);
		// s->we = mlx_xpm_file_to_image(s->mlx, get_fn(l + 2), &s->w, &s->h);
	else if (buffcomp("EA", l))
		s->ea = get_fn(l + 2);
		// s->ea = mlx_xpm_file_to_image(s->mlx, get_fn(l + 2), &s->w, &s->h);
	else if (buffcomp("F", l))
		s->floor = get_rgb(l + 1);
	else if (buffcomp("C", l))
		s->ceiling = get_rgb(l + 1);
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
