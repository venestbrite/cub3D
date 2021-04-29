/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 10:55:27 by stribuzi          #+#    #+#             */
/*   Updated: 2021/04/26 16:49:56 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_floor	draw_floor_support_1(t_p *p, t_floor ceiling_data)
{
	ceiling_data.ray_dir_x_0 = p->player.dir_x - p->player.plane_x;
	ceiling_data.ray_dir_y_0 = p->player.dir_y - p->player.plane_y;
	ceiling_data.ray_dir_x_1 = p->player.dir_x + p->player.plane_x;
	ceiling_data.ray_dir_y_1 = p->player.dir_y + p->player.plane_y;
	ceiling_data.pos = ceiling_data.y - p->screen_height / 2;
	ceiling_data.pos_z = 0.5 * p->screen_height;
	ceiling_data.row_distance = ceiling_data.pos_z / ceiling_data.pos;
	ceiling_data.floor_step_x = ceiling_data.row_distance
		* (ceiling_data.ray_dir_x_1 - ceiling_data.ray_dir_x_0)
		/ p->screen_width;
	ceiling_data.floor_step_y = ceiling_data.row_distance
		* (ceiling_data.ray_dir_y_1 - ceiling_data.ray_dir_y_0)
		/ p->screen_width;
	ceiling_data.floor_x = p->player.pos_x + ceiling_data.row_distance
		* ceiling_data.ray_dir_x_0;
	ceiling_data.floor_y = p->player.pos_y + ceiling_data.row_distance
		* ceiling_data.ray_dir_y_0;
	ceiling_data.x = 0;
	return (ceiling_data);
}

t_floor	draw_floor_support_2(t_floor ceiling_data)
{
	ceiling_data.cell_x = (int)(ceiling_data.floor_x);
	ceiling_data.cell_y = (int)(ceiling_data.floor_y);
	ceiling_data.tx = (int)(ceiling_data.ceiling_texture.width
			* (ceiling_data.floor_x - ceiling_data.cell_x))
		& (ceiling_data.ceiling_texture.width - 1);
	ceiling_data.ty = (int)(ceiling_data.ceiling_texture.height
			* (ceiling_data.floor_y - ceiling_data.cell_y))
		& (ceiling_data.ceiling_texture.height - 1);
	ceiling_data.floor_x += ceiling_data.floor_step_x;
	ceiling_data.floor_y += ceiling_data.floor_step_y;
	ceiling_data.color = ceiling_data.ceiling_texture.mlx_get_data[
		ceiling_data.ceiling_texture.width * ceiling_data.ty + ceiling_data.tx];
	ceiling_data.color = (ceiling_data.color >> 1) & 8355711;
	return (ceiling_data);
}

unsigned char	*fill_pixels_floor(t_p *p,
		unsigned char *pixels, t_floor ceiling_data)
{
	if (p->do_screenshot == 1)
	{
		pixels[ceiling_data.position] = ceiling_data.color_floor.b;
		pixels[ceiling_data.position + 1] = ceiling_data.color_floor.g;
		pixels[ceiling_data.position + 2] = ceiling_data.color_floor.r;
	}
	return (pixels);
}

unsigned char	*draw_floor_and_ceiling(t_p *p, unsigned char *pixels)
{
	p->ceiling_data.y = 0;
	while (++p->ceiling_data.y < p->screen_height)
	{
		p->ceiling_data = draw_floor_support_1(p, p->ceiling_data);
		while (++p->ceiling_data.x < p->screen_width)
		{
			p->ceiling_data = draw_floor_support_2(p->ceiling_data);
			p->ceiling_data.color_floor = int_to_rgb(p->ceiling_data.color);
			my_mlx_pixel_put(&p->img, p->ceiling_data.x, p->ceiling_data.y,
				p->ceiling_data.color);
			p->ceiling_data.position = (p->ceiling_data.y * p->screen_width
					+ p->ceiling_data.x) * 3;
			pixels = fill_pixels_floor(p, pixels, p->ceiling_data);
			p->ceiling_data.color
				= p->ceiling_data.ceiling_texture.mlx_get_data[
				p->ceiling_data.ceiling_texture.width * p->ceiling_data.ty
				+ p->ceiling_data.tx];
			p->ceiling_data.color = (p->ceiling_data.color >> 1) & 8355711;
			my_mlx_pixel_put(&p->img, p->ceiling_data.x, p->screen_height
				- p->ceiling_data.y - 1, p->ceiling_data.color);
			p->ceiling_data.color_floor = int_to_rgb(p->ceiling_data.color);
			pixels = fill_pixels_floor(p, pixels, p->ceiling_data);
		}
	}
	return (pixels);
}

void	draw_color(t_p *p, t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < p->screen_height)
	{
		x = 0;
		while (x < p->screen_width)
		{
			my_mlx_pixel_put(data, x, y, color_to_int(255, 0, 0));
			x++;
		}
		y++;
	}
}
