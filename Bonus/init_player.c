/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 09:39:28 by stribuzi          #+#    #+#             */
/*   Updated: 2021/03/31 16:58:15 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

void	init_2(t_player *player)
{
	if (player->initial_direction == 'E')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (player->initial_direction == 'W')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
}

t_player	init(t_player player)
{
	if (player.initial_direction == 'N')
	{
		player.dir_x = -1;
		player.dir_y = 0;
		player.plane_x = 0;
		player.plane_y = 0.66;
	}
	else if (player.initial_direction == 'S')
	{
		player.dir_x = 1;
		player.dir_y = 0;
		player.plane_x = 0;
		player.plane_y = -0.66;
	}
	init_2(&player);
	return (player);
}

void	initialize_floor_texture(t_p *p)
{
	check_if_file_exists(p, "./extras/redbrick.png");
	p->ceiling_data.ceiling_texture.image = mlx_png_file_to_image(p->mlx,
			"./extras/redbrick.png", &p->ceiling_data.ceiling_texture.width,
			&p->ceiling_data.ceiling_texture.height);
	p->ceiling_data.ceiling_texture.mlx_get_data
		= (unsigned int *)mlx_get_data_addr(
			p->ceiling_data.ceiling_texture.image,
			&p->ceiling_data.ceiling_texture.bits_per_pixel,
			&p->ceiling_data.ceiling_texture.size_line,
			&p->ceiling_data.ceiling_texture.endian);
	mlx_destroy_image(p->mlx, p->ceiling_data.ceiling_texture.image);
}
