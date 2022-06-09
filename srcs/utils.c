/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:00:27 by jvermeer          #+#    #+#             */
/*   Updated: 2022/06/09 23:30:54 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	rad(float degree)
{
	return (degree * (float)PI / (float)180);
}

float	modulo_2pi(float deg)
{
	if (deg < 0)
		deg += 360;
	else if (deg > 359)
		deg -= 360;
	return (deg);
}

char	*get_fn(char *l)
{
	char	*dest;
	int		i;

	i = 0;
	while (*l && ft_isspace(*l))
		l++;
	dest = malloc(sizeof(char) * (ft_strlen(l) + 1));
	if (!dest)
		return (NULL);
	while (*l && !ft_isspace(*l))
	{
		dest[i] = *l;
		i++;
		l++;
	}
	dest[i] = '\0';
	return (dest);
}

void	free_array(char **str)
{
	char	**tmp;

	tmp = str;
	while (tmp && *tmp)
	{
		free(*tmp);
		++tmp;
	}
	free(str);
}

int	write_error(char *message)
{
	write(2, "Error\n", 6);
	ft_putstr_fd(message, 2);
	return (0);
}
