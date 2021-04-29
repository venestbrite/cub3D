/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_right.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 08:15:35 by stribuzi          #+#    #+#             */
/*   Updated: 2021/04/26 16:35:42 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ouch(t_p *p)
{
	p->life--;
	system("say -v Alex ouch &");
}

void	move_left(t_p *p)
{
	double	old_dir_x;
	double	dir_x;
	double	dir_y;

	dir_x = p->player.dir_x;
	dir_y = p->player.dir_y;
	old_dir_x = p->player.dir_x;
	dir_x = -dir_y;
	dir_y = old_dir_x;
	if (is_wall(p->map[(int)(p->player.pos_x + dir_x
				* p->player.move_speed)][(int)(p->player.pos_y)]) == 0
		&& p->map[(int)(p->player.pos_x + dir_x
					* p->player.move_speed)][(int)(p->player.pos_y)] != '3')
		p->player.pos_x += dir_x * p->player.move_speed;
	else
		ouch(p);
	if (is_wall(p->map[(int)(p->player.pos_x)][(int)(p->player.pos_y
		+ dir_y * p->player.move_speed)]) == 0 && p->map
		[(int)(p->player.pos_x)][(int)(p->player.pos_y
							+ dir_y * p->player.move_speed)] != '3')
		p->player.pos_y += dir_y * p->player.move_speed;
	else
		ouch(p);
}

void	move_right(t_p *p)
{
	double	old_dir_x;
	double	dir_x;
	double	dir_y;

	dir_x = p->player.dir_x;
	dir_y = p->player.dir_y;
	old_dir_x = p->player.dir_x;
	dir_x = -dir_y * sin(-deg_to_rad(90));
	dir_y = old_dir_x * sin(-deg_to_rad(90));
	if (is_wall(p->map[(int)(p->player.pos_x + dir_x
				* p->player.move_speed)][(int)(p->player.pos_y)]) == 0
		&& p->map[(int)(p->player.pos_x + dir_x
					* p->player.move_speed)][(int)(p->player.pos_y)] != '3')
		p->player.pos_x += dir_x * p->player.move_speed;
	else
		ouch(p);
	if (is_wall(p->map[(int)(p->player.pos_x)][(int)(p->player.pos_y
		+ dir_y * p->player.move_speed)]) == 0 && p->map
		[(int)(p->player.pos_x)][(int)(p->player.pos_y
							+ dir_y * p->player.move_speed)] != '3')
		p->player.pos_y += dir_y * p->player.move_speed;
	else
		ouch(p);
}
