/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 14:23:41 by stribuzi          #+#    #+#             */
/*   Updated: 2021/03/30 18:15:02 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	deg_to_rad(float deg)
{
	float	res;

	res = deg * M_PI / 180;
	return (res);
}

int	is_wall(char c)
{
	if (c == '1')
		return (1);
	return (0);
}

int	is_spawn_position(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

void	draw_background(t_p *p, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < p->screen_height)
	{
		x = 0;
		while (x < p->screen_width)
		{
			my_mlx_pixel_put(&p->img, x, y, color);
			x++;
		}
		y++;
	}
}

int	is_printable(int c)
{
	if (c >= 33 && c <= 126)
		return (1);
	return (0);
}
