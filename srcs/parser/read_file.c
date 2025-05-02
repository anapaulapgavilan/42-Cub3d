/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:14:57 by ana-pper          #+#    #+#             */
/*   Updated: 2025/03/23 14:18:27 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**realloc_scene(char **scene, int new_size)
{
	char	**new_scene;
	int		i;

	new_scene = malloc(sizeof(char *) * (new_size + 1));
	if (!new_scene)
		return (NULL);
	i = 0;
	while (scene && scene[i])
	{
		new_scene[i] = scene[i];
		i++;
	}
	new_scene[new_size] = NULL;
	free(scene);
	return (new_scene);
}

static char	*read_and_format_line(int fd)
{
	char	*line;
	char	*formatted;
	int		len;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	formatted = ft_strdup(line);
	free(line);
	line = formatted;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

static int	add_line_to_scene(char ***scene, int *line_count, int fd)
{
	char	*line;
	char	**temp;

	line = read_and_format_line(fd);
	if (!line)
		return (0);
	if (line[0] == '\0')
	{
		free(line);
		return (1);
	}
	temp = realloc_scene(*scene, *line_count + 1);
	if (!temp)
	{
		free(line);
		return (ERROR);
	}
	*scene = temp;
	(*scene)[*line_count] = line;
	(*line_count)++;
	(*scene)[*line_count] = NULL;
	return (1);
}

int	read_scene(t_data *data, char *file)
{
	int		fd;
	int		line_count;
	char	**scene;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd(SCENE_FILE_ERR, 2), ERROR);
	scene = malloc(sizeof(char *));
	if (!scene)
		return (close(fd), ERROR);
	scene[0] = NULL;
	line_count = 0;
	while (add_line_to_scene(&scene, &line_count, fd))
		;
	close(fd);
	if (line_count == 0)
	{
		free(scene);
		return (ft_putstr_fd(IS_EMPTY_ERR, 2), ERROR);
	}
	data->scene = scene;
	check_valid_scene(data);
	return (SUCCESS);
}
