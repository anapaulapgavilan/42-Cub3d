/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isierra <isierra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 09:59:41 by isierra           #+#    #+#             */
/*   Updated: 2025/04/06 10:57:23 by isierra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	select_texture(t_mlx *mlx, t_wallinfo *w, int ray_idx)
{
	if (mlx->ray[ray_idx].flag == 0)
	{
		if (mlx->ray[ray_idx].ray_ngl > M_PI / 2
			&& mlx->ray[ray_idx].ray_ngl < 3 * M_PI / 2)
			w->texture = mlx->txt->w_tex;
		else
			w->texture = mlx->txt->e_tex;
	}
	else
	{
		if (mlx->ray[ray_idx].ray_ngl > 0
			&& mlx->ray[ray_idx].ray_ngl < M_PI)
			w->texture = mlx->txt->s_tex;
		else
			w->texture = mlx->txt->n_tex;
	}
}

static void	calc_wall_height(t_mlx *mlx, int ray_idx, t_wallinfo *w)
{
	double	correct_dist;
	double	wall_height;

	correct_dist = mlx->ray[ray_idx].distance
		* cos(nor_angle(mlx->ray[ray_idx].ray_ngl - mlx->ply->p_ang));
	wall_height = (CELL_SIZE / correct_dist) * ((WIDTH / 2.0)
			/ tan(mlx->ply->fov_rd / 2.0));
	w->ray = ray_idx;
	w->bottom = (int)((HEIGHT / 2.0) + (wall_height / 2.0));
	w->top = (int)((HEIGHT / 2.0) - (wall_height / 2.0));
}

void	render_scene(t_mlx *mlx)
{
	t_wallinfo	w;
	int			ray;

	ray = 0;
	while (ray < WIDTH)
	{
		calc_wall_height(mlx, ray, &w);
		select_texture(mlx, &w, ray);
		draw_wall_with_texture(mlx, w);
		draw_floor_ceiling(mlx, w.ray, w.top, w.bottom);
		ray++;
	}
}
