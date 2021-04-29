/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 08:02:50 by stribuzi          #+#    #+#             */
/*   Updated: 2021/03/30 15:27:37 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	color_to_int(int red, int green, int blue)
{
	int		rgb;

	rgb = red;
	rgb = (rgb << 8) + green;
	rgb = (rgb << 8) + blue;
	return (rgb);
}

t_color	int_to_rgb(int color)
{
	int		b;
	int		g;
	int		r;
	t_color	to_return;

	b = color % 256;
	g = ((color - b) / 256) % 256;
	r = ((color - b) / pow(256, 2)) - g / 256;
	to_return.r = r;
	to_return.g = g;
	to_return.b = b;
	return (to_return);
}
