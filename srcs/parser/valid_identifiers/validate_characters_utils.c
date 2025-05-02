/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_characters_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:53:50 by ana-pper          #+#    #+#             */
/*   Updated: 2025/03/23 12:55:42 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_identifier(const char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0);
}

int	is_valid_map_line(const char *line)
{
	while (*line)
	{
		if (!ft_strchr("01NSEW ", *line))
			return (0);
		line++;
	}
	return (1);
}

int	print_error_and_free(char *line, char *error_msg)
{
	ft_putstr_fd(error_msg, 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd("\n", 2);
	free(line);
	return (ERROR);
}
