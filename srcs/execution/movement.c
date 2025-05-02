/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isierra <isierra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 09:59:32 by isierra           #+#    #+#             */
/*   Updated: 2025/05/01 19:07:20 by isierra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_exit(mlx_key_data_t keydata, t_mlx *mlx)
{
	if (keydata.key == MLX_KEY_ESCAPE && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
	{
		myexit(mlx);
	}
}

static void	calculate_movement(mlx_key_data_t keydata, t_mlx *mlx,
		double *next_x_pix, double *next_y_pix)
{
	double	ang;

	ang = mlx->ply->p_ang;
	if (keydata.key == MLX_KEY_W)
	{
		*next_x_pix += cos(ang) * PLAYER_SPEED;
		*next_y_pix += sin(ang) * PLAYER_SPEED;
	}
	else if (keydata.key == MLX_KEY_S)
	{
		*next_x_pix -= cos(ang) * PLAYER_SPEED;
		*next_y_pix -= sin(ang) * PLAYER_SPEED;
	}
	else if (keydata.key == MLX_KEY_A)
	{
		*next_x_pix += cos(ang - M_PI_2) * PLAYER_SPEED;
		*next_y_pix += sin(ang - M_PI_2) * PLAYER_SPEED;
	}
	else if (keydata.key == MLX_KEY_D)
	{
		*next_x_pix += cos(ang + M_PI_2) * PLAYER_SPEED;
		*next_y_pix += sin(ang + M_PI_2) * PLAYER_SPEED;
	}
}

static void	handle_rotation(mlx_key_data_t keydata, t_mlx *mlx)
{
	if (keydata.key == MLX_KEY_LEFT)
		mlx->ply->p_ang -= ROTATION_SPEED;
	else if (keydata.key == MLX_KEY_RIGHT)
		mlx->ply->p_ang += ROTATION_SPEED;
	if (mlx->ply->p_ang < 0)
		mlx->ply->p_ang += 2 * M_PI;
	else if (mlx->ply->p_ang > 2 * M_PI)
		mlx->ply->p_ang -= 2 * M_PI;
}

static void	check_collision_and_update(t_mlx *mlx, double next_x_pix,
		double next_y_pix)
{
	int	cell_x;
	int	cell_y;

	cell_x = (int)(next_x_pix / CELL_SIZE);
	cell_y = (int)(next_y_pix / CELL_SIZE);
	if (cell_x >= 0 && cell_x < mlx->dt->map_width && cell_y >= 0
		&& cell_y < mlx->dt->map_height && mlx->dt->map[cell_y][cell_x] != '1')
	{
		mlx->ply->p_x_pix = next_x_pix;
		mlx->ply->p_y_pix = next_y_pix;
		mlx->dt->p_x = cell_x;
		mlx->dt->p_y = cell_y;
	}
}

void	handle_keypress(mlx_key_data_t keydata, void *param)
{
	t_mlx	*mlx;
	double	next_x_pix;
	double	next_y_pix;

	mlx = (t_mlx *)param;
	next_x_pix = mlx->ply->p_x_pix;
	next_y_pix = mlx->ply->p_y_pix;
	handle_exit(keydata, mlx);
	calculate_movement(keydata, mlx, &next_x_pix, &next_y_pix);
	handle_rotation(keydata, mlx);
	check_collision_and_update(mlx, next_x_pix, next_y_pix);
}
