/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isierra <isierra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 09:59:54 by isierra           #+#    #+#             */
/*   Updated: 2025/03/22 11:14:19 by isierra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	if (x < 0)
		return ;
	else if (x >= WIDTH)
		return ;
	if (y < 0)
		return ;
	else if (y >= HEIGHT)
		return ;
	mlx_put_pixel(mlx->img, x, y, color);
}

double	nor_angle(double angle)
{
	while (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	while (angle < 0)
		angle += (2 * M_PI);
	return (angle);
}

void	draw_floor_ceiling(t_mlx *mlx, int ray, int t_pix, int b_pix)
{
	int	i;
	int	floor_color;
	int	ceil_color;

	floor_color = mlx->dt->floor_color;
	ceil_color = mlx->dt->ceil_color;
	i = b_pix;
	while (i < HEIGHT)
		my_mlx_pixel_put(mlx, ray, i++, floor_color);
	i = 0;
	while (i < t_pix)
		my_mlx_pixel_put(mlx, ray, i++, ceil_color);
}
