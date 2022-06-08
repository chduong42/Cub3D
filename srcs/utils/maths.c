/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:37:07 by chduong           #+#    #+#             */
/*   Updated: 2022/06/08 16:48:22 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	rad(float degree)
{
	return (degree * PI / 180);
}

float	dist_ab(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

float	modulo_2pi(float deg)
{
	if (deg < 0)
		deg += 360;
	else if (deg > 359)
		deg -= 360;
	return (deg);
}