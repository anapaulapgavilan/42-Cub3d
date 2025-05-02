/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_identifiers_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 13:11:18 by ana-pper          #+#    #+#             */
/*   Updated: 2025/03/23 13:23:52 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map_line(char *line)
{
	while (*line)
	{
		if (!ft_strchr("01NSEW ", *line))
			return (0);
		line++;
	}
	return (1);
}

int	process_identifier_line(char *line, t_identifiers *found)
{
	if (ft_strnstr(line, "NO", ft_strlen(line)))
		found->no = 1;
	else if (ft_strnstr(line, "SO", ft_strlen(line)))
		found->so = 1;
	else if (ft_strnstr(line, "WE", ft_strlen(line)))
		found->we = 1;
	else if (ft_strnstr(line, "EA", ft_strlen(line)))
		found->ea = 1;
	else if (ft_strnstr(line, "F", ft_strlen(line)))
		found->f = 1;
	else if (ft_strnstr(line, "C", ft_strlen(line)))
		found->c = 1;
	return (SUCCESS);
}

int	handle_map_line(char *line, int *map_started, t_identifiers *found)
{
	if (!(*map_started))
	{
		*map_started = 1;
		if (!found->no || !found->so || !found->we || !found->ea || !found->f
			|| !found->c)
		{
			ft_putstr_fd(MISSING_ID_ERR, 2);
			free(line);
			return (ERROR);
		}
	}
	free(line);
	return (SUCCESS);
}

int	check_unique_counts(t_identifiers *found)
{
	if (found->no != 1 || found->so != 1 || found->we != 1 || found->ea != 1
		|| found->f != 1 || found->c != 1)
	{
		ft_putstr_fd(FORMAT_ID_ERR, 2);
		return (ERROR);
	}
	return (SUCCESS);
}

int	check_map_or_empty(char *line, int *found_map)
{
	if (line[0] == '\0')
	{
		free(line);
		return (1);
	}
	if (is_map_line(line))
	{
		*found_map = 1;
		free(line);
		return (1);
	}
	return (0);
}
