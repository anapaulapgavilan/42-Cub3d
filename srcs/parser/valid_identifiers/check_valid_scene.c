/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_scene.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:23:00 by ana-pper          #+#    #+#             */
/*   Updated: 2025/03/23 12:42:19 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*format_identifiers_and_colors(const char *line)
{
	char	*trimmed;
	char	*split_pos;
	char	*identifier;
	char	*value;
	char	*formatted;

	trimmed = ft_strtrim(line, " ");
	if (!trimmed)
		return (NULL);
	split_pos = ft_strchr(trimmed, ' ');
	if (!split_pos)
		return (trimmed);
	identifier = ft_strndup(trimmed, split_pos - trimmed);
	if (!identifier)
		return (free(trimmed), NULL);
	value = ft_strtrim(split_pos + 1, " ");
	if (!value)
		return (free(trimmed), free(identifier), NULL);
	formatted = ft_strjoin_three(identifier, " ", value);
	free(trimmed);
	free(identifier);
	free(value);
	return (formatted);
}

static char	*format_scene_line(const char *scene_line)
{
	char	*line;
	char	*trimmed_line;

	if (ft_strncmp(scene_line, "NO", 2) == 0 || ft_strncmp(scene_line, "SO",
			2) == 0 || ft_strncmp(scene_line, "WE", 2) == 0
		|| ft_strncmp(scene_line, "EA", 2) == 0 || ft_strncmp(scene_line, "F",
			1) == 0 || ft_strncmp(scene_line, "C", 1) == 0)
	{
		trimmed_line = ft_strtrim(scene_line, " ");
		if (!trimmed_line)
			return (NULL);
		line = format_identifiers_and_colors(trimmed_line);
		free(trimmed_line);
	}
	else
		line = ft_strdup(scene_line);
	return (line);
}

static void	process_scene_lines(t_data *data)
{
	int		i;
	char	*line;

	i = 0;
	while (data->scene[i])
	{
		line = format_scene_line(data->scene[i]);
		if (!line)
			exit(ERROR);
		free(line);
		i++;
	}
}

static void	initial_scene_validations(t_data *data)
{
	if (validate_allowed_characters(data) != SUCCESS)
		exit(ERROR);
	if (validate_unknown_identifiers(data) != SUCCESS)
		exit(ERROR);
	if (validate_unique_identifiers(data) != SUCCESS)
		exit(ERROR);
	if (validate_identifier_order(data) != SUCCESS)
		exit(ERROR);
	if (validate_texture_and_colors(data) != SUCCESS)
		exit(ERROR);
	extract_map(data);
	if (validate_map(data) != SUCCESS)
		exit(ERROR);
}

void	check_valid_scene(t_data *data)
{
	initial_scene_validations(data);
	process_scene_lines(data);
}
