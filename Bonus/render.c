/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 16:12:17 by stribuzi          #+#    #+#             */
/*   Updated: 2021/03/30 18:07:27 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

unsigned char	*fill_pixels(t_p *p, unsigned char *pixels, int x, int y)
{
	int	position;

	position = ((p->screen_height - y) * p->screen_width + x) * 3;
	if (p->do_screenshot == 1)
	{
		pixels[position] = p->player.color_struct.b;
		pixels[position + 1] = p->player.color_struct.g;
		pixels[position + 2] = p->player.color_struct.r;
	}
	return (pixels);
}

void	render_support_1(t_p *p, int x)
{
	p->player.camera_x = 2 * x / (double)(p->screen_width) - 1;
	p->player.ray_dir_x = p->player.dir_x + p->player.plane_x
		* p->player.camera_x;
	p->player.ray_dir_y = p->player.dir_y + p->player.plane_y
		* p->player.camera_x;
	p->player.map_x = (int)(p->player.pos_x);
	p->player.map_y = (int)(p->player.pos_y);
	if (p->player.ray_dir_y == 0)
		p->player.delta_dist_x = 0;
	else if (p->player.ray_dir_x == 0)
		p->player.delta_dist_x = 1;
	else
		p->player.delta_dist_x = fabs(1 / p->player.ray_dir_x);
	if (p->player.ray_dir_y == 0)
		p->player.delta_dist_y = 0;
	else if (p->player.ray_dir_y == 0)
		p->player.delta_dist_y = 1;
	else
		p->player.delta_dist_y = fabs(1 / p->player.ray_dir_y);
}

void	render_support_2(t_p *p)
{
	if (p->player.ray_dir_x < 0)
	{
		p->player.step_x = -1;
		p->player.side_dist_x = (p->player.pos_x - p->player.map_x)
			* p->player.delta_dist_x;
	}
	else
	{
		p->player.step_x = 1;
		p->player.side_dist_x = (p->player.map_x + 1.0 - p->player.pos_x)
			* p->player.delta_dist_x;
	}
	if (p->player.ray_dir_y < 0)
	{
		p->player.step_y = -1;
		p->player.side_dist_y = (p->player.pos_y - p->player.map_y)
			* p->player.delta_dist_y;
	}
	else
	{
		p->player.step_y = 1;
		p->player.side_dist_y = (p->player.map_y + 1.0 - p->player.pos_y)
			* p->player.delta_dist_y;
	}
}

void	render_support_3(t_p *p)
{
	int	x;

	if (p->do_screenshot == 1)
	{
		p->pixels = (unsigned char *)malloc(sizeof(unsigned char)
				* p->screen_width * p->screen_height * 4);
		if (!p->pixels)
			throw_error(p, "Failed to malloc for screenshot!\n");
	}
	p->pixels = draw_floor_and_ceiling(p, p->pixels);
	x = 0;
	while (x < p->screen_width)
	{
		render_support_1(p, x);
		render_support_2(p);
		calculate_wall_hit(p);
		calculate_wall_pos(p, x);
		p->pixels = while_player_draw(p, p->pixels, x);
		x++;
	}
}

int	render_next_frame(t_p *p)
{
	draw_color(p, &p->img);
	mlx_put_image_to_window(p->mlx, p->window, p->img.img, 0, 0);
	if (p->life <= 0)
		p->life = 20;
	render_support_3(p);
	draw_sprites(p, p->pixels);
	if (p->do_screenshot == 1)
		write_screenshot(p, p->pixels);
	render_show_extras(p);
	key_update(p);
	mlx_do_sync(p->mlx);
	return (0);
}
