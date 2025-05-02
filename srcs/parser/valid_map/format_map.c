/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 13:58:33 by ana-pper          #+#    #+#             */
/*   Updated: 2025/03/23 13:59:22 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*format_map_line(const char *line)
{
	char	*copy;
	size_t	len;

	copy = ft_strdup(line);
	if (!copy)
		return (NULL);
	len = ft_strlen(copy);
	if (len > 0 && copy[len - 1] == '\n')
		copy[len - 1] = '\0';
	return (copy);
}

void	format_map_spaces(t_data *data)
{
	int		i;
	char	*formatted_line;

	i = 0;
	while (data->map[i])
	{
		formatted_line = format_map_line(data->map[i]);
		if (!formatted_line)
		{
			ft_putstr_fd(MEMORY_ERR, 2);
			exit(ERROR);
		}
		free(data->map[i]);
		data->map[i] = formatted_line;
		i++;
	}
}
