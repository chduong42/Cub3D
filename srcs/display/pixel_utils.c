/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:10:11 by chduong           #+#    #+#             */
/*   Updated: 2022/05/30 16:18:07 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	create_trgb(int t, int r, int g, int b)
{
	printf("t=%d\t r=%d\t g=%d\t b=%d\n", t, r, g, b);
	return (t << 24 | r << 16 | g << 8 | b);
}

t_uint	get_pixel_color(t_cube *s, int x, int y)
{
	char	*dst;

	dst = s->addr + (x * (s->bpp / 8) + y * s->sizeline);
	return ((*(t_uint *)dst));
}

void	my_mlx_pixel_put(t_cube *s, int x, int y, int color)
{
	char	*dst;

	dst = s->addr + (y * s->sizeline + x * s->bpp / 8);
	*(unsigned int *)dst = color;
}
