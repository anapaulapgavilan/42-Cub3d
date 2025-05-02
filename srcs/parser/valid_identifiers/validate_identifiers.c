/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_identifiers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:57:55 by ana-pper          #+#    #+#             */
/*   Updated: 2025/03/23 13:21:51 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	process_scene_line(const char *scene_line, int *map_started,
		t_identifiers *found)
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
	if (is_map_line(line))
		return (handle_map_line(line, map_started, found));
	if (*map_started)
	{
		free(line);
		ft_putstr_fd(MISSING_ID_ERR, 2);
		return (ERROR);
	}
	ret = process_identifier_line(line, found);
	free(line);
	return (ret);
}

int	validate_identifier_order(t_data *data)
{
	int				i;
	int				map_started;
	t_identifiers	found;

	found.no = 0;
	found.so = 0;
	found.we = 0;
	found.ea = 0;
	found.f = 0;
	found.c = 0;
	i = 0;
	map_started = 0;
	while (data->scene[i])
	{
		if (process_scene_line(data->scene[i], &map_started, &found) == ERROR)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

static int	update_identifier(const char *line, t_identifiers *found)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		found->no++;
	else if (ft_strncmp(line, "SO", 2) == 0)
		found->so++;
	else if (ft_strncmp(line, "WE", 2) == 0)
		found->we++;
	else if (ft_strncmp(line, "EA", 2) == 0)
		found->ea++;
	else if (ft_strncmp(line, "F", 1) == 0)
		found->f++;
	else if (ft_strncmp(line, "C", 1) == 0)
		found->c++;
	return (SUCCESS);
}

static int	process_unique_identifier_line(const char *scene_line,
		int *found_map, t_identifiers *found)
{
	char	*line;
	int		skip;
	int		ret;

	line = ft_strtrim(scene_line, " ");
	if (!line)
		return (ft_putstr_fd(MEMORY_ERR, 2), ERROR);
	skip = check_map_or_empty(line, found_map);
	if (skip)
		return (SUCCESS);
	ret = update_identifier(line, found);
	free(line);
	return (ret);
}

int	validate_unique_identifiers(t_data *data)
{
	t_identifiers	found;
	int				i;
	int				found_map;
	int				ret;

	found.no = 0;
	found.so = 0;
	found.we = 0;
	found.ea = 0;
	found.f = 0;
	found.c = 0;
	found_map = 0;
	i = 0;
	while (data->scene[i])
	{
		ret = process_unique_identifier_line(data->scene[i], &found_map,
				&found);
		if (ret == ERROR)
			return (ERROR);
		i++;
	}
	return (check_unique_counts(&found));
}
