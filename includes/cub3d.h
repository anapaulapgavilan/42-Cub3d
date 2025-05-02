/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isierra <isierra@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:20:06 by ana-pper          #+#    #+#             */
/*   Updated: 2025/05/01 16:42:50 by isierra          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/includes/libft.h"
# include <../lib/MLX42/MLX42.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define INVALID_NUMBER_ERR "Error: Invalid Number of Arguments\n"
# define FILE_EXTENSION_ERR "Error: Invalid File Extension\n"
# define SCENE_FILE_ERR "Error: Error Reading File\n"
# define IS_EMPTY_ERR "Error: File is Empty\n"
# define SCENE_ERR "Error: Invalid Scene\n"
# define MEMORY_ERR "Error: Memory allocation failed\n"
# define DUPLICATE_ID_ERR "Error: Duplicate identifiers found in .cub file\n"
# define MISSING_ID_ERR "Error: Missing identifiers in .cub file\n"
# define TEXT_FILE_ERR "Error: Texture file not found\n"
# define COLOR_FORMAT_ERR "Error: Invalid color format\n"
# define INVALID_RGB_ERR "Error: Invalid RGB values\n"
# define EXTENSION_ERR "Error: Texture file must have .png extension\n"
# define INVALID_ID_ERR "Error: Invalid identifier or unexpected character: "
# define INVALID_MAP_LINE_ERR "Error: Invalid map line: "
# define UKNOWN_ID_ERR "Error: Unknown identifier found: "
# define FORMAT_ID_ERR "Error: Identifiers in .cub file are not formatted\n"
# define INVALID_CHAR_ERR "Error: Invalid character in map.\n"
# define PLAYER_POS_ERR "Error: Map must contain exactly one player position.\n"
# define ENCOLSE_MAP_ERR "Error: Map must be properly enclosed.\n"
# define MAP_MISSING_ERR "Error: Map is missing.\n"
# define MAP_MEASURE_ERR "Error: Map width or height is zero.\n"
# define MAP_DISCONECTED_ERR "Error: Map has disconnected areas.\n"
# define PLAYER_TRAPPED_ERR "Error: Player is completely trapped.\n"
# define PLAYER_PATH_ERR "Error: Player has no valid path.\n"
# define INVALID_COLORS_ERR "Error: RGB values must be between 0-255.\n"
# define MLX_INIT_ERR "Error: Error Initializinf MLX42\n"
# define IMAGE_ERR "Error: Error creating main image\n"
# define TEXTURE_ERR "Error: Error loading texture\n"

# define ERROR 1
# define SUCCESS 0
# define BUFFER_SIZE 42
# define WIDTH 612
# define HEIGHT 512
# define CELL_SIZE 20
# define FOV 60
# define ROTATION_SPEED 0.045
# define PLAYER_SPEED 4
# define MINIMAP_SCALE 0.2
# define MINIMAP_OFFSET_X 10
# define MINIMAP_OFFSET_Y 10
# define PROGRAM_NAME "Cub3D"

typedef struct s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct s_dim
{
	int				width;
	int				height;
}					t_dim;

typedef struct s_texture
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	mlx_texture_t	*n_tex;
	mlx_texture_t	*s_tex;
	mlx_texture_t	*e_tex;
	mlx_texture_t	*w_tex;
}					t_texture;

typedef struct s_data
{
	char			**scene;
	t_texture		textures;
	int				floor_color;
	int				ceil_color;
	char			**map;
	int				map_width;
	int				map_height;
	int				map_start_line;

	int				p_x;
	int				p_y;
	char			p_orientation;

}					t_data;

typedef struct s_identifiers
{
	int				no;
	int				so;
	int				we;
	int				ea;
	int				f;
	int				c;
}					t_identifiers;

typedef struct s_ray
{
	int				index;
	double			ray_ngl;
	double			distance;
	int				flag;
	double			wall_hit_x;
	double			wall_hit_y;
}					t_ray;

typedef struct s_player
{
	double			p_x_pix;
	double			p_y_pix;
	double			p_ang;
	double			fov_rd;
}					t_player;

typedef struct s_mlx
{
	mlx_image_t		*img;
	mlx_t			*mlx_p;
	t_data			*dt;
	t_player		*ply;
	t_ray			*ray;
	t_texture		*txt;
}					t_mlx;

typedef struct s_wallinfo
{
	int				ray;
	int				top;
	int				bottom;
	int				line_height;
	mlx_texture_t	*texture;
	unsigned int	tex_x;
	unsigned int	tex_y;
	unsigned int	pixel_pos;
	uint32_t		color;
}					t_wallinfo;

typedef struct s_minimap
{
	int				tile_size;
	int				offset_x;
	int				offset_y;
	uint32_t		color_wall;
	uint32_t		color_floor;
	uint32_t		color_player;
	int				player_size;
	int				row;
	int				col;
	int				start_x;
	int				start_y;
	uint32_t		color;
	int				y;
	int				x;
	double			px;
	double			py;
}					t_minimap;

// Parser
int					read_scene(t_data *data, char *file);
char				*get_next_line(int fd);
void				check_valid_scene(t_data *data);
int					validate_texture_and_colors(t_data *data);
int					validate_identifier_order(t_data *data);
int					validate_unique_identifiers(t_data *data);
int					is_map_line(char *line);
int					validate_allowed_characters(t_data *data);
int					validate_unknown_identifiers(t_data *data);
int					validate_map(t_data *data);
void				extract_map(t_data *data);
void				format_map_spaces(t_data *data);
char				*format_map_line(const char *line);
int					validate_map_connectivity(t_data *data);
int					find_player_position(t_data *data, int *px, int *py);
int					parse_scene_textures(t_data *data);
int					parse_scene_colors(t_data *data);
int					find_and_store_player_position(t_data *data);
int					parsing(t_data *data);
int					ft_array_size(char **array);
void				ft_strdel(char **str);
void				copy_str(char *dest, const char *src, int *i);
int					is_new_line(char *str);
int					validate_rgb_format(const char *rgb_str);
int					validate_rgb_components(char **values);
int					is_valid_number(const char *str);
char				*ft_strldup(const char *src, int max_width, char pad);
char				*ft_strreplace_all(const char *str, const char *to_remove);
char				*ft_strjoin_three(const char *s1, const char *s2,
						const char *s3);
int					is_valid_identifier(const char *line);
int					is_valid_map_line(const char *line);
int					print_error_and_free(char *line, char *error_msg);
int					is_map_line(char *line);
int					process_identifier_line(char *line, t_identifiers *found);
int					handle_map_line(char *line, int *map_started,
						t_identifiers *found);
int					check_unique_counts(t_identifiers *found);
int					check_map_or_empty(char *line, int *found_map);
int					find_player_position(t_data *data, int *px, int *py);
int					is_player_trapped(t_data *data, int px, int py);
int					check_valid_chars(t_data *data);

// Memory Management
void				free_data(t_data *data);
void				free_map_parser(char **map);
void				ft_free_tab(void **tab, int n);
char				*ft_strldup(const char *src, int max_width, char pad);

// Execution
int					execution(t_data *data);
void				get_angle(t_mlx *mlx);
void				free_map(t_data *dt);
void				myexit(t_mlx *mlx);
void				handle_keypress(mlx_key_data_t keydata, void *param);
void				cast_rays(t_mlx *mlx);
void				cast_single_ray(t_mlx *mlx, int i, double angle);
int					unit_circle(double angle, char c);
int					inter_check(double angle, double *inter, double *step,
						int is_Horizon);
int					wall_hit(double x, double y, t_mlx *mlx);
double				get_h_inter(t_mlx *mlx, double angl, double *hit_x,
						double *hit_y);
void				setup_h_intersection(t_mlx *mlx, int ray_idx,
						double h_inter, double *coords);
double				get_v_inter(t_mlx *mlx, double angl, double *hit_x,
						double *hit_y);
void				setup_v_intersection(t_mlx *mlx, int ray_idx,
						double v_inter, double *coords);
void				render_scene(t_mlx *mlx);
void				my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
double				nor_angle(double angle);
void				draw_floor_ceiling(t_mlx *mlx, int ray, int t_pix,
						int b_pix);
void				load_textures(t_mlx *mlx);
void				draw_wall_with_texture(t_mlx *mlx, t_wallinfo w);
void				free_textures_mlx(t_mlx *mlx);
void				draw_player_on_minimap(t_mlx *mlx);
void				draw_minimap2d(t_mlx *mlx);

#endif
