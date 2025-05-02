/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_intersect_v.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isierra <isierra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 09:59:41 by isierra           #+#    #+#             */
/*   Updated: 2025/05/01 16:44:34 by isierra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	adjust_v_step(double angl, double *y_step)
{
	if ((unit_circle(angl, 'x') && *y_step < 0)
		|| (!unit_circle(angl, 'x') && *y_step > 0))
		*y_step *= -1;
}

double	get_v_inter(t_mlx *mlx, double angl, double *hit_x, double *hit_y)
{
	int		pixel;
	double	v_x;
	double	v_y;
	double	x_step;
	double	y_step;

	x_step = CELL_SIZE;
	y_step = CELL_SIZE * tan(angl);
	v_x = floor(mlx->ply->p_x_pix / CELL_SIZE) * CELL_SIZE;
	pixel = inter_check(angl, &v_x, &x_step, 0);
	v_y = mlx->ply->p_y_pix + (v_x - mlx->ply->p_x_pix) * tan(angl);
	adjust_v_step(angl, &y_step);
	while (wall_hit(v_x - pixel, v_y, mlx))
	{
		v_x += x_step;
		v_y += y_step;
	}
	*hit_x = v_x;
	*hit_y = v_y;
	return (sqrt(pow(v_x - mlx->ply->p_x_pix, 2)
			+ pow(v_y - mlx->ply->p_y_pix, 2)));
}

void	setup_v_intersection(t_mlx *mlx, int ray_idx, double v_inter,
		double *coords)
{
	mlx->ray[ray_idx].distance = v_inter;
	mlx->ray[ray_idx].flag = 0;
	mlx->ray[ray_idx].wall_hit_x = coords[0];
	mlx->ray[ray_idx].wall_hit_y = coords[1];
}
