/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:37:07 by chduong           #+#    #+#             */
/*   Updated: 2022/06/08 10:56:36 by jvermeer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	rad(float degree)
{
	return (degree * (float)PI / (float)180);
}

float	normalize_angle(float angle)
{
	angle = remainder(angle, PI * 2);
	if (angle < 0)
		angle += PI * 2;
	return (angle);
}

float	dist_ab(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
