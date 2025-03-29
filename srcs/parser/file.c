/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 20:08:17 by tchaloei          #+#    #+#             */
/*   Updated: 2025/03/29 20:18:59 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"





void	wall_point(t_cub3d *cub, int i, int j, int k)
{
	// if ((i == 0 || !cub->map->plan[i + 1]) && cub->map->plan[i][j] != '1' && cub->map->plan[i][j] != ' ')//ใช้ในกรณีที่มี space แล้วจุดข้างล่างเป็น 0
	// 	exit_code("Error: information wrong[2]\n", FREE_S, cub);// จะเท่ากับ wall เป็นรู
	
	// if (j == 0 && cub->map->plan[i][j] != '1')
	// 	exit_code("Error: information wrong\n", FREE_S, cub);
	if (cub->map->plan[i][j] && cub->map->plan[i][j] != ' ' && cub->map->plan[i][j] != '1' && cub->map->plan[i][j] != '0' && cub->map->plan[i][j] != 'N' && cub->map->plan[i][j] != 'S' && cub->map->plan[i][j] != 'W' && cub->map->plan[i][j] != 'E')
		exit_code("Error: information wrong[1..]\n", FREE_S, cub);
	else if ((i == 0 || !cub->map->plan[i + 1]) && (cub->map->plan[i][j] != '1' && cub->map->plan[i][j] != ' '))
	{
		// printf("i = %d\nj = %d\n", i, j);
		exit_code("Error: information wrong[2..]\n", FREE_S, cub);
	}
	else if (i > 0 && j > 0 && cub->map->plan[i][k] == ' ' && cub->map->plan[i][j] != '1')
		exit_code("Error: information wrong[3]\n", FREE_S, cub);
	else if (i > 0 && (j == 0 || !cub->map->plan[i][j + 1]) && cub->map->plan[i][k] == ' ' && cub->map->plan[i][j] != '1')
		exit_code("Error: information wrong[4]\n", FREE_S, cub);
	else if (cub->map->player == 2)
		exit_code("Error: information wrong[5]\n", FREE_S, cub);
	
}

void	map_survey(t_cub3d *cub)
{
	int	i; 
	int	j;

	i = 0;
	while (cub->map->plan[i])
	{
		j = 0;
		while (cub->map->plan[i][j])
		{
			if (cub->map->plan[i][j] == 'N' || cub->map->plan[i][j] == 'S' || cub->map->plan[i][j] == 'W' || cub->map->plan[i][j] == 'E')
				cub->map->player++;
			while (cub->map->plan[i][j + 1] && cub->map->plan[i][j] == ' ')
				j++;
			wall_point(cub, i, j, j - 1);
			j++;
		}
		j--;
		
		while (j >= 0)
		{
			while (j >= 1 && cub->map->plan[i][j] == ' ')
				j--;
			wall_point(cub, i, j, j + 1);
			j--;
		}
		i++;
	}
	if (cub->map->player == 0)
		exit_code("Error: information wrong\n", FREE_S, cub);// no player
}

void    file_parsing(char *file, t_cub3d *cub)
{
	int fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_code("Error: No such file or directory\n", FREE_S, cub);
	cub->map = malloc(sizeof(t_map));
	if (!cub->map)
		exit_code("can not allocate memory\n", FREE_S, cub);
	cub->map->no = NULL;
	cub->map->so = NULL;
	cub->map->we = NULL;
	cub->map->ea = NULL;
	cub->map->player = 0;
	cub->map->plan = NULL;
	reading_map(fd, cub, 1);
	map_survey(cub);
	printf("%s\n%s\n%s\n%s\n", cub->map->no, cub->map->so, cub->map->we, cub->map->ea);
	printf("%d %d %d\n", cub->map->floor[0], cub->map->floor[1], cub->map->floor[2]);
	printf("%d %d %d\n", cub->map->ceiling[0], cub->map->ceiling[1], cub->map->ceiling[2]);
	int i = 0;
	while (cub->map->plan[i])
		printf("%s\n", cub->map->plan[i++]);
}
