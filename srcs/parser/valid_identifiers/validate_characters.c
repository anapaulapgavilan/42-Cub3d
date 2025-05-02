/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_characters.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:44:08 by ana-pper          #+#    #+#             */
/*   Updated: 2025/03/23 12:54:46 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	validate_line(const char *scene_line, int *map_started)
{
	char	*line;

	line = ft_strtrim(scene_line, " ");
	if (!line)
		return (ft_putstr_fd(MEMORY_ERR, 2), ERROR);
	if (!line[0])
	{
		free(line);
		return (SUCCESS);
	}
	if (is_valid_map_line(line))
		*map_started = 1;
	else if (!(*map_started))
	{
		if (!is_valid_identifier(line))
			return (print_error_and_free(line, INVALID_ID_ERR));
	}
	else
		return (print_error_and_free(line, INVALID_MAP_LINE_ERR));
	free(line);
	return (SUCCESS);
}

int	validate_allowed_characters(t_data *data)
{
	int	i;
	int	map_started;
	int	ret;

	i = 0;
	map_started = 0;
	while (data->scene[i])
	{
		ret = validate_line(data->scene[i], &map_started);
		if (ret == ERROR)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

static int	check_unknown_identifier(char *line, int *map_started)
{
	if (is_map_line(line))
		*map_started = 1;
	else if (!(*map_started))
	{
		if (!(ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
				|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ",
					3) == 0 || ft_strncmp(line, "F ", 2) == 0
				|| ft_strncmp(line, "C ", 2) == 0))
		{
			ft_putstr_fd(UKNOWN_ID_ERR, 2);
			ft_putstr_fd(line, 2);
			ft_putstr_fd("\n", 2);
			return (ERROR);
		}
	}
	return (SUCCESS);
}

static int	validate_unknown_identifier_line(const char *scene_line,
		int *map_started)
{
	char	*line;
	int		ret;

	line = ft_strtrim(scene_line, " ");
	if (!line)
		return (ft_putstr_fd(MEMORY_ERR, 2), ERROR);
	if (line[0] == '\0')
	{
		free(line);
		return (SUCCESS);
	}
	ret = check_unknown_identifier(line, map_started);
	free(line);
	return (ret);
}

int	validate_unknown_identifiers(t_data *data)
{
	int	i;
	int	map_started;
	int	ret;

	i = 0;
	map_started = 0;
	while (data->scene[i])
	{
		ret = validate_unknown_identifier_line(data->scene[i], &map_started);
		if (ret == ERROR)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}
