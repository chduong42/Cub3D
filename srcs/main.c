/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 08:58:22 by jvermeer          #+#    #+#             */
/*   Updated: 2022/05/30 15:44:50 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

int	main(int ac, char **av)
{
	t_cube	s;

	ft_memset(&s, 0, sizeof(t_cube));
	if (!parsing(&s, ac, av) || !data_collect(&s))
	{
		free_all(&s);
		return (1);
	}
	s.mlx = mlx_init();
	s.win = mlx_new_window(s.mlx, LENGTH, HEIGHT, TITLE);
	s.img = mlx_new_image(s.mlx, LENGTH, HEIGHT);
	s.addr = mlx_get_data_addr(s.img, &s.bpp, &s.sizeline, &s.endian);
	draw_player_view(&s);
	draw_minimap(&s);
	mlx_put_image_to_window(s.mlx, s.win, s.img, 0, 0);
	mlx_hook(s.win, KeyPress, KeyPressMask, keypress, (void *)&s);
	mlx_hook(s.win, KeyRelease, KeyReleaseMask, keyrelease, (void *)&s);
	mlx_hook(s.win, ClientMessage, LeaveWindowMask, mlx_loop_end, s.mlx);
	mlx_loop(s.mlx);
	free_all(&s);
	return (0);
}
