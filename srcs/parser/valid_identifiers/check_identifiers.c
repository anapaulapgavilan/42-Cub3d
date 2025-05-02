/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_identifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:01:54 by ana-pper          #+#    #+#             */
/*   Updated: 2025/03/23 12:20:14 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	file_exists(const char *filepath)
{
	int	len;
	int	fd;

	len = ft_strlen(filepath);
	if (len < 4 || ft_strncmp(filepath + len - 4, ".png", 4) != 0)
	{
		ft_putstr_fd(EXTENSION_ERR, 2);
		return (ERROR);
	}
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd(TEXT_FILE_ERR, 2);
		return (ERROR);
	}
	close(fd);
	return (SUCCESS);
}

int	validate_rgb_components(char **values)
{
	int	r;
	int	g;
	int	b;

	if (!is_valid_number(values[0]) || !is_valid_number(values[1])
		|| !is_valid_number(values[2]))
		return (ERROR);
	r = ft_atoi(values[0]);
	g = ft_atoi(values[1]);
	b = ft_atoi(values[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (ERROR);
	return (SUCCESS);
}

static int	validate_tokens(char **tokens)
{
	if (ft_strcmp(tokens[0], "NO") == 0 || ft_strcmp(tokens[0], "SO") == 0
		|| ft_strcmp(tokens[0], "WE") == 0 || ft_strcmp(tokens[0], "EA") == 0)
	{
		if (!tokens[1] || tokens[2])
			return (ft_putstr_fd(TEXTURE_ERR, 2), ERROR);
		else if (file_exists(tokens[1]) == ERROR)
			return (ERROR);
	}
	else if (ft_strcmp(tokens[0], "F") == 0 || ft_strcmp(tokens[0], "C") == 0)
	{
		if (!tokens[1] || tokens[2])
			return (ft_putstr_fd(COLOR_FORMAT_ERR, 2), ERROR);
		else if (validate_rgb_format(tokens[1]) == ERROR)
			return (ft_putstr_fd(INVALID_RGB_ERR, 2), ERROR);
	}
	return (SUCCESS);
}

static int	process_scene_line(const char *scene_line)
{
	char	*line;
	char	**tokens;
	int		ret;

	line = ft_strtrim(scene_line, " ");
	ret = SUCCESS;
	if (!line)
		return (ft_putstr_fd(MEMORY_ERR, 2), ERROR);
	if (!line[0])
	{
		free(line);
		return (SUCCESS);
	}
	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0])
	{
		free(line);
		ft_free_tab((void **)tokens, -1);
		return (SUCCESS);
	}
	ret = validate_tokens(tokens);
	ft_free_tab((void **)tokens, -1);
	free(line);
	return (ret);
}

int	validate_texture_and_colors(t_data *data)
{
	int	i;

	i = 0;
	while (data->scene[i])
	{
		if (process_scene_line(data->scene[i]) == ERROR)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}
