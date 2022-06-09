/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 08:58:22 by jvermeer          #+#    #+#             */
/*   Updated: 2022/06/09 22:49:58 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_all(t_cube *s)
{
	if (s->no)
		mlx_destroy_image(s->mlx, s->no);
	if (s->so)
		mlx_destroy_image(s->mlx, s->so);
	if (s->we)
		mlx_destroy_image(s->mlx, s->we);
	if (s->ea)
		mlx_destroy_image(s->mlx, s->ea);
	if (s->file)
		free_array(s->file);
	if (s->maps)
		free_array(s->maps);
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

int	display(t_cube *s)
{
	keys_effects(s);
	balayage(s, (float)s->pov);
	mlx_put_image_to_window(s->mlx, s->win, s->img, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_cube	s;

	ft_memset(&s, 0, sizeof(t_cube));
	s.mlx = mlx_init();
	if (!parsing(&s, ac, av) || !data_collect(&s))
	{
		free_all(&s);
		return (1);
	}
	s.win = mlx_new_window(s.mlx, WIDTH, HEIGHT, "Cub3D");
	s.img = mlx_new_image(s.mlx, WIDTH, HEIGHT);
	s.addr = mlx_get_data_addr(s.img, &s.bpp, &s.sizeline, &s.endian);
	mlx_loop_hook(s.mlx, &display, &s);
	mlx_hook(s.win, KeyPress, KeyPressMask, keypress, (void *)&s);
	mlx_hook(s.win, KeyRelease, KeyReleaseMask, keyrelease, (void *)&s);
	mlx_hook(s.win, ClientMessage, LeaveWindowMask, mlx_loop_end, s.mlx);
	mlx_loop(s.mlx);
	free_all(&s);
	return (0);
}
