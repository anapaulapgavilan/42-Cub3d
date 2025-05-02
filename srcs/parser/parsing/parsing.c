/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:00:19 by ana-pper          #+#    #+#             */
/*   Updated: 2025/03/23 12:00:21 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parsing(t_data *data)
{
	if (parse_scene_textures(data) != SUCCESS)
		return (ERROR);
	if (parse_scene_colors(data) != SUCCESS)
		return (ERROR);
	find_and_store_player_position(data);
	return (SUCCESS);
}
