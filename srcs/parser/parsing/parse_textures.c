/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 11:59:16 by ana-pper          #+#    #+#             */
/*   Updated: 2025/03/23 11:59:55 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_texture(t_data *data, const char *line)
{
	char	**tokens;
	int		result;

	result = SUCCESS;
	tokens = ft_split(line, ' ');
	if (!tokens)
		return (ft_putstr_fd(MEMORY_ERR, 2), ERROR);
	if (!tokens[0] || !tokens[1])
	{
		ft_free_tab((void **)tokens, -1);
		return (ft_putstr_fd(TEXTURE_ERR, 2), ERROR);
	}
	if (!ft_strcmp(tokens[0], "NO") && !data->textures.no)
		data->textures.no = ft_strdup(tokens[1]);
	else if (!ft_strcmp(tokens[0], "SO") && !data->textures.so)
		data->textures.so = ft_strdup(tokens[1]);
	else if (!ft_strcmp(tokens[0], "WE") && !data->textures.we)
		data->textures.we = ft_strdup(tokens[1]);
	else if (!ft_strcmp(tokens[0], "EA") && !data->textures.ea)
		data->textures.ea = ft_strdup(tokens[1]);
	else
		result = (ft_putstr_fd(TEXTURE_ERR, 2), ERROR);
	ft_free_tab((void **)tokens, -1);
	return (result);
}

int	parse_scene_textures(t_data *data)
{
	int	i;

	i = 0;
	while (data->scene[i])
	{
		if (ft_strncmp(data->scene[i], "NO ", 3) == 0
			|| ft_strncmp(data->scene[i], "SO ", 3) == 0
			|| ft_strncmp(data->scene[i], "WE ", 3) == 0
			|| ft_strncmp(data->scene[i], "EA ", 3) == 0)
		{
			if (parse_texture(data, data->scene[i]) != SUCCESS)
				return (ERROR);
		}
		i++;
	}
	if (!data->textures.no || !data->textures.so || !data->textures.we
		|| !data->textures.ea)
		return (ft_putstr_fd(TEXTURE_ERR, 2), ERROR);
	return (SUCCESS);
}
