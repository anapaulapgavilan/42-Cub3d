/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_intersect_h.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isierra <isierra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 09:59:41 by isierra           #+#    #+#             */
/*   Updated: 2025/05/01 16:44:22 by isierra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	adjust_h_step(double angl, double *x_step)
{
	if ((unit_circle(angl, 'y') && *x_step > 0)
		|| (!unit_circle(angl, 'y') && *x_step < 0))
		*x_step *= -1;
}

double	get_h_inter(t_mlx *mlx, double angl, double *hit_x, double *hit_y)
{
	int		pixel;
	double	h_x;
	double	h_y;
	double	x_step;
	double	y_step;

	y_step = CELL_SIZE;
	x_step = CELL_SIZE / tan(angl);
	h_y = floor(mlx->ply->p_y_pix / CELL_SIZE) * CELL_SIZE;
	pixel = inter_check(angl, &h_y, &y_step, 1);
	h_x = mlx->ply->p_x_pix + (h_y - mlx->ply->p_y_pix) / tan(angl);
	adjust_h_step(angl, &x_step);
	while (wall_hit(h_x, h_y - pixel, mlx))
	{
		h_x += x_step;
		h_y += y_step;
	}
	*hit_x = h_x;
	*hit_y = h_y;
	return (sqrt(pow(h_x - mlx->ply->p_x_pix, 2)
			+ pow(h_y - mlx->ply->p_y_pix, 2)));
}

void	setup_h_intersection(t_mlx *mlx, int ray_idx, double h_inter,
		double *coords)
{
	mlx->ray[ray_idx].distance = h_inter;
	mlx->ray[ray_idx].flag = 1;
	mlx->ray[ray_idx].wall_hit_x = coords[0];
	mlx->ray[ray_idx].wall_hit_y = coords[1];
}
