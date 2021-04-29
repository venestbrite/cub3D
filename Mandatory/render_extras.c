/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_extras.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 09:53:24 by stribuzi          #+#    #+#             */
/*   Updated: 2021/04/26 16:38:13 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	show_gun(t_p *p)
{
	t_tex	gun;

	gun.image = mlx_xpm_file_to_image(p->mlx,
			"./extras/guns/gun",
			&gun.width, &gun.height);
	if (!gun.image)
		return ;
	mlx_put_image_to_window(p->mlx, p->window, gun.image,
		p->screen_width - 200, p->screen_height - 100);
}

void	show_life_bar(t_p *p)
{
	char	numero[2];

	free(p->life_bar);
	p->life_bar = ft_strdup_life(p);
	mlx_string_put(p->mlx, p->window, 20, p->screen_height - 30,
		color_to_int(255, 255, 255), p->life_bar);
	numero[0] = p->player.num_secret_doors + '0';
	numero[1] = '\0';
	mlx_string_put(p->mlx, p->window, p->screen_width - 100,
		p->screen_height - 30, color_to_int(255, 255, 255), "Score: ");
	mlx_string_put(p->mlx, p->window, p->screen_width - 30,
		p->screen_height - 30, color_to_int(255, 255, 255), numero);
}

void	show_scope(t_p *p)
{
	t_tex	scope;

	if (p->player.scope_preference == 1)
		scope.image = mlx_xpm_file_to_image(p->mlx,
				"./extras/scopes/mirino_1", &scope.width, &scope.height);
	else if (p->player.scope_preference == 2)
		scope.image = mlx_xpm_file_to_image(p->mlx,
				"./extras/scopes/mirino_2", &scope.width, &scope.height);
	else if (p->player.scope_preference == 3)
		scope.image = mlx_xpm_file_to_image(p->mlx,
				"./extras/scopes/mirino_3", &scope.width, &scope.height);
	else if (p->player.scope_preference == 4)
		scope.image = mlx_xpm_file_to_image(p->mlx,
				"./extras/scopes/mirino_4", &scope.width, &scope.height);
	mlx_put_image_to_window(p->mlx, p->window, scope.image,
		p->screen_width / 2 - (scope.width / 2),
		p->screen_height / 2 - (scope.height / 2));
}

void	show_warning(t_p *p)
{
	t_tex	texture;

	texture.image = mlx_xpm_file_to_image(p->mlx, "extras/hand_stop",
			&texture.width, &texture.height);
	mlx_put_image_to_window(p->mlx, p->window, texture.image, 15, 15);
	mlx_string_put(p->mlx, p->window, p->screen_width - 250,
		p->screen_height / 2 - 100, color_to_int(255, 0, 0),
		"COLLISION DETECTED");
}

void	render_show_extras(t_p *p)
{
	mlx_put_image_to_window(p->mlx, p->window, p->img.img, 0, 0);
	show_scope(p);
	show_life_bar(p);
	show_gun(p);
	if (is_wall(p->map[(int)(p->player.pos_x + p->player.dir_x
				* p->player.move_speed)][(int)(p->player.pos_y)]) == 1)
		show_warning(p);
	else if (is_wall(p->map[(int)(p->player.pos_x)][(int)(p->player.pos_y
		+ p->player.dir_y * p->player.move_speed)]) == 1)
		show_warning(p);
}
