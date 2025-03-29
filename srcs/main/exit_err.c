/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:27:28 by tchaloei          #+#    #+#             */
/*   Updated: 2025/03/21 02:39:26 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    exit_code(char *msg, int opt, t_cub3d *cub)
{
    ft_putstr_fd(msg, 2);
    if (opt == FREE_S)
        ft_free_struct(cub);
    exit(1);
}
