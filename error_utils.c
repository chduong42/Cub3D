/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 18:00:57 by chduong           #+#    #+#             */
/*   Updated: 2022/05/16 18:01:26 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error(t_data *data, const char *msg)
{
	printf("\n\e[0;31mError\n\e[0m");
	printf("\e[41m%s\e[0m\n", msg);
	clear_data(data);
}

void	check_ptr(void *ptr, t_data *data)
{
	if (!ptr)
	{
		printf("\e[0;31mError\n\e[0m");
		printf("\e[41mFail memory allocation\n\e[0m");
		clear_data(data);
	}
}
