/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 13:35:31 by chduong           #+#    #+#             */
/*   Updated: 2022/06/06 21:15:48 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_background(t_cube *s)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				my_mlx_pixel_put(s, x, y, s->ceiling);
			else
				my_mlx_pixel_put(s, x, y, s->floor);
			++x;
		}
		++y;
	}
}

void	draw_wall(int x, t_cub3d *cub, t_ray ray, t_data *text)
{
	int		y_off;
	int		x_off;
	int		y_start;
	int		y_end;

	y_start = (cub->stripeh[x] > cub->w_height) ?
	0 : (cub->w_height / 2 - cub->stripeh[x] / 2);
	y_end = (cub->stripeh[x] > cub->w_height) ?
	cub->w_height : y_start + cub->stripeh[x];
	if (ray.hor)
		x_off = (int)ray.inter.x % TILE_SIZE;
	else
		x_off = (int)ray.inter.y % TILE_SIZE;
	x_off = (x_off * text->width) / TILE_SIZE;
	y_off = (cub->stripeh[x] > cub->w_height) ?
	(cub->stripeh[x] / 2 - cub->w_height / 2) : 0;
	while (y_start < y_end)
	{
		my_mlx_pixel_put(&cub->img, x, y_start,
		get_pixel_color(text, x_off, (y_off * text->height) / cub->stripeh[x]));
		y_start++;
		y_off++;
	}
}

void	render_wall(t_cub3d *cub, char *img_data)
{
	t_ray	ray;
	int		pix;
	double	angle;

	pix = 0;
	ft_bzero(img_data, cub->w_width * cub->w_height * 4);
	draw_background(cub);
	while (pix < cub->w_width)
	{
		angle = normalize_angle(cub->player.angle +
		atan((pix - (cub->w_width / 2)) / cub->dstprojplane));
		ray = raycast(cub, angle);
		cub->raydst[pix] = ray.dst;
		ray.dst *= cos(angle - cub->player.angle);
		cub->stripeh[pix] = floor((TILE_SIZE / ray.dst) * cub->dstprojplane);
		draw_wall(pix, cub, ray, get_wall_text(cub, angle, ray.hor));
		pix++;
	}
}

void	draw_player_view(t_cube *s)
{
	draw_background(s);
}
