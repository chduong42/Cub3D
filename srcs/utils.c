/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:00:27 by jvermeer          #+#    #+#             */
/*   Updated: 2022/05/18 16:31:57 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_array(char **str)
{
	char	**tmp;

	tmp = str;
	while (tmp && *tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(str);
}

void	free_minimap(t_cube *s)
{
	if (s->minip)
		mlx_destroy_image(s->cube_ptr, s->minip);
	if (s->minig)
		mlx_destroy_image(s->cube_ptr, s->minig);
	if (s->miniw)
		mlx_destroy_image(s->cube_ptr, s->miniw);
//	if (s->image)
//		mlx_destroy_image(s->cube_ptr, s->image);
	if (s->cube_win)
		mlx_destroy_window(s->cube_ptr, s->cube_win);
	if (s->cube_ptr)
	{
		mlx_destroy_display(s->cube_ptr);
		free(s->cube_ptr);
	}
}

void	free_all(t_cube *s)
{
	if (s->no)
		free(s->no);
	if (s->so)
		free(s->so);
	if (s->we)
		free(s->we);
	if (s->ea)
		free(s->ea);
	free_array(s->file);
	free_array(s->map);
	free_minimap(s);
}
/*
int	free_and_leave(t_stru *sl)
{
	if (sl->one)
		mlx_destroy_image(sl->m_ptr, sl->one);
	if (sl->zero)
		mlx_destroy_image(sl->m_ptr, sl->zero);
	if (sl->collec)
		mlx_destroy_image(sl->m_ptr, sl->collec);
	if (sl->exit)
		mlx_destroy_image(sl->m_ptr, sl->exit);
	while (i < 4)
		if (sl->player[i])
			mlx_destroy_image(sl->m_ptr, sl->player[i++]);
	mlx_destroy_window(sl->m_ptr, sl->w_ptr);
	mlx_destroy_display(sl->m_ptr);
	free(sl->m_ptr);
}
*/
int	write_error(char *message)
{
	int	i;

	i = 0;
	write(2, "Error\n", 6);
	while (message[i])
	{
		write(2, &message[i], 1);
		i++;
	}
	return (0);
}

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
