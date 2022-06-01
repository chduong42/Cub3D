/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnextline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 10:37:49 by jvermeer          #+#    #+#             */
/*   Updated: 2022/05/31 10:33:13 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	help_realloc(char **line, int old_size, int size)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = *line;
	*line = malloc(sizeof(char) * size);
	if (!(*line))
	{
		free(tmp);
		tmp = NULL;
		return (0);
	}
	while (i < old_size)
	{
		line[0][i] = tmp[i];
		i++;
	}
	free(tmp);
	return (1);
}

int	how_long_malloc(char **ptr_buff, int counter)
{
	int	i;

	i = 0;
	while (i < counter)
	{
		if (ptr_buff[0][i] == '\n')
			return (i);
		i++;
	}
	return (counter);
}

int	manage_malloc(char **line, int counter, t_gnl *s, char **ptr_buff)
{
	int	old_size;

	old_size = s->size;
	s->size = s->size + how_long_malloc(ptr_buff, counter);
	if (s->bean == 1)
	{
		s->size++;
		*line = malloc(sizeof(char) * s->size);
		if (!(*line))
			return (0);
	}
	else if (s->bean == 2)
	{
		if (!(help_realloc(line, old_size, s->size)))
			return (0);
	}
	s->bean = 0;
	return (1);
}

int	read_n_getchar(int fd, char **line, t_gnl *s)
{
	static int	counter = 0;
	static char	buff[10];
	static char	*ptr_buff;

	if (counter == 0)
	{
		counter = read(fd, buff, 10);
		if (counter == 0)
		{
			if (!(manage_malloc(line, 0, s, &ptr_buff)))
				return (-1);
			return (0);
		}
		if (counter == -1)
			return (-1);
		ptr_buff = buff;
	}
	if (s->bean == 1 || s->bean == 2)
		if (!(manage_malloc(line, (int)counter, s, &ptr_buff)))
			return (-1);
	s->c = *ptr_buff++;
	if (--counter == 0)
		s->bean = 2;
	return (1);
}

int	get_next_line(int fd, char **line)
{
	int		i;
	t_gnl	s;

	i = 0;
	s.bean = 1;
	s.size = 0;
	if (!(line) || fd < 0)
		return (-1);
	s.ret = read_n_getchar(fd, line, &s);
	while (s.ret && s.c != '\n')
	{
		if (s.ret == -1)
			return (-1);
		line[0][i] = s.c;
		i++;
		s.ret = read_n_getchar(fd, line, &s);
	}
	line[0][i] = '\0';
	if (s.ret == 0 && **line == '\0')
		return (0);
	return (1);
}
