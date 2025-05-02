/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_core.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: issierra <issierra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 09:59:41 by isierra           #+#    #+#             */
/*   Updated: 2025/03/23 11:08:48 by issierra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	unit_circle(double angle, char c)
{
	if (c == 'x')
		return (angle > 0 && angle < M_PI);
	else if (c == 'y')
		return (angle > (M_PI / 2) && angle < (3 * M_PI) / 2);
	return (0);
}

int	inter_check(double angle, double *inter, double *step, int is_horizon)
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += CELL_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
		{
			*inter += CELL_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int	wall_hit(double x, double y, t_mlx *mlx)
{
	int	x_m;
	int	y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor(x / CELL_SIZE);
	y_m = floor(y / CELL_SIZE);
	if (y_m >= mlx->dt->map_height || x_m >= mlx->dt->map_width || y_m < 0
		|| x_m < 0)
		return (0);
	if (x_m >= (int)ft_strlen(mlx->dt->map[y_m]))
		return (0);
	if (mlx->dt->map[y_m][x_m] == '1')
		return (0);
	return (1);
}

void	cast_single_ray(t_mlx *mlx, int i, double angle)
{
	double	h_inter;
	double	v_inter;
	double	h_coords[2];
	double	v_coords[2];

	mlx->ray[i].index = i;
	mlx->ray[i].ray_ngl = nor_angle(angle);
	h_inter = get_h_inter(mlx, mlx->ray[i].ray_ngl, &h_coords[0], &h_coords[1]);
	v_inter = get_v_inter(mlx, mlx->ray[i].ray_ngl, &v_coords[0], &v_coords[1]);
	if (v_inter <= h_inter)
		setup_v_intersection(mlx, i, v_inter, v_coords);
	else
		setup_h_intersection(mlx, i, h_inter, h_coords);
}

void	cast_rays(t_mlx *mlx)
{
	double	start_angle;
	int		ray_i;

	start_angle = mlx->ply->p_ang - (mlx->ply->fov_rd / 2.0);
	ray_i = 0;
	while (ray_i < WIDTH)
	{
		cast_single_ray(mlx, ray_i, start_angle);
		start_angle += (mlx->ply->fov_rd / (double)WIDTH);
		ray_i++;
	}
}
