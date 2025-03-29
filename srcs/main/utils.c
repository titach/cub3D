/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 20:23:50 by tchaloei          #+#    #+#             */
/*   Updated: 2025/03/29 20:25:07 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strlen2d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ft_free_struct(t_cub3d *cub)
{
	if (cub)
	{
		if (cub->map)
		{
			if (cub->map->no)
				free(cub->map->no);
			if (cub->map->so)
				free(cub->map->so);
			if (cub->map->we)
				free(cub->map->we);
			if (cub->map->ea)
				free(cub->map->ea);
			if (cub->map->plan)
				ft_free_split(cub->map->plan);
			free(cub->map);
		}
		free(cub);
	}
}
