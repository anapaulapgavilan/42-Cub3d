/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isierra <isierra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 09:59:08 by isierra           #+#    #+#             */
/*   Updated: 2025/04/06 10:29:50 by isierra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_data *dt)
{
	int	i;

	i = 0;
	while (i < dt->map_height)
	{
		free(dt->map[i]);
		i++;
	}
	free(dt->map);
}

void	myexit(t_mlx *mlx)
{
	free_map(mlx->dt);
	free_textures_mlx(mlx);
	mlx_delete_image(mlx->mlx_p, mlx->img);
	mlx_close_window(mlx->mlx_p);
	mlx_terminate(mlx->mlx_p);
	free(mlx->ply);
	free(mlx->ray);
	exit(EXIT_SUCCESS);
}

void	get_angle(t_mlx *mlx)
{
	char	c;

	c = mlx->dt->map[mlx->dt->p_y][mlx->dt->p_x];
	if (c == 'N')
		mlx->ply->p_ang = 3 * M_PI / 2;
	if (c == 'S')
		mlx->ply->p_ang = M_PI / 2;
	if (c == 'E')
		mlx->ply->p_ang = 0;
	if (c == 'W')
		mlx->ply->p_ang = M_PI;
	mlx->ply->p_x_pix = (mlx->dt->p_x * CELL_SIZE) + CELL_SIZE / 2;
	mlx->ply->p_y_pix = (mlx->dt->p_y * CELL_SIZE) + CELL_SIZE / 2;
	mlx->ply->fov_rd = FOV * M_PI / 180;
}

static void	render_frame(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	cast_rays(mlx);
	render_scene(mlx);
	draw_minimap2d(mlx);
	draw_player_on_minimap(mlx);
	mlx_image_to_window(mlx->mlx_p, mlx->img, 0, 0);
}

int	execution(t_data *data)
{
	t_mlx	mlx;

	mlx.dt = data;
	mlx.ply = (t_player *)ft_calloc(sizeof(t_player), 1);
	mlx.ray = (t_ray *)ft_calloc(WIDTH, sizeof(t_ray));
	mlx.txt = (t_texture *)ft_calloc(sizeof(t_texture), 1);
	mlx.mlx_p = mlx_init(WIDTH, HEIGHT, PROGRAM_NAME, false);
	if (!mlx.mlx_p)
		return (printf(MLX_INIT_ERR), EXIT_FAILURE);
	get_angle(&mlx);
	mlx.img = mlx_new_image(mlx.mlx_p, WIDTH, HEIGHT);
	if (!mlx.img)
	{
		mlx_terminate(mlx.mlx_p);
		return (printf(IMAGE_ERR), EXIT_FAILURE);
	}
	load_textures(&mlx);
	mlx_key_hook(mlx.mlx_p, handle_keypress, &mlx);
	mlx_loop_hook(mlx.mlx_p, render_frame, &mlx);
	mlx_loop(mlx.mlx_p);
	myexit(&mlx);
	return (EXIT_SUCCESS);
}
