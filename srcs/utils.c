/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:57:55 by chduong           #+#    #+#             */
/*   Updated: 2022/05/16 17:59:33 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	deg_to_rad(double degrees)
{
	return (degrees * (M_PI / 180.0));
}

double	rad_to_deg(double radians)
{
	return (radians * (180.0 / M_PI));
}

void	data_init(t_data *data)
{
	printf("\e[1;33mData Initialization...\e[0m");
	data->width = 0;
	data->height = 0;
	data->win = NULL;
	data->mlx = mlx_init();
	check_ptr(data->mlx, data);
	printf("\t✅\n");
}

void	clear_data(t_data *data)
{
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	if (data->map.tab)
		free_map(data->map.tab, data->map.dim.y);
	exit(EXIT_SUCCESS);
}
