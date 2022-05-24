/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:00:27 by jvermeer          #+#    #+#             */
/*   Updated: 2022/05/24 18:03:17 by chduong          ###   ########.fr       */
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
		++tmp;
	}
	free(str);
}

void	free_world(t_cube *s)
{
	if (s->img)
		mlx_destroy_image(s->mlx, s->img);
	if (s->win)
		mlx_destroy_window(s->mlx, s->win);
	if (s->mlx)
	{
		mlx_destroy_display(s->mlx);
		free(s->mlx);
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
	if (s->file)
		free_array(s->file);
	if (s->map)
		free_array(s->map);
	free_world(s);
}

int	write_error(char *message)
{
	int	i;

	i = 0;
	write(2, "Error\n", 6);
	while (message[i])
		write(2, &message[i++], 1);
	return (0);
}
