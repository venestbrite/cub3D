/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 16:17:53 by stribuzi          #+#    #+#             */
/*   Updated: 2021/03/31 11:03:45 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprite_get_data(t_p *p)
{
	p->sprite.sprite_texture.mlx_get_data = (unsigned int *)mlx_get_data_addr(
			p->sprite.sprite_texture.image,
			&p->sprite.sprite_texture.bits_per_pixel,
			&p->sprite.sprite_texture.size_line,
			&p->sprite.sprite_texture.endian);
}

void	set_sprite_texture(t_p *p)
{
	if (ft_strcmp(&p->sprite_texture[ft_strlen(p->sprite_texture) - 4],
			".xpm") == 0)
	{
		p->sprite.sprite_texture.image = mlx_xpm_file_to_image(
				p->mlx, p->sprite_texture,
				&p->sprite.sprite_texture.width,
				&p->sprite.sprite_texture.height);
		if (!(p->sprite.sprite_texture.image))
			throw_error(p, "Please insert a valid sprite texture!");
	}
	else if (ft_strcmp(&p->sprite_texture[ft_strlen(p->sprite_texture) - 4],
			".png") == 0)
	{
		p->sprite.sprite_texture.image = mlx_png_file_to_image(p->mlx,
				p->sprite_texture, &p->sprite.sprite_texture.width,
				&p->sprite.sprite_texture.height);
		if (!(p->sprite.sprite_texture.image))
			throw_error(p, "Please insert a valid sprite texture!");
	}
	else
		throw_error(p, "Invalid sprite texture! \n");
	sprite_get_data(p);
	mlx_destroy_image(p->mlx, p->sprite.sprite_texture.image);
}

void	check_open_textures(t_p *p)
{
	int	fd;

	fd = open(p->south_texture, O_RDONLY);
	if (fd < 0)
		throw_error(p, "invalid south tex\n");
	close(fd);
	fd = open(p->east_texture, O_RDONLY);
	if (fd < 0)
		throw_error(p, "invalid East tex\n");
	close(fd);
	fd = open(p->north_texture, O_RDONLY);
	if (fd < 0)
		throw_error(p, "invalid north tex\n");
	close(fd);
	fd = open(p->west_texture, O_RDONLY);
	if (fd < 0)
		throw_error(p, "invalid west tex\n");
	close(fd);
	fd = open(p->sprite_texture, O_RDONLY);
	if (fd < 0)
		throw_error(p, "invalid sprite tex\n");
	close(fd);
}

void	check_screen_size(t_p *p)
{
	mlx_get_screen_size(p->mlx, &p->mac_screen_width, &p->mac_screen_height);
	if (p->screen_height >= p->mac_screen_height)
		p->screen_height = p->mac_screen_height;
	if (p->screen_width >= p->mac_screen_width)
		p->screen_width = p->mac_screen_width;
}

t_p	initialize_general(t_p *p)
{
	p->mlx = mlx_init();
	check_screen_size(p);
	p->window = mlx_new_window(p->mlx, p->screen_width, p->screen_height, "D");
	p->player = init(p->player);
	p->life = 20;
	p->life_bar = ft_strdup_life(p);
	p->img.img = mlx_new_image(p->mlx, p->screen_width, p->screen_height);
	p->img.addr = mlx_get_data_addr(p->img.img, &p->img.bits_per_pixel,
			&p->img.line_length, &p->img.endian);
	p->player.rotation_speed = deg_to_rad(5);
	p->player.move_speed = 0.2;
	p->sprite_order = malloc(sizeof(int) * p->num_of_sprites);
	p->sprite_distance = malloc(sizeof(double) * p->num_of_sprites);
	key_set(p);
	set_textures(p);
	mlx_hook(p->window, 17, 1L << 0, close_program, p);
	mlx_loop_hook(p->mlx, render_next_frame, p);
	mlx_hook(p->window, 2, 1L << 0, key_press, p);
	mlx_hook(p->window, 3, 1L << 1, key_release, p);
	mlx_hook(p->window, 06, 1L << 6, mouse_move, p);
	mlx_loop(p->mlx);
	return (*p);
}
