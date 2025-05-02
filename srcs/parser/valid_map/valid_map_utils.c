/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:11:31 by ana-pper          #+#    #+#             */
/*   Updated: 2025/03/23 14:11:58 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_valid_chars(t_data *data)
{
	int		row;
	int		col;
	int		start_pos_count;
	char	c;

	start_pos_count = 0;
	row = 0;
	while (data->map[row])
	{
		col = 0;
		while (data->map[row][col])
		{
			c = data->map[row][col];
			if (!ft_strchr("01NSEW ", c))
				return (ft_putstr_fd(INVALID_CHAR_ERR, 2), ERROR);
			if (ft_strchr("NSEW", c))
				start_pos_count++;
			col++;
		}
		row++;
	}
	if (start_pos_count != 1)
		return (ft_putstr_fd(PLAYER_POS_ERR, 2), ERROR);
	return (SUCCESS);
}
