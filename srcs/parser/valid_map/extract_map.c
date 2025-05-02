/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 13:25:37 by ana-pper          #+#    #+#             */
/*   Updated: 2025/03/23 13:30:10 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_blank_line(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static int	remove_blank_rows(t_data *data, int map_start)
{
	int	i;
	int	valid_row_count;

	i = map_start;
	valid_row_count = 0;
	while (data->scene[i])
	{
		if (!is_blank_line(data->scene[i]))
			valid_row_count++;
		i++;
	}
	return (valid_row_count);
}

static void	find_map_dimensions(t_data *data, int *map_start, int *map_width)
{
	int	i;
	int	line_length;

	*map_start = -1;
	*map_width = 0;
	i = 0;
	while (data->scene[i])
	{
		if (is_map_line(data->scene[i]))
		{
			if (*map_start == -1)
				*map_start = i;
			line_length = ft_strlen(data->scene[i]);
			if (line_length > *map_width)
				*map_width = line_length;
		}
		i++;
	}
}

static void	fill_map(t_data *data, int map_start, int map_width)
{
	int	i;
	int	j;

	i = map_start;
	j = 0;
	while (data->scene[i])
	{
		if (!is_blank_line(data->scene[i]))
		{
			data->map[j] = ft_strldup(data->scene[i], map_width, ' ');
			j++;
		}
		i++;
	}
	data->map[j] = NULL;
}

void	extract_map(t_data *data)
{
	int	map_start;
	int	map_width;
	int	map_height;

	find_map_dimensions(data, &map_start, &map_width);
	if (map_start == -1)
	{
		ft_putstr_fd(MAP_MISSING_ERR, 2);
		exit(ERROR);
	}
	map_height = remove_blank_rows(data, map_start);
	data->map_width = map_width;
	data->map_height = map_height;
	data->map_start_line = map_start;
	data->map = malloc(sizeof(char *) * (map_height + 1));
	if (!data->map)
	{
		ft_putstr_fd(MEMORY_ERR, 2);
		exit(ERROR);
	}
	fill_map(data, map_start, map_width);
}
