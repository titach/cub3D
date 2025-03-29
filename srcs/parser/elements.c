/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 20:22:14 by tchaloei          #+#    #+#             */
/*   Updated: 2025/03/29 20:22:19 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	which_elements(t_cub3d *cub, int i)
{
	if (ft_strncmp(cub->data + i, "NO", 2) == 0 || ft_strncmp(cub->data + i, "SO", 2) == 0 || ft_strncmp(cub->data + i, "WE", 2) == 0 || ft_strncmp(cub->data + i, "EA", 2) == 0)
		return (0);
	else if (ft_strncmp(cub->data + i, "F", 1) == 0 || ft_strncmp(cub->data + i, "C", 1) == 0)
		return (1);
	return (2);
}

void	elements_checking(t_cub3d *cub)
{
	int i;
	int	flag[2];
	int n;

	i = 0;
	flag[0] = -1;
	flag[1] = -1;
	while (cub->data[i])
	{
		flag[0] = which_elements(cub, i);
		while (cub->data[i] && cub->data[i] != '\n')
			i++;
		n = 0;
		while (cub->data[i] && cub->data[i] == '\n')
		{
			n++;
			i++;
		}
		flag[1] = which_elements(cub, i);
		if (cub->data[i] && flag[0] != flag[1] && n < 2)
		{
			free(cub->data);
			exit_code("Error: information wrong\n", FREE_S, cub);
		}
	}
}

void    reading_map(int fd, t_cub3d *cub, int b)
{
	cub->data = ft_strdup("\0");
	while (b > 0)
	{
		b = read(fd, cub->buf, 9);
		cub->buf[9] = '\0';
		cub->tmp2 = ft_strdup(cub->buf);
		ft_memset(cub->buf, 0, sizeof(cub->buf));
		cub->tmp1 = ft_strdup(cub->data);
		free(cub->data);
		cub->data = ft_strjoin(cub->tmp1, cub->tmp2);
		free(cub->tmp1);
		free(cub->tmp2);
	}
	elements_checking(cub);
	map_checking(cub, -1);
	free(cub->data);
	close(fd);
}
