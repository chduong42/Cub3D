/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 18:02:16 by chduong           #+#    #+#             */
/*   Updated: 2022/05/16 18:02:31 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_file(t_data *data, const char *path_file)
{
	size_t	len;
	char	*ext;

	printf("\e[1;33mChecking map file...\e[0m");
	len = ft_strlen(path_file);
	if (len < 4)
		print_error(data, "No \".ber\" extension");
	ext = ft_strnstr(path_file, ".ber", len);
	len = ft_strlen(ext);
	if (len == 0 || len > 4)
		print_error(data, "No \".ber\" extension");
	if (open(path_file, __O_DIRECTORY) > 0)
		print_error(data, "Input is a directory, not a file.ber");
	printf("\t✅\n");
	return (0);
}

static t_dim	dim_map(const char *path_file)
{
	int		fd;
	char	*line;
	t_dim	dim;

	fd = open(path_file, O_RDONLY);
	line = NULL;
	dim.y = 0;
	while (get_next_line(fd, &line))
	{
		dim.x = ft_strlen(line);
		++dim.y;
	}	
	free(line);
	close(fd);
	return (dim);
}

void	free_map(char **map, int y)
{
	int	i;

	i = 0;
	while (i < y)
		free(map[i++]);
	free(map);
	map = NULL;
}

static char	**malloc_map(t_data *data, t_dim dim)
{
	int		i;
	char	**map;

	map = malloc(sizeof(char **) * (dim.y + 1));
	check_ptr(map, data);
	i = 0;
	while (i < dim.y)
	{
		map[i] = malloc(sizeof(char *) * (dim.x + 1));
		if (map[i] == NULL)
		{
			free_map(map, i);
			print_error(data, "Fail malloc map");
		}
		++i;
	}
	map[i] = NULL;
	return (map);
}

void	get_map(t_data *data, const char *path_file)
{
	int		i;
	int		fd;
	char	*line;
	t_map	*map;

	map = &data->map;
	check_file(data, path_file);
	printf("\e[1;33mParsing the map...\e[0m");
	map->dim = dim_map(path_file);
	map->tab = malloc_map(data, map->dim);
	i = 0;
	line = NULL;
	fd = open(path_file, O_RDONLY);
	while (get_next_line(fd, &line))
		ft_strlcpy(map->tab[i++], line, map->dim.x + 1);
	close(fd);
	free(line);
	check_map(data);
	printf("\t✅\n");
}