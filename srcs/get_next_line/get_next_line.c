/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 11:34:48 by ana-pper          #+#    #+#             */
/*   Updated: 2025/03/23 11:48:49 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*conc_strings(char *str, char *buffer)
{
	char	*new_str;
	int		str_len;
	int		buffer_len;
	int		i;

	i = 0;
	if (!buffer)
		return (NULL);
	if (str)
		str_len = ft_strlen(str);
	else
		str_len = 0;
	buffer_len = ft_strlen(buffer);
	new_str = malloc((str_len + buffer_len + 1) * sizeof(char));
	if (!new_str)
	{
		free(str);
		return (NULL);
	}
	if (str)
		copy_str(new_str, str, &i);
	copy_str(new_str, buffer, &i);
	new_str[i] = '\0';
	free(str);
	return (new_str);
}

static char	*delete_first_chars(char *str, int n)
{
	char	*new_str;
	int		len;
	int		i;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (n >= len)
	{
		free(str);
		return (NULL);
	}
	new_str = malloc((len - n + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len - n)
	{
		new_str[i] = str[n + i];
		i++;
	}
	new_str[i] = '\0';
	free(str);
	return (new_str);
}

static char	*select_line(char **strptr)
{
	char	*selected_line;
	char	*str;
	int		i;
	int		len;

	if (!strptr || !(*strptr))
		return (NULL);
	str = *strptr;
	len = is_new_line(str);
	if (!len)
		len = ft_strlen(str);
	selected_line = malloc((len + 1) * sizeof(char));
	if (!selected_line)
		return (NULL);
	i = -1;
	while (str[++i] && str[i] != '\n')
		selected_line[i] = str[i];
	if (str[i] == '\n')
		selected_line[i++] = '\n';
	selected_line[i] = '\0';
	*strptr = delete_first_chars(*strptr, i);
	if (!(*strptr))
		*strptr = NULL;
	return (selected_line);
}

static int	read_to_str(int fd, char **str)
{
	char	*buffer;
	int		ret;
	char	*temp;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (-1);
	while (!is_new_line(*str))
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret <= 0)
			break ;
		buffer[ret] = '\0';
		temp = conc_strings(*str, buffer);
		if (!temp)
		{
			free(buffer);
			ft_strdel(str);
			return (-1);
		}
		*str = temp;
	}
	free(buffer);
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*str = NULL;
	char		*line;

	read_to_str(fd, &str);
	if (!str || *str == '\0')
	{
		ft_strdel(&str);
		return (NULL);
	}
	line = select_line(&str);
	return (line);
}
