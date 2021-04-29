/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:23:33 by stribuzi          #+#    #+#             */
/*   Updated: 2021/03/30 18:22:19 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_south_texture(t_p *p)
{
	if (ft_strcmp(&p->south_texture[ft_strlen(p->south_texture) - 4], ".xpm")
		== 0)
	{
		p->texture_south.image = mlx_xpm_file_to_image(p->mlx,
				p->south_texture, &p->texture_south.width,
				&p->texture_south.height);
		if (!p->texture_south.image)
			throw_error(p, "Please insert a valid south texture!");
	}
	else if (ft_strcmp(&p->south_texture[ft_strlen(p->south_texture) - 4],
			".png") == 0)
	{
		p->texture_south.image = mlx_png_file_to_image(p->mlx,
				p->south_texture, &p->texture_south.width,
				&p->texture_south.height);
		if (!p->texture_south.image)
			throw_error(p, "Please insert a valid south texture!");
	}
	else
		throw_error(p, "Invalid south texture! \n");
	p->texture_south.mlx_get_data = (unsigned int *)mlx_get_data_addr(
			p->texture_south.image, &p->texture_south.bits_per_pixel,
			&p->texture_south.size_line, &p->texture_south.endian);
	mlx_destroy_image(p->mlx, p->texture_south.image);
}

void	set_north_texture(t_p *p)
{
	if (ft_strcmp(&p->north_texture[ft_strlen(p->north_texture) - 4],
			".xpm") == 0)
	{
		p->texture_north.image = mlx_xpm_file_to_image(p->mlx,
				p->north_texture, &p->texture_north.width,
				&p->texture_north.height);
		if (!p->texture_north.image)
			throw_error(p, "Please insert a valid north texture!");
	}
	else if (ft_strcmp(&p->north_texture[ft_strlen(p->north_texture) - 4],
			".png") == 0)
	{
		p->texture_north.image = mlx_png_file_to_image(
				p->mlx, p->north_texture, &p->texture_north.width,
				&p->texture_north.height);
		if (!p->texture_north.image)
			throw_error(p, "Please insert a valid north texture!");
	}
	else
		throw_error(p, "Invalid north texture! \n");
	p->texture_north.mlx_get_data = (unsigned int *)mlx_get_data_addr(
			p->texture_north.image, &p->texture_north.bits_per_pixel,
			&p->texture_north.size_line, &p->texture_north.endian);
	mlx_destroy_image(p->mlx, p->texture_north.image);
}

void	set_west_texture(t_p *p)
{
	if (ft_strcmp(&p->west_texture[ft_strlen(p->west_texture) - 4],
			".xpm") == 0)
	{
		p->texture_west.image = mlx_xpm_file_to_image(p->mlx,
				p->west_texture, &p->texture_west.width,
				&p->texture_west.height);
		if (!p->texture_west.image)
			throw_error(p, "Please insert a valid west texture!");
	}
	else if (ft_strcmp(&p->west_texture[ft_strlen(p->west_texture) - 4],
			".png") == 0)
	{
		p->texture_west.image = mlx_png_file_to_image(p->mlx,
				p->west_texture, &p->texture_west.width,
				&p->texture_west.height);
		if (!p->texture_west.image)
			throw_error(p, "Please insert a valid west texture!");
	}
	else
		throw_error(p, "Invalid west texture! \n");
	p->texture_west.mlx_get_data = (unsigned int *)mlx_get_data_addr(
			p->texture_west.image, &p->texture_west.bits_per_pixel,
			&p->texture_west.size_line, &p->texture_west.endian);
	mlx_destroy_image(p->mlx, p->texture_west.image);
}

void	set_east_texture(t_p *p)
{
	if (ft_strcmp(&p->east_texture[ft_strlen(p->east_texture) - 4],
			".xpm") == 0)
	{
		p->texture_east.image = mlx_xpm_file_to_image(
				p->mlx, p->east_texture, &p->texture_east.width,
				&p->texture_east.height);
		if (!p->texture_east.image)
			throw_error(p, "Please insert a valid east texture!");
	}
	else if (ft_strcmp(&p->east_texture[ft_strlen(p->east_texture) - 4],
			".png") == 0)
	{
		p->texture_east.image = mlx_png_file_to_image(p->mlx,
				p->east_texture, &p->texture_east.width,
				&p->texture_east.height);
		if (!p->texture_east.image)
			throw_error(p, "Please insert a valid east texture!");
	}
	else
		throw_error(p, "Invalid east texture! \n");
	p->texture_east.mlx_get_data = (unsigned int *)mlx_get_data_addr(
			p->texture_east.image, &p->texture_east.bits_per_pixel,
			&p->texture_east.size_line, &p->texture_east.endian);
	mlx_destroy_image(p->mlx, p->texture_east.image);
}

void	set_textures(t_p *p)
{
	set_south_texture(p);
	set_north_texture(p);
	set_west_texture(p);
	set_east_texture(p);
	set_sprite_texture(p);
	initialize_floor_texture(p);
}
