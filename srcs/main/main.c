/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 11:50:11 by ana-pper          #+#    #+#             */
/*   Updated: 2025/03/23 11:50:35 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *data)
{
	data->scene = NULL;
	data->textures.no = NULL;
	data->textures.so = NULL;
	data->textures.we = NULL;
	data->textures.ea = NULL;
	data->floor_color = -1;
	data->ceil_color = -1;
	data->map = NULL;
	data->map_width = 0;
	data->map_height = 0;
	data->map_start_line = -1;
	data->p_x = -1;
	data->p_y = -1;
}

int	validate_arguments(int argc, char **argv)
{
	int	arg_len;

	if (argc != 2)
		return (ft_putstr_fd(INVALID_NUMBER_ERR, 2), 1);
	arg_len = ft_strlen(argv[1]);
	if (arg_len < 4 || argv[1][arg_len - 1] != 'b' || argv[1][arg_len
		- 2] != 'u' || argv[1][arg_len - 3] != 'c' || argv[1][arg_len
		- 4] != '.')
		return (ft_putstr_fd(FILE_EXTENSION_ERR, 2), 1);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (validate_arguments(argc, argv))
		return (ERROR);
	init_data(&data);
	if (read_scene(&data, argv[1]) != SUCCESS)
	{
		free_data(&data);
		return (ERROR);
	}
	parsing(&data);
	execution(&data);
	free_data(&data);
	return (SUCCESS);
}
