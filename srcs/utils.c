/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:57:55 by chduong           #+#    #+#             */
/*   Updated: 2022/05/17 16:28:56 by chduong          ###   ########.fr       */
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
