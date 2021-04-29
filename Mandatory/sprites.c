/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:45:32 by stribuzi          #+#    #+#             */
/*   Updated: 2021/03/30 17:44:56 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprite_support_1(t_p *p, int i)
{
	p->sprite.sprite_x = p->sprites[i][0] - p->player.pos_x;
	p->sprite.sprite_y = p->sprites[i][1] - p->player.pos_y;
	p->sprite.inv_det = 1.0 / (p->player.plane_x * p->player.dir_y
			- p->player.dir_x * p->player.plane_y);
	p->sprite.transform_x = p->sprite.inv_det * (p->player.dir_y
			* p->sprite.sprite_x - p->player.dir_x * p->sprite.sprite_y);
	p->sprite.transform_y = p->sprite.inv_det * (-p->player.plane_y
			* p->sprite.sprite_x + p->player.plane_x * p->sprite.sprite_y);
}

void	sprite_support(t_p *p, int i)
{
	sprite_support_1(p, i);
	p->sprite.transform_y = p->sprite.inv_det * (-p->player.plane_y
			* p->sprite.sprite_x + p->player.plane_x * p->sprite.sprite_y);
	p->sprite.sprite_screen_x = (int)((p->screen_width / 2)
			* (1 + p->sprite.transform_x / p->sprite.transform_y));
	p->sprite.sprite_height = abs((int)(p->screen_height
				/ (p->sprite.transform_y)));
	p->sprite.draw_start_y = -p->sprite.sprite_height / 2
		+ p->screen_height / 2;
	if (p->sprite.draw_start_y < 0)
		p->sprite.draw_start_y = 0;
	p->sprite.draw_end_y = p->sprite.sprite_height / 2 + p->screen_height / 2;
	if (p->sprite.draw_end_y >= p->screen_height)
		p->sprite.draw_end_y = p->screen_height - 1;
	p->sprite.sprite_width = abs((int)(p->screen_height
				/ (p->sprite.transform_y)));
	p->sprite.draw_start_x = -p->sprite.sprite_width / 2
		+ p->sprite.sprite_screen_x;
	if (p->sprite.draw_start_x < 0)
		p->sprite.draw_start_x = 0;
	p->sprite.draw_end_x = p->sprite.sprite_width / 2
		+ p->sprite.sprite_screen_x;
	if (p->sprite.draw_end_x >= p->screen_width)
		p->sprite.draw_end_x = p->screen_width - 1;
}

void	sprite_support_2_nested_1(t_p *p, int y, unsigned char *pixels)
{
	int	color;

	p->sprite.distance = (y) * 256 - p->screen_height * 128
		+ p->sprite.sprite_height * 128;
	p->sprite.tex_y = ((p->sprite.distance * p->sprite.sprite_texture.height)
			/ p->sprite.sprite_height) / 256;
	color = p->sprite.sprite_texture.mlx_get_data[p->sprite.sprite_texture.width
		* p->sprite.tex_y + p->sprite.tex_x];
	if (color > 0)
		my_mlx_pixel_put(&p->img, p->sprite.draw_start_x, y, color);
	p->sprite.color_struct = int_to_rgb(color);
	if (p->do_screenshot == 1 && color > 0)
	{
		p->sprite.position = ((p->screen_height - y) * p->screen_width
				+ p->sprite.draw_start_x) * 3;
		pixels[p->sprite.position] = p->sprite.color_struct.b;
		pixels[p->sprite.position + 1] = p->sprite.color_struct.g;
		pixels[p->sprite.position + 2] = p->sprite.color_struct.r;
	}
}

void	sprite_support_2(t_p *p, int y, unsigned char *pixels)
{
	while (p->sprite.draw_start_x < p->sprite.draw_end_x)
	{
		p->sprite.tex_x = (int)(256 * (p->sprite.draw_start_x
					- (-p->sprite.sprite_width / 2 + p->sprite.sprite_screen_x))
				* p->sprite.sprite_texture.width
				/ p->sprite.sprite_width) / 256;
		if (p->sprite.transform_y > 0 && p->sprite.draw_start_x > 0
			&& p->sprite.draw_start_x < p->screen_width
			&& p->sprite.transform_y
			< p->z_buffer[p->sprite.draw_start_x])
		{
			y = p->sprite.draw_start_y;
			while (y < p->sprite.draw_end_y)
			{
				sprite_support_2_nested_1(p, y, pixels);
				y++;
			}
		}
		p->sprite.draw_start_x++;
	}
}

void	draw_sprites(t_p *p, unsigned char *pixels)
{
	int		i;
	int		y;

	i = 0;
	y = 0;
	while (i < p->num_of_sprites)
	{
		p->sprite_order[i] = i;
		p->sprite_distance[i] = ((p->player.pos_x - p->sprites[i][0])
				* (p->player.pos_x
					- p->sprites[i][0]) + (p->player.pos_y - p->sprites[i][1])
				* (p->player.pos_y - p->sprites[i][1]));
		i++;
	}
	bubble_sort_trid(p, p->sprite_distance);
	sort_trid(p, p->sprite_distance);
	i = 0;
	while (i < p->num_of_sprites)
	{
		sprite_support(p, i);
		sprite_support_2(p, y, pixels);
		i++;
	}	
}
