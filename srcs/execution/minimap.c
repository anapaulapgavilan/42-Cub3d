/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isierra <isierra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 09:59:23 by isierra           #+#    #+#             */
/*   Updated: 2025/03/19 20:01:51 by isierra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_minimap(t_minimap *m)
{
	m->tile_size = (int)(CELL_SIZE * MINIMAP_SCALE);
	m->offset_x = MINIMAP_OFFSET_X;
	m->offset_y = MINIMAP_OFFSET_Y;
	m->color_wall = 0x444444FF;
	m->color_floor = 0xCCCCCCFF;
	m->color_player = 0xFF0000FF;
	m->player_size = m->tile_size / 2;
	m->row = 0;
	m->col = 0;
	m->start_x = 0;
	m->start_y = 0;
	m->color = 0;
	m->x = 0;
	m->y = 0;
	m->px = 0;
	m->py = 0;
}

static int	get_tile_color(t_mlx *mlx, t_minimap *m, int row, int col)
{
	size_t	line_len;

	line_len = ft_strlen(mlx->dt->map[row]);
	if (col >= (int)line_len)
		return (m->color_floor);
	if (mlx->dt->map[row][col] == '1')
		return (m->color_wall);
	return (m->color_floor);
}

static void	draw_tile(t_mlx *mlx, t_minimap *m, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < m->tile_size)
	{
		x = 0;
		while (x < m->tile_size)
		{
			my_mlx_pixel_put(mlx, m->start_x + x, m->start_y + y, color);
			x++;
		}
		y++;
	}
}

void	draw_minimap2d(t_mlx *mlx)
{
	t_minimap	m;

	init_minimap(&m);
	m.row = 0;
	while (m.row < mlx->dt->map_height)
	{
		m.col = 0;
		while (m.col < mlx->dt->map_width)
		{
			m.start_x = m.offset_x + m.col * m.tile_size;
			m.start_y = m.offset_y + m.row * m.tile_size;
			m.color = get_tile_color(mlx, &m, m.row, m.col);
			draw_tile(mlx, &m, m.color);
			m.col++;
		}
		m.row++;
	}
}

void	draw_player_on_minimap(t_mlx *mlx)
{
	t_minimap	m;

	init_minimap(&m);
	m.px = m.offset_x + (int)(mlx->ply->p_x_pix * MINIMAP_SCALE);
	m.py = m.offset_y + (int)(mlx->ply->p_y_pix * MINIMAP_SCALE);
	m.y = 0;
	while (m.y < m.player_size)
	{
		m.x = 0;
		while (m.x < m.player_size)
		{
			my_mlx_pixel_put(mlx, m.px + m.x, m.py + m.y, m.color_player);
			m.x++;
		}
		m.y++;
	}
}
