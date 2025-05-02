/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_identifiers_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-pper <ana-pper@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 12:17:51 by ana-pper          #+#    #+#             */
/*   Updated: 2025/03/23 12:42:32 by ana-pper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_rgb_format(const char *rgb_str)
{
	char	**values;
	int		ret;

	values = ft_split(rgb_str, ',');
	if (!values || !values[0] || !values[1] || !values[2] || values[3])
	{
		ft_free_tab((void **)values, -1);
		return (ERROR);
	}
	ret = validate_rgb_components(values);
	ft_free_tab((void **)values, -1);
	return (ret);
}

int	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strldup(const char *src, int max_width, char pad)
{
	int		i;
	int		len;
	char	*dup;

	i = 0;
	len = ft_strlen(src);
	dup = malloc(max_width + 1);
	if (!dup)
		return (NULL);
	while (i < len && i < max_width)
	{
		dup[i] = src[i];
		i++;
	}
	while (i < max_width)
	{
		dup[i] = pad;
		i++;
	}
	dup[max_width] = '\0';
	return (dup);
}

char	*ft_strreplace_all(const char *str, const char *to_remove)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = malloc(ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (!ft_strchr(to_remove, str[i]))
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*ft_strjoin_three(const char *s1, const char *s2, const char *s3)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(s1, s2);
	result = ft_strjoin(temp, s3);
	free(temp);
	return (result);
}
