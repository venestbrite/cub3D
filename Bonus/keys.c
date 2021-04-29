/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 08:49:15 by stribuzi          #+#    #+#             */
/*   Updated: 2021/04/26 16:31:48 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	gun_shot(int key_pressed, t_p *p)
{
	t_tex	gun;

	if (key_pressed == 22)
	{
		gun.image = mlx_xpm_file_to_image(p->mlx,
				"./extras/guns/gun_shot", &gun.width, &gun.height);
		mlx_put_image_to_window(p->mlx, p->window, gun.image,
			p->screen_width - 200, p->screen_height - 100);
		mlx_destroy_image(p->mlx, gun.image);
	}
	if (key_pressed == 31)
	{
		if (p->map[(int)(p->player.pos_x + p->player.dir_x
				* p->player.move_speed)][(int)(p->player.pos_y)] == '3')
			p->map[(int)(p->player.pos_x + p->player.dir_x
					* p->player.move_speed)][(int)(p->player.pos_y)] = '0';
	}
}

int	key_press(int key_pressed, t_p *p)
{
	gun_shot(key_pressed, p);
	choose_scope(key_pressed, p);
	check_hidden_doors(key_pressed, p);
	if (key_pressed == 53)
		red_button(p);
	if (key_pressed == 0)
		p->a_on = 1;
	else if (key_pressed == 2)
		p->d_on = 1;
	else if (key_pressed == 13)
		p->w_on = 1;
	else if (key_pressed == 1)
		p->s_on = 1;
	else if (key_pressed == 124)
		p->right_arrow = 1;
	else if (key_pressed == 123)
		p->left_arrow = 1;
	return (1);
}

int	key_release(int key_pressed, t_p *p)
{
	if (key_pressed == 0)
		p->a_on = 0;
	else if (key_pressed == 2)
		p->d_on = 0;
	else if (key_pressed == 13)
		p->w_on = 0;
	else if (key_pressed == 1)
		p->s_on = 0;
	else if (key_pressed == 124)
		p->right_arrow = 0;
	else if (key_pressed == 123)
		p->left_arrow = 0;
	return (1);
}

int	key_update(t_p *p)
{
	if (p->w_on == 1)
		go_forward(p);
	if (p->a_on == 1)
		move_left(p);
	if (p->d_on == 1)
		move_right(p);
	if (p->s_on == 1)
		go_backwards(p);
	if (p->right_arrow == 1)
		look_right(p);
	if (p->left_arrow == 1)
		look_left(p);
	return (1);
}

void	key_set(t_p *p)
{
	p->w_on = 0;
	p->s_on = 0;
	p->d_on = 0;
	p->a_on = 0;
	p->right_arrow = 0;
	p->left_arrow = 0;
}
