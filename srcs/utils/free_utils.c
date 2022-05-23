/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:00:27 by jvermeer          #+#    #+#             */
/*   Updated: 2022/05/23 14:24:33 by chduong          ###   ########.fr       */
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

void	free_world(t_cube *s)
{
	if (s->image)
		mlx_destroy_image(s->cube_ptr, s->image);
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
	free_world(s);
}

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
