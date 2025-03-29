/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 20:19:01 by tchaloei          #+#    #+#             */
/*   Updated: 2025/03/29 20:19:08 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_parsing_plan(t_cub3d *cub, t_map *map, char **tmp)
{
	int i;

	map->plan = malloc(sizeof(char **) * (ft_strlen2d(tmp) - 6 + 1));
	if (!map->plan)
	{
		free(cub->data);
		ft_free_split(tmp);
		exit_code("can not allocate memory\n", FREE_S, cub);
	}
	i = 0;
	while (tmp[i + 6])
	{
		map->plan[i] = ft_strdup(tmp[i + 6]);
		i++;
	}
	map->plan[i] = NULL;
	(void)cub;
	// (void)map;
	// printf("[%d]\n", ft_strlen2d(tmp) - 6 + 1);
}

void	map_parsing_direction(t_cub3d *cub, t_map *map)
{
	if (cub->info[1][2])
	{
		free(cub->data);
		ft_free_split(cub->info[1]);
		ft_free_split(cub->info[0]);
		exit_code("Error: information wrong\n", FREE_S, cub);
	}
	if (ft_strncmp(cub->info[1][0], "NO", 3) == 0)
			map->no = ft_strdup(cub->info[1][1]);
		else if (ft_strncmp(cub->info[1][0], "SO", 3) == 0)
			map->so = ft_strdup(cub->info[1][1]);
		else if (ft_strncmp(cub->info[1][0], "WE", 3) == 0)
			map->we = ft_strdup(cub->info[1][1]);
		else if (ft_strncmp(cub->info[1][0], "EA", 3) == 0)
			map->ea = ft_strdup(cub->info[1][1]);
}


static int	count_parsing_color(t_cub3d *cub, int obj[3], char *row, int i)
{
	int	j;

	j = 0;
	while (row[i])
	{
		while (row[i] && row[i] == ' ')
			i++;
		if (ft_isdigit(row[i]))
		{
			obj[j] = ft_atoi(row + i);
			j++;
			while (row[i] && (ft_isdigit(row[i]) || row[i] == ' '))
				i++;
			if (row[i] == ',' && j < 3)
                i++;
		}
		else
		{
			free(cub->data);
			ft_free_split(cub->info[1]);
			ft_free_split(cub->info[0]);
			exit_code("Error: information wrong\n", FREE_S, cub);
		}
	}
	return (j);
}

void	map_parsing_color(t_cub3d *cub, int	obj[3], char *row, char *format)
{
	int i;

	i = 0;
	while (row[i] && row[i] != format[0])
		i++;
	i++;
	if (count_parsing_color(cub, obj, row, i) < 3 || obj[0] > 255 || obj[1] > 255 || obj[2] > 255)
	{
		free(cub->data);
		ft_free_split(cub->info[1]);
		ft_free_split(cub->info[0]);
		exit_code("Error: information wrong\n", FREE_S, cub);
	}
}

void	map_checking(t_cub3d *cub, int i)
{
	cub->info[0] = ft_split(cub->data, '\n');
	while (++i < 6)
	{
		cub->info[1] = ft_split(cub->info[0][i], ' ');
		if (ft_strncmp(cub->info[1][0], "NO", 3) == 0 || ft_strncmp(cub->info[1][0], "WE", 3) == 0)
			map_parsing_direction(cub, cub->map);
		else if (ft_strncmp(cub->info[1][0], "SO", 3) == 0 || ft_strncmp(cub->info[1][0], "EA", 3) == 0)
			map_parsing_direction(cub, cub->map);
		else if (ft_strncmp(cub->info[1][0], "F", 2) == 0)
			map_parsing_color(cub, cub->map->floor, cub->info[0][i], cub->info[1][0]);
		else if (ft_strncmp(cub->info[1][0], "C", 2) == 0)
			map_parsing_color(cub, cub->map->ceiling, cub->info[0][i], cub->info[1][0]);
		else
		{
			free(cub->data);
			ft_free_split(cub->info[1]);
			ft_free_split(cub->info[0]);
			exit_code("Error: information wrong\n", FREE_S, cub);
		}
		ft_free_split(cub->info[1]);
	}
	map_parsing_plan(cub, cub->map, cub->info[0]);
	ft_free_split(cub->info[0]);
}
