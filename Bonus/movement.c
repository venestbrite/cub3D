/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 09:53:03 by stribuzi          #+#    #+#             */
/*   Updated: 2021/04/26 16:34:04 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	look_left(t_p *p)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->player.dir_x;
	p->player.dir_x = p->player.dir_x * cos(p->player.rotation_speed)
		- p->player.dir_y * sin(p->player.rotation_speed);
	p->player.dir_y = old_dir_x * sin(p->player.rotation_speed)
		+ p->player.dir_y * cos(p->player.rotation_speed);
	old_plane_x = p->player.plane_x;
	p->player.plane_x = p->player.plane_x * cos(p->player.rotation_speed)
		- p->player.plane_y * sin(p->player.rotation_speed);
	p->player.plane_y = old_plane_x * sin(p->player.rotation_speed)
		+ p->player.plane_y * cos(p->player.rotation_speed);
}

void	look_right(t_p *p)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->player.dir_x;
	p->player.dir_x = p->player.dir_x * cos(-p->player.rotation_speed)
		- p->player.dir_y * sin(-p->player.rotation_speed);
	p->player.dir_y = old_dir_x * sin(-p->player.rotation_speed)
		+ p->player.dir_y * cos(-p->player.rotation_speed);
	old_plane_x = p->player.plane_x;
	p->player.plane_x = p->player.plane_x * cos(-p->player.rotation_speed)
		- p->player.plane_y * sin(-p->player.rotation_speed);
	p->player.plane_y = old_plane_x * sin(-p->player.rotation_speed)
		+ p->player.plane_y * cos(-p->player.rotation_speed);
}

void	go_forward(t_p *p)
{
	if (is_wall(p->map[(int)(p->player.pos_x + p->player.dir_x
				* p->player.move_speed)][(int)(p->player.pos_y)]) == 0
		&& p->map[(int)(p->player.pos_x + p->player.dir_x
					* p->player.move_speed)][(int)(p->player.pos_y)] != '3')
		p->player.pos_x += p->player.dir_x * p->player.move_speed;
	else
	{
		p->life--;
	}
	if (is_wall(p->map[(int)(p->player.pos_x)][(int)(p->player.pos_y
		+ p->player.dir_y * p->player.move_speed)])
		== 0 && p->map[(int)(p->player.pos_x)][(int)
		(p->player.pos_y + p->player.dir_y * p->player.move_speed)] != '3')
		p->player.pos_y += p->player.dir_y * p->player.move_speed;
	else
	{
		p->life--;
	}
}

void	go_backwards(t_p *p)
{
	if (is_wall(p->map[(int)(p->player.pos_x - p->player.dir_x
				* p->player.move_speed)][(int)(p->player.pos_y)]) == 0)
		p->player.pos_x -= p->player.dir_x * p->player.move_speed;
	if (is_wall(p->map[(int)(p->player.pos_x)][(int)(p->player.pos_y
		- p->player.dir_y * p->player.move_speed)]) == 0)
		p->player.pos_y -= p->player.dir_y * p->player.move_speed;
}
