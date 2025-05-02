/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 13:32:58 by ana-pper          #+#    #+#             */
/*   Updated: 2025/03/23 13:56:54 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	flood_fill(char **map, t_point pos, t_dim dim)
{
	if (pos.y < 0 || pos.y >= dim.height || pos.x < 0 || pos.x >= dim.width)
		return ;
	if (map[pos.y][pos.x] == '1' || map[pos.y][pos.x] == 'V')
		return ;
	map[pos.y][pos.x] = 'V';
	flood_fill(map, (t_point){pos.x + 1, pos.y}, dim);
	flood_fill(map, (t_point){pos.x - 1, pos.y}, dim);
	flood_fill(map, (t_point){pos.x, pos.y + 1}, dim);
	flood_fill(map, (t_point){pos.x, pos.y - 1}, dim);
}

static char	**duplicate_map(t_data *data, int max_height)
{
	char	**map_copy;
	int		y;

	map_copy = malloc(sizeof(char *) * (max_height + 1));
	if (!map_copy)
	{
		ft_putstr_fd(MEMORY_ERR, 2);
		return (NULL);
	}
	y = 0;
	while (y < max_height)
	{
		map_copy[y] = ft_strdup(data->map[y]);
		if (!map_copy[y])
		{
			ft_putstr_fd(MEMORY_ERR, 2);
			return (NULL);
		}
		y++;
	}
	map_copy[max_height] = NULL;
	return (map_copy);
}

static int	run_flood_fill_and_check(char **map_copy, t_dim dim, t_point start)
{
	int	valid_path;
	int	y;
	int	x;

	flood_fill(map_copy, start, dim);
	valid_path = 0;
	y = 0;
	while (y < dim.height)
	{
		x = 0;
		while (x < (int)ft_strlen(map_copy[y]))
		{
			if (map_copy[y][x] == 'V')
			{
				valid_path = 1;
				break ;
			}
			x++;
		}
		if (valid_path)
			break ;
		y++;
	}
	return (valid_path);
}

static char	**prepare_map_copy(t_data *data, t_point *player, t_dim dim)
{
	char	**map_copy;

	if (dim.width == 0 || dim.height == 0)
	{
		ft_putstr_fd(MAP_MEASURE_ERR, 2);
		return (NULL);
	}
	if (!find_player_position(data, &player->x, &player->y))
	{
		ft_putstr_fd(PLAYER_POS_ERR, 2);
		return (NULL);
	}
	if (is_player_trapped(data, player->x, player->y))
	{
		ft_putstr_fd(PLAYER_TRAPPED_ERR, 2);
		return (NULL);
	}
	map_copy = duplicate_map(data, dim.height);
	return (map_copy);
}

int	validate_map_connectivity(t_data *data)
{
	char	**map_copy;
	t_point	start;
	t_dim	dim;

	dim.width = data->map_width;
	dim.height = data->map_height;
	map_copy = prepare_map_copy(data, &start, dim);
	if (!map_copy)
		return (ERROR);
	if (!run_flood_fill_and_check(map_copy, dim, start))
	{
		ft_putstr_fd(PLAYER_PATH_ERR, 2);
		ft_free_tab((void **)map_copy, -1);
		return (ERROR);
	}
	ft_free_tab((void **)map_copy, -1);
	return (SUCCESS);
}
