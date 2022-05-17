/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 13:55:22 by chduong           #+#    #+#             */
/*   Updated: 2022/05/17 16:16:56 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_window(t_data *data, t_xy map)
{
	t_xy	res;

	printf("\e[1;37m--> Window Launching !\e[0m");
	res.x = map.x * PIX;
	res.y = map.y * PIX;
	data->win = mlx_new_window(data->mlx, res.x, res.y, TITLE);
	check_ptr(data->win, data);
	printf("\t🚀\n");
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		printf("\e[1;37mUsage :\e[0m %s <file.cub>\n", av[0]);
	else
	{
		create_window(&data, data.map.dim);
		mlx_loop_hook(data.mlx, &handle_display, &data);
		mlx_hook(data.win, KeyPress, KeyPressMask, &handle_keypress, &data);
		mlx_hook(data.win, ClientMessage, LeaveWindowMask, &cross_btn, &data);
		display_map(&data);
		mlx_loop(data.mlx);
	}
	return (0);
}
