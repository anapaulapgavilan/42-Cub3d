/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:00:04 by ana-pper          #+#    #+#             */
/*   Updated: 2025/03/23 14:11:48 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_nsew_spaces(t_data *data, int row, int col, t_dim dim)
{
	if (row > 0 && data->map[row - 1][col] == ' ')
		return (ft_putstr_fd(ENCOLSE_MAP_ERR, 2), ERROR);
	if (col > 0 && data->map[row][col - 1] == ' ')
		return (ft_putstr_fd(ENCOLSE_MAP_ERR, 2), ERROR);
	if (row + 1 < dim.height && data->map[row + 1]
		&& data->map[row + 1][col] == ' ')
		return (ft_putstr_fd(ENCOLSE_MAP_ERR, 2), ERROR);
	if (col + 1 < dim.width && data->map[row][col + 1] == ' ')
		return (ft_putstr_fd(ENCOLSE_MAP_ERR, 2), ERROR);
	return (SUCCESS);
}

static int	check_neighbors(t_data *data, int row, int col, t_dim dim)
{
	if (row > 0 && col < dim.width && data->map[row - 1][col] && data->map[row
		- 1][col] != '1' && data->map[row - 1][col] != ' ')
		return (ft_putstr_fd(ENCOLSE_MAP_ERR, 2), ERROR);
	if (col > 0 && data->map[row][col - 1] && data->map[row][col - 1] != '1'
		&& data->map[row][col - 1] != ' ')
		return (ft_putstr_fd(ENCOLSE_MAP_ERR, 2), ERROR);
	if (row + 1 < dim.height && col < dim.width && data->map[row + 1]
		&& data->map[row + 1][col] && data->map[row + 1][col] != '1'
		&& data->map[row + 1][col] != ' ')
		return (ft_putstr_fd(ENCOLSE_MAP_ERR, 2), ERROR);
	if (col + 1 < dim.width && data->map[row][col + 1] && data->map[row][col
		+ 1] != '1' && data->map[row][col + 1] != ' ')
		return (ft_putstr_fd(ENCOLSE_MAP_ERR, 2), ERROR);
	return (SUCCESS);
}

static int	check_spaces(t_data *data, int row, int col)
{
	int		width;
	int		height;
	t_dim	dim;
	char	c;

	width = data->map_width;
	height = data->map_height;
	dim.width = width;
	dim.height = height;
	c = data->map[row][col];
	if (ft_strchr("NSEW", c))
	{
		if (check_nsew_spaces(data, row, col, dim) == ERROR)
			return (ERROR);
	}
	if (check_neighbors(data, row, col, dim) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

static int	check_map_closed(t_data *data)
{
	int	row;
	int	col;

	row = 0;
	while (data->map[row])
	{
		col = 0;
		while (data->map[row][col])
		{
			if ((row == 0 || !data->map[row + 1]) && data->map[row][col] != '1'
				&& data->map[row][col] != ' ')
				return (ft_putstr_fd(ENCOLSE_MAP_ERR, 2), ERROR);
			if (data->map[row][col] == ' ')
				if (check_spaces(data, row, col) != SUCCESS)
					return (ERROR);
			col++;
		}
		if ((data->map[row][0] != '1' && data->map[row][0] != ' ')
			|| (data->map[row][col - 1] != '1' && data->map[row][col
				- 1] != ' '))
			return (ft_putstr_fd(ENCOLSE_MAP_ERR, 2), ERROR);
		row++;
	}
	return (SUCCESS);
}

int	validate_map(t_data *data)
{
	if (!data->map)
		return (ft_putstr_fd(MAP_MISSING_ERR, 2), ERROR);
	format_map_spaces(data);
	if (check_valid_chars(data) != SUCCESS)
		return (ERROR);
	if (check_map_closed(data) != SUCCESS)
		return (ERROR);
	if (validate_map_connectivity(data) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}
