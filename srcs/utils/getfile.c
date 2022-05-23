/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:24:06 by chduong           #+#    #+#             */
/*   Updated: 2022/05/23 14:24:50 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*get_file_name(char *l)
{
	char	*dest;
	int		i;

	i = 0;
	while (*l && *l == ' ')
		l++;
	dest = malloc(sizeof(char) * (ft_strlen(l) + 1));
	if (!dest)
		return (NULL);
	while (*l && *l != ' ')
	{
		dest[i] = *l;
		i++;
		l++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**get_all_file(t_cube *s, char **av, int *fd)
{
	char	**dest;
	char	*tmp;
	int		i;

	i = 0;
	s->nblines = 0;
	while (get_next_line(*fd, &tmp) > 0)
	{
		s->nblines = s->nblines + 1;
		free(tmp);
	}
	free(tmp);
	close(*fd);
	*fd = open(av[1], O_RDONLY);
	if (*fd == -1)
		return (NULL);
	dest = malloc(sizeof(char *) * (s->nblines + 1));
	if (!dest)
		return (NULL);
	while (get_next_line(*fd, &tmp) > 0)
		dest[i++] = tmp;
	free(tmp);
	dest[i] = NULL;
	return (dest);
}
