/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 13:55:22 by chduong           #+#    #+#             */
/*   Updated: 2022/05/13 16:42:37 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_window(t_data *data, t_dim map)
{
	t_dim	res;

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
		printf("\e[1;37musage :\e[0m %s <mapfile.ber>\n", av[0]);
	else
	{
		data_init(&data);
		get_map(&data, av[1]);
		load_img(&data);
		create_window(&data, data.map.dim);
		mlx_loop_hook(data.mlx, &handle_display, &data);
		mlx_hook(data.win, KeyPress, KeyPressMask, &handle_keypress, &data);
		mlx_hook(data.win, ClientMessage, LeaveWindowMask, &cross_btn, &data);
		printf("\e[1;32mReady Player 1 :\t🐱\n\e[0m");
		printf("\e[1;32mReady Player 2 :\t🐭\n\e[0m");
		printf("============= 🐱 RUN BABY RUN 🐭 =============== \n");
		display_map(&data);
		mlx_loop(data.mlx);
	}
	return (0);
}