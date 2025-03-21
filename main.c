/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:05:08 by tchaloei          #+#    #+#             */
/*   Updated: 2025/03/22 02:04:51 by tchaloei         ###   ########.fr       */
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

void    input_handling(int ac, char **av)
{
	int i;

	i = 0;
	if (ac != 2)
	{
		write(2, "Error: Invalid arguments.\n", 26);
		exit(1);
	}
	else
	{
		while (*av[1])
		{
			if (ft_strncmp(av[1], ".cub", 5) == 0)
			{
				while (i-- > 0)
					av[1]--;
				return ;
			}
			i++;
			av[1]++;
		}
		write(2, "Error: This is not a map in format *.cub\n", 42);
		exit(1);
	}
}

void	map_parsing_color(t_cub3d *cub, int	obj[3], char **tmp, int fc)
{
	char	**color;

	color = ft_split(tmp[fc] + 2, ',');
	// int i = 0;
	// while (color[i])
	// 	printf("%s\n", color[i++]);
	if (!color[0] || !color[1] || !color[2] || color[3])
	{
		ft_free_split(color);
		ft_free_split(tmp);
		free(cub->data);
		exit_code("Error: defined wrong color\n", FREE_S, cub);
	}
	obj[0] = ft_atoi(color[0]);
	obj[1] = ft_atoi(color[1]);
	obj[2] = ft_atoi(color[1]);
	ft_free_split(color);
}

void	map_parsing_plan(t_cub3d *cub, t_map *map, char **tmp)
{
	int i;
	
	map->plan = malloc(sizeof(char **) * (ft_strlen2d(tmp) - 6 + 1));
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

void	map_parsing(t_cub3d *cub, t_map *map)
{
	char	**tmp;

	
	tmp = ft_split(cub->data, '\n');//ต้องดักกรณีที่map มันว่างด้วย !tmp[0] !tmp[1] ...
	if (ft_strncmp(tmp[0], "NO ", 3) || ft_strncmp(tmp[1], "SO ", 3)
		|| ft_strncmp(tmp[2], "WE ", 3)|| ft_strncmp(tmp[3], "EA ", 3)
		|| ft_strncmp(tmp[4], "F ", 2) || ft_strncmp(tmp[5], "C ", 2))
	{
		ft_free_split(tmp);
		free(cub->data);
		exit_code("Error: information wrong\n", FREE_S, cub);
	}
	map->no = ft_strdup(tmp[0] + 3);
	map->so = ft_strdup(tmp[1] + 3);
	map->we = ft_strdup(tmp[2] + 3);
	map->ea = ft_strdup(tmp[3] + 3);	
	map_parsing_color(cub, map->floor, tmp, 4);
	map_parsing_color(cub, map->ceiling, tmp, 5);
	map_parsing_plan(cub, map, tmp);
	ft_free_split(tmp);
	free(cub->data);
}

void    reading_map(int fd, t_cub3d *cub, int b)
{
	cub->data = ft_strdup("\0");
	while (b > 0)
	{
		b = read(fd, cub->buf, 9);
		cub->buf[9] = '\0';
		// if (b == 0)
		//     break;
		cub->tmp2 = ft_strdup(cub->buf);
		ft_memset(cub->buf, 0, sizeof(cub->buf));
		cub->tmp1 = ft_strdup(cub->data);
		free(cub->data);
		cub->data = ft_strjoin(cub->tmp1, cub->tmp2);
		free(cub->tmp1);
		free(cub->tmp2);
	}
	// printf("%s\n", cub->data);
	// free(cub->data);
	map_parsing(cub, cub->map);
	close(fd);
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
	cub->map->plan = NULL;
	reading_map(fd, cub, 1);
	printf("%s\n%s\n%s\n%s\n", cub->map->no, cub->map->so, cub->map->we, cub->map->ea);
	printf("%d %d %d\n", cub->map->floor[0], cub->map->floor[1], cub->map->floor[2]);
	printf("%d %d %d\n", cub->map->ceiling[0], cub->map->ceiling[1], cub->map->ceiling[2]);
	int i = 0;
	while (cub->map->plan[i])
		printf("%s\n", cub->map->plan[i++]);
}

void    clean_all(t_cub3d *cub)
{
	// free(cub->map);
	// free(cub);
	ft_free_struct(cub);
}

int	main(int ac, char **av)
{
	t_cub3d   *cub;

	input_handling(ac, av);
	cub = malloc(sizeof(t_cub3d));
	if (!cub)
		exit_code("can not allocate memory\n", NO_FREE_S, cub);
	cub->map = NULL;
	file_parsing(av[1], cub);

	
	// void    *mlx_connect;
	// void    *mlx_win;

	// mlx_connect = mlx_init();
	// mlx_win = mlx_new_window(mlx_connect, 800, 800, "cub3D");

	// mlx_loop(mlx_connect);

	// mlx_destroy_window(mlx_connect, mlx_win);
	// mlx_destroy_display(mlx_connect);
	// free(mlx_connect);
	// printf("cub3D\n");
	clean_all(cub);
}
