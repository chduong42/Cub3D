/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 17:06:21 by chduong           #+#    #+#             */
/*   Updated: 2022/05/16 18:42:19 by chduong          ###   ########.fr       */
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

	else if (keysym == S)

	else if (keysym == A)

	else if (keysym == D)

	else if (keysym == ARROW_UP)

	else if (keysym == ARROW_DOWN)

	else if (keysym == ARROW_LEFT)

	else if (keysym == ARROW_RIGHT)

	display_map(data);
	return (0);
}

int	cross_btn(t_data *data)
{
	clear_data(data);
	return (0);
}
