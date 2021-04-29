/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 09:31:25 by stribuzi          #+#    #+#             */
/*   Updated: 2021/04/29 15:01:56 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>
# include <stdlib.h>
# include "get_next_line.h"
# include "../mlx/mlx.h"

typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct s_found
{
	int				res_found;
	int				east_found;
	int				south_found;
	int				north_found;
	int				west_found;
	int				sprite_found;
	int				floor_found;
	int				ceiling_found;
	int				spawn_pos;
	int				**sprites;
}					t_found;

typedef struct s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct s_texture
{
	void			*image;
	int				endian;
	int				size_line;
	int				bits_per_pixel;
	int				width;
	int				height;
	unsigned int	*mlx_get_data;
}					t_tex;

typedef struct s_sprite
{
	double			sprite_x;
	double			sprite_y;
	double			inv_det;
	double			transform_x;
	double			transform_y;
	int				sprite_screen_x;
	int				sprite_height;
	int				draw_start_y;
	int				draw_end_y;
	int				sprite_width;
	int				draw_start_x;
	int				draw_end_x;
	int				tex_x;
	int				tex_y;
	int				distance;
	int				position;
	t_tex			sprite_texture;
	t_color			color_struct;
}					t_sprite;

typedef struct s_floor
{
	float			ray_dir_x_0;
	float			ray_dir_y_0;
	float			ray_dir_x_1;
	float			ray_dir_y_1;
	float			row_distance;
	float			floor_step_x;
	float			floor_step_y;
	float			floor_x;
	float			floor_y;
	int				y;
	int				x;
	int				color;
	t_color			color_floor;
	int				pos;
	float			pos_z;
	int				cell_x;
	int				cell_y;
	int				tx;
	int				ty;
	int				position;
	t_tex			ceiling_texture;
}					t_floor;

typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	float			move_speed;
	float			rotation_speed;
	double			plane_x;
	double			plane_y;
	double			dir_x;
	double			dir_y;
	double			ray_dir_x;
	double			ray_dir_y;
	double			camera_x;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	int				tex_x;
	int				tex_y;
	double			wall_x;
	double			step;
	double			tex_pos;
	double			perpendicular_wall_dist;
	int				side;
	int				step_x;
	int				step_y;
	int				line_height;
	int				draw_start;
	int				draw_end;
	t_color			color_struct;
	int				num_secret_doors;
	char			initial_direction;
	int				scope_preference;
	int				weapon_preference;
	int				spawn_pos;
}					t_player;

typedef struct s_p
{
	void			*mlx;
	void			*window;
	int				screen_width;
	int				screen_height;
	int				floor_color;
	int				ceiling_color;
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
	char			*sprite_texture;
	char			**map;
	int				num_of_sprites;
	int				**sprites;
	int				map_height;
	int				*z_buffer;
	int				mac_screen_width;
	int				mac_screen_height;
	int				do_screenshot;
	t_data			img;
	t_tex			texture;
	t_tex			texture_north;
	t_tex			texture_south;
	t_tex			texture_east;
	t_tex			texture_west;
	t_player		player;
	t_sprite		sprite;
	t_floor			ceiling_data;
	char			*life_bar;
	int				life;
	int				show_intro;
	int				w_on;
	int				s_on;
	int				d_on;
	int				a_on;
	int				right_arrow;
	int				left_arrow;
	t_found			found;
	unsigned char	*pixels;
	int				*sprite_order;
	double			*sprite_distance;
	int				map_started;
}					t_p;

int					ft_strcmp(char *s1, char *s2);
int					is_number(char c);
int					is_space(char c);
int					ft_isprint(int c);
char				*ft_strcpy(char *dst, char *src);
int					render_next_frame(t_p *p);
void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
int					color_to_int (int red, int green, int blue);
float				deg_to_rad(float deg);
int					is_wall(char c);
int					is_spawn_position(char c);
void				*ft_memset(void *str, int c, size_t n);
int					write_screenshot(t_p *p, unsigned char *pixels);
unsigned char		*create_bitmap_file_header (int height, int stride);
unsigned char		*create_bitmap_info_header (int height, int width);
t_color				int_to_rgb(int color);
void				ft_bzero(void *s, size_t n);
int					check_first_line(t_p *p, char *line);
void				throw_error(t_p *p, char *error);
void				sprite_support(t_p *p, int i);
void				sprite_support_2(t_p *p, int y,
						unsigned char *pixels);
void				draw_sprites(t_p *p, unsigned char *pixels);
void				show_warning(t_p *p);
void				draw_background(t_p *p, int color);
t_player			init(t_player player);
t_p					initialize_general(t_p *p);
int					close_program(t_p *p);
int					move(int key_pressed, t_p *p);
int					check_hidden_doors(int key_pressed, t_p *p);
int					mouse_handler(int button, int x, int y, t_p *p);
char				*ft_strdup_life(t_p *p);
void				draw_background_general(t_p *p, t_data img, int color);
void				red_button(t_p *p);
void				choose_scope(int key_pressed, t_p *p);
void				render_show_extras(t_p *p);
int					show_intro(t_p *p);
int					finished_level(t_p *p);
int					die(t_p *p);
int					key_press(int key_pressed, t_p *p);
int					key_release(int key_pressed, t_p *p);
int					key_update(t_p *p);
unsigned char		*draw_floor_and_ceiling(t_p *p, unsigned char *pixels);
void				render_support_1(t_p *p, int x);
void				render_support_2(t_p *p);
void				calculate_wall_hit(t_p *p);
void				calculate_wall_pos(t_p *p, int x);
unsigned char		*while_player_draw(t_p *p, unsigned char *pixels, int x);
void				bubble_sort_trid(t_p *p, double *sprite_distance);
void				sort_trid(t_p *p, double *sprite_distance);
void				set_textures(t_p *p);
void				set_sprite_texture(t_p *p);
void				initialize_floor_texture(t_p *p);
t_p					parse_info(char *path, t_p *p);
int					is_printable(int c);
void				mini_atoi(int *res, int *i, char *line);
void				move_right(t_p *p);
void				move_left(t_p *p);
void				key_set(t_p *p);
void				look_left(t_p *p);
void				look_right(t_p *p);
void				go_forward(t_p *p);
void				go_backwards(t_p *p);
void				draw_color(t_p *p, t_data *data);
int					mouse_move(int x, int y, t_p *p);
int					is_parsing_checkable(char c);
int					is_valid_map_line_support_1(t_p *p, int i,
						int k, char *line);

#endif
