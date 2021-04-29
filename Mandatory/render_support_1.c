/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_support_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:40:53 by stribuzi          #+#    #+#             */
/*   Updated: 2021/03/30 16:36:24 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	calculate_wall_hit_support_1(t_p *p)
{
	if (p->player.side_dist_x < p->player.side_dist_y)
	{
		p->player.side_dist_x += p->player.delta_dist_x;
		p->player.map_x += p->player.step_x;
		p->player.side = 0;
		if (p->player.step_x == -1)
			p->player.side = 2;
	}
	else
	{
		p->player.side_dist_y += p->player.delta_dist_y;
		p->player.map_y += p->player.step_y;
		p->player.side = 1;
		if (p->player.step_y == -1)
			p->player.side = 3;
	}
}

void	calculate_wall_hit_support_2(t_p *p)
{
	if (p->player.side == 0 || p->player.side == 2)
		p->player.perpendicular_wall_dist = (p->player.map_x
				- p->player.pos_x + (1 - p->player.step_x) / 2)
			/ p->player.ray_dir_x;
	else
		p->player.perpendicular_wall_dist = (p->player.map_y
				- p->player.pos_y + (1 - p->player.step_y) / 2)
			/ p->player.ray_dir_y;
}

void	calculate_wall_hit(t_p *p)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		calculate_wall_hit_support_1(p);
		if (p->map[p->player.map_x][p->player.map_y] != '0'
			&& (is_spawn_position(p->map[p->player.map_x]
					[p->player.map_y]) == 0) && p->map
			[p->player.map_x][p->player.map_y] != '2')
			hit = 1;
		calculate_wall_hit_support_2(p);
		p->player.line_height = (int)(p->screen_height
				/ p->player.perpendicular_wall_dist);
		p->player.draw_start = -p->player.line_height
			/ 2 + p->screen_height / 2;
		p->player.draw_end = p->player.line_height / 2 + p->screen_height / 2;
		if (p->player.draw_start < 0)
			p->player.draw_start = 0;
		if (p->player.draw_end >= p->screen_height)
			p->player.draw_end = p->screen_height - 1;
	}
}

void	calculate_wall_pos(t_p *p, int x)
{
	if (p->player.side == 0 || p->player.side == 2)
		p->player.wall_x = p->player.pos_y
			+ p->player.perpendicular_wall_dist * p->player.ray_dir_y;
	else
		p->player.wall_x = p->player.pos_x
			+ p->player.perpendicular_wall_dist * p->player.ray_dir_x;
	p->player.wall_x -= floor(p->player.wall_x);
	p->player.tex_x = (int)(p->player.wall_x
			* (double)(p->texture_north.width));
	p->player.step = 1.0 * p->texture_north.height / p->player.line_height;
	p->player.tex_pos = (p->player.draw_start - p->screen_height / 2
			+ p->player.line_height / 2) * p->player.step;
	if (p->player.side == 0 && p->player.ray_dir_x > 0)
		p->player.tex_x = p->texture_north.width - p->player.tex_x - 1;
	if (p->player.side == 1 && p->player.ray_dir_y < 0)
		p->player.tex_x = p->texture_north.width - p->player.tex_x - 1;
	p->z_buffer[x] = p->player.perpendicular_wall_dist;
}

unsigned char	*while_player_draw(t_p *p, unsigned char *pixels, int x)
{
	int	color;

	while (p->player.draw_start < p->player.draw_end)
	{
		p->player.tex_y = (int)(p->player.tex_pos)
			& (p->texture_north.height - 1);
		p->player.tex_pos += p->player.step;
		if (p->player.side == 1)
			color = p->texture_west.mlx_get_data[p->texture_west.height
				* p->player.tex_y + p->player.tex_x];
		if (p->player.side == 3)
			color = p->texture_east.mlx_get_data[p->texture_east.height
				* p->player.tex_y + p->player.tex_x];
		if (p->player.side == 2)
			color = p->texture_north.mlx_get_data[p->texture_north.height
				* p->player.tex_y + p->player.tex_x];
		if (p->player.side == 0)
			color = p->texture_south.mlx_get_data[p->texture_south.height
				* p->player.tex_y + p->player.tex_x];
		my_mlx_pixel_put(&p->img, x, p->player.draw_start, color);
		p->player.color_struct = int_to_rgb(color);
		pixels = fill_pixels(p, pixels, x, p->player.draw_start);
		p->player.draw_start++;
	}
	return (pixels);
}
