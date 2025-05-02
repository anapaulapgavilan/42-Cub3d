/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 13:55:35 by ana-pper          #+#    #+#             */
/*   Updated: 2025/03/23 13:57:04 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_player_position(t_data *data, int *px, int *py)
{
	int	y;
	int	x;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (ft_strchr("NSEW", data->map[y][x]))
			{
				*px = x;
				*py = y;
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	is_player_trapped(t_data *data, int px, int py)
{
	if (data->map[py - 1][px] == '0' || data->map[py + 1][px] == '0'
		|| data->map[py][px - 1] == '0' || data->map[py][px + 1] == '0')
	{
		return (0);
	}
	return (1);
}
