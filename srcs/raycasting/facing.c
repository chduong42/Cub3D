/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   facing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 17:56:21 by chduong           #+#    #+#             */
/*   Updated: 2022/05/31 18:00:31 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	isfacedown(double angle)
{
	return (angle > 0 && angle < PI);
}

int	isfaceup(double angle)
{
	return (!isfacedown(angle));
}

int	isfaceright(double angle)
{
	return (angle < 0.5 * PI || angle > 1.5 * PI);
}

int	isfaceleft(double angle)
{
	return (!isfaceright(angle));
}
