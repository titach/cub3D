/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 05:06:47 by tchaloei          #+#    #+#             */
/*   Updated: 2025/03/29 20:26:06 by tchaloei         ###   ########.fr       */
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
# include <stdbool.h>
# include "mlx.h"
# include "libft.h"
# include <X11/X.h>      // สำหรับค่าของ event ต่างๆ
# include <X11/keysym.h>

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
    int    player;
    char    **plan;
}   t_map;

typedef struct s_cub3d
{
    char    *tmp1;
    char    *tmp2;
    char    **info[2];
    char    *data;
    char    buf[10];
    t_map   *map;
}   t_cub3d;

/* ------------------main------------------ */
//exit_err
void    exit_code(char *msg, int opt, t_cub3d *cub);
//utils
int	ft_strlen2d(char **str);
void	ft_free_split(char **split);
void	ft_free_struct(t_cub3d *cub);

/* ------------------parser------------------ */
//file
void    file_parsing(char *file, t_cub3d *cub);
//elements
void    reading_map(int fd, t_cub3d *cub, int b);
//map
void	map_checking(t_cub3d *cub, int i);

#endif