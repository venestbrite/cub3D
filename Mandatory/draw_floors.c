/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbasso <fbasso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 10:55:27 by stribuzi          #+#    #+#             */
/*   Updated: 2021/04/07 09:27:02 by fbasso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_support(t_p *p, unsigned char *pixels)
{
	int		y;
	int		x;
	t_color	color;

	color = int_to_rgb(p->ceiling_color);
	y = 0;
	while (y < p->screen_height / 2)
	{
		x = 0;
		while (x < p->screen_width)
		{
			my_mlx_pixel_put(&p->img, x, y, p->floor_color);
			if (p->do_screenshot == 1)
			{
				pixels[((y * p->screen_width + x) * 3)] = color.b;
				pixels[((y * p->screen_width + x) * 3) + 1] = color.g;
				pixels[((y * p->screen_width + x) * 3) + 2] = color.r;
			}
			x++;
		}
		y++;
	}
}

unsigned char	*draw_floor_and_ceiling(t_p *p, unsigned char *pixels)
{
	int		y;
	int		x;
	t_color	color;

	draw_support(p, pixels);
	y = p->screen_height / 2;
	color = int_to_rgb(p->floor_color);
	while (y < p->screen_height)
	{
		x = 0;
		while (x < p->screen_width)
		{
			my_mlx_pixel_put(&p->img, x, y, p->ceiling_color);
			if (p->do_screenshot == 1)
			{
				pixels[((y * p->screen_width + x) * 3)] = color.b;
				pixels[((y * p->screen_width + x) * 3) + 1] = color.g;
				pixels[((y * p->screen_width + x) * 3) + 2] = color.r;
			}
			x++;
		}
		y++;
	}
	return (pixels);
}
