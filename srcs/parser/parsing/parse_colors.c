/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 11:52:22 by ana-pper          #+#    #+#             */
/*   Updated: 2025/03/23 11:56:46 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_array_size(char **array)
{
	int	count;

	count = 0;
	if (!array)
		return (0);
	while (array[count])
		count++;
	return (count);
}

int	parse_color_line(const char *line, t_data *data)
{
	char	**rgb_parts;
	int		r;
	int		g;
	int		b;
	int		color;

	rgb_parts = ft_split(line + 2, ',');
	if (!rgb_parts || ft_array_size(rgb_parts) != 3)
		return (ft_putstr_fd(COLOR_FORMAT_ERR, 2), ERROR);
	r = ft_atoi(rgb_parts[0]);
	g = ft_atoi(rgb_parts[1]);
	b = ft_atoi(rgb_parts[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		ft_putstr_fd(INVALID_COLORS_ERR, 2);
		ft_free_tab((void **)rgb_parts, -1);
		return (ERROR);
	}
	color = (r << 16) | (g << 8) | b;
	if (line[0] == 'F')
		data->floor_color = color;
	else
		data->ceil_color = color;
	ft_free_tab((void **)rgb_parts, -1);
	return (SUCCESS);
}

int	parse_scene_colors(t_data *data)
{
	int	i;
	int	ret;

	i = 0;
	while (data->scene[i])
	{
		if (data->scene[i][0] == 'F' || data->scene[i][0] == 'C')
		{
			ret = parse_color_line(data->scene[i], data);
			if (ret != SUCCESS)
				return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}
