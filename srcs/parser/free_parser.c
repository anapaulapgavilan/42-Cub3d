/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:14:36 by ana-pper          #+#    #+#             */
/*   Updated: 2025/03/23 14:14:37 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_tab(void **tab, int n)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	if (n != -1)
	{
		while (i < n)
		{
			free(tab[i]);
			tab[i++] = NULL;
		}
	}
	else
	{
		while (tab[i])
		{
			free(tab[i]);
			tab[i++] = NULL;
		}
	}
	free(tab);
	tab = NULL;
}

void	free_scene(char **scene)
{
	int	i;

	if (!scene)
		return ;
	i = 0;
	while (scene[i])
	{
		free(scene[i]);
		i++;
	}
	free(scene);
	scene = NULL;
}

void	free_textures(t_texture *textures)
{
	if (textures->no)
		free(textures->no);
	if (textures->so)
		free(textures->so);
	if (textures->we)
		free(textures->we);
	if (textures->ea)
		free(textures->ea);
}

void	free_map_parser(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_data(t_data *data)
{
	int	i;

	if (data->scene)
	{
		i = 0;
		while (data->scene[i])
		{
			free(data->scene[i]);
			i++;
		}
		free(data->scene);
		data->scene = NULL;
	}
	free_textures(&data->textures);
	free_map_parser(data->map);
}
