/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:10:11 by chduong           #+#    #+#             */
/*   Updated: 2022/05/24 17:15:34 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

t_uint	get_pixel_color(t_data *text, int x, int y)
{
	char	*dst;

	dst = text->img_data + (x * (text->bpp / 8) + y * text->size_line);
	return ((*(t_uint *)dst));
}

void	my_mlx_pixel_put(t_cube *s, int x, int y, int color)
{
	char	*dst;

	dst = s->addr + (y * s->sizeline + x * s->bpp / 8);
	*(unsigned int *)dst = color;
}

void	write_big_pixel(t_cube *s, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < s->mnm_pix)
	{
		j = 0;
		while (j < s->mnm_pix)
		{
			my_mlx_pixel_put(s, x + j, y + i, color);
			j++;
		}
		i++;
	}
}
