/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:31:12 by chduong           #+#    #+#             */
/*   Updated: 2022/05/13 17:05:32 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	erase_oldplayer(char player, t_dim loc, char **map)
{
	if (map[loc.y][loc.x] == player)
		map[loc.y][loc.x] = '0';
}

int	go_up_down(int dir, t_data *data)
{
	t_dim	p;
	char	**map;
	int		count;

	count = 0;
	p = data->map.ploc;
	map = data->map.tab;
	if (map[p.y + dir][p.x] == '0' || map[p.y + dir][p.x] == 'C')
	{
		if (map[p.y + dir][p.x] == 'C')
			data->map.collect -= 1;
		map[p.y + dir][p.x] = 'P';
		++count;
	}
	else if (map[p.y + dir][p.x] == 'E')
	{
		map[p.y + dir][p.x] = '2';
		++count;
	}
	if (count > 0)
		erase_oldplayer('P', p, map);
	return (count);
}

int	go_left_right(int dir, t_data *data)
{
	t_dim	p;
	char	**map;
	int		count;

	count = 0;
	p = data->map.ploc;
	map = data->map.tab;
	if (map[p.y][p.x + dir] == '0' || map[p.y][p.x + dir] == 'C')
	{
		if (map[p.y][p.x + dir] == 'C')
			data->map.collect -= 1;
		map[p.y][p.x + dir] = 'P';
		++count;
	}
	else if (map[p.y][p.x + dir] == 'E')
	{
		map[p.y][p.x + dir] = '2';
		++count;
	}
	if (count > 0)
		erase_oldplayer('P', p, map);
	return (count);
}