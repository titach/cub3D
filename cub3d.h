/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 05:06:47 by tchaloei          #+#    #+#             */
/*   Updated: 2025/03/21 02:46:05 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "minilibx-linux/mlx.h"
# include "libft/libft.h"

# define NO_FREE_S 0
# define FREE_S 1

typedef struct s_map
{
    char    *no;
    char    *so;
    char    *we;
    char    *ea;
    int     floor[3];
    int     ceiling[3];
    char    **plan;
}   t_map;

typedef struct s_cub3d
{
    char    *tmp1;
    char    *tmp2;
    char    *data;
    char    buf[10];
    t_map   *map;
}   t_cub3d;

void    exit_code(char *msg, int opt, t_cub3d *cub);
void	ft_free_struct(t_cub3d *cub);

#endif