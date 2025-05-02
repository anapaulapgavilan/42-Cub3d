/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isierra <isierra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 08:05:12 by isierra           #+#    #+#             */
/*   Updated: 2025/05/01 16:43:54 by isierra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_textures_mlx(t_mlx *mlx)
{
	if (mlx->txt)
	{
		if (mlx->txt->n_tex)
			mlx_delete_texture(mlx->txt->n_tex);
		if (mlx->txt->s_tex)
			mlx_delete_texture(mlx->txt->s_tex);
		if (mlx->txt->e_tex)
			mlx_delete_texture(mlx->txt->e_tex);
		if (mlx->txt->w_tex)
			mlx_delete_texture(mlx->txt->w_tex);
		free(mlx->txt);
	}
}

void	load_textures(t_mlx *mlx)
{
	mlx->txt->n_tex = mlx_load_png(mlx->dt->textures.no);
	mlx->txt->s_tex = mlx_load_png(mlx->dt->textures.so);
	mlx->txt->e_tex = mlx_load_png(mlx->dt->textures.ea);
	mlx->txt->w_tex = mlx_load_png(mlx->dt->textures.we);
	if (!mlx->txt->n_tex || !mlx->txt->s_tex || !mlx->txt->e_tex
		|| !mlx->txt->w_tex)
	{
		printf(TEXTURE_ERR);
		myexit(mlx);
	}
}

static int	compute_tex_x(t_mlx *mlx, int ray, mlx_texture_t *texture)
{
	int		tex_x;
	double	offset_in_cell;
	double	hit_coord;

	if (mlx->ray[ray].flag == 1)
		hit_coord = mlx->ray[ray].wall_hit_x;
	else
		hit_coord = mlx->ray[ray].wall_hit_y;
	offset_in_cell = fmod(hit_coord, CELL_SIZE) / CELL_SIZE;
	tex_x = (int)(offset_in_cell * texture->width);
	if ((mlx->ray[ray].flag == 0 && mlx->ray[ray].ray_ngl > M_PI / 2
			&& mlx->ray[ray].ray_ngl < 3 * M_PI / 2) || (mlx->ray[ray].flag == 1
			&& (mlx->ray[ray].ray_ngl < M_PI || mlx->ray[ray].ray_ngl < 0)))
		tex_x = (int)texture->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	else if (tex_x >= (int)texture->width)
		tex_x = (int)texture->width - 1;
	return (tex_x);
}

void	draw_wall_with_texture(t_mlx *mlx, t_wallinfo w)
{
	int				y;
	int				d;

	w.tex_x = compute_tex_x(mlx, w.ray, w.texture);
	y = w.top;
	w.line_height = w.bottom - w.top;
	while (y < w.bottom)
	{
		d = y - (HEIGHT / 2) + (w.line_height / 2);
		w.tex_y = (d * w.texture->height) / w.line_height;
		if (w.tex_y >= w.texture->height)
			w.tex_y = w.texture->height - 1;
		w.pixel_pos = (w.tex_y * w.texture->width + w.tex_x) * 4;
		if (w.pixel_pos + 3 < w.texture->width * w.texture->height * 4)
		{
			w.color = (w.texture->pixels[w.pixel_pos
					+ 0] << 24) | (w.texture->pixels[w.pixel_pos
					+ 1] << 16) | (w.texture->pixels[w.pixel_pos
					+ 2] << 8) | (w.texture->pixels[w.pixel_pos + 3]);
			my_mlx_pixel_put(mlx, w.ray, y, w.color);
		}
		y++;
	}
}
