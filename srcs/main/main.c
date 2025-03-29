/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:05:08 by tchaloei          #+#    #+#             */
/*   Updated: 2025/03/29 20:24:26 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



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
