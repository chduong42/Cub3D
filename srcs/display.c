/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 18:00:17 by chduong           #+#    #+#             */
/*   Updated: 2022/05/16 18:00:33 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	display_map(t_data *data)
{
	int		i;
	int		j;
	char	**map;

	map = data->map.tab;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			parse_display(data, j++, i);
		++i;
	}
	display_counter(data);
}
