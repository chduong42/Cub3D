/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 17:06:21 by chduong           #+#    #+#             */
/*   Updated: 2022/05/13 17:06:59 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_display(t_data *data)
{
	t_dim	loc;
	char	**player;

	loc = data->map.ploc;
	player = data->map.tab;
	if (player[loc.y][loc.x] == '2' && data->map.collect == 0)
		clear_data(data);
	return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		clear_data(data);
	else if (keysym == W)
		data->map.ploc.y -= go_up_down(UP, data);
	else if (keysym == S)
		data->map.ploc.y += go_up_down(DOWN, data);
	else if (keysym == A)
		data->map.ploc.x -= go_left_right(LEFT, data);
	else if (keysym == D)
		data->map.ploc.x += go_left_right(RIGHT, data);
	display_map(data);
	return (0);
}

int	cross_btn(t_data *data)
{
	clear_data(data);
	return (0);
}