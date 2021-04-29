/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbasso <fbasso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:40:34 by stribuzi          #+#    #+#             */
/*   Updated: 2021/04/26 16:36:09 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	jump_nest_square(t_p *p)
{
	if (p->player.side_dist_x < p->player.side_dist_y)
	{
		p->player.side_dist_x += p->player.delta_dist_x;
		p->player.map_x += p->player.step_x;
		p->player.side = 0;
		if (p->player.step_x == -1)
			p->player.side = 2;
	}
	else
	{
		p->player.side_dist_y += p->player.delta_dist_y;
		p->player.map_y += p->player.step_y;
		p->player.side = 1;
		if (p->player.step_y == -1)
			p->player.side = 3;
	}
}

int	mouse_handler(int button, int x, int y, t_p *p)
{
	if (button < 0 || x < 0 || y < 0)
		return (0);
	if (p->player.num_secret_doors == 0)
	{
		p->player.num_secret_doors = 1;
		p->player.dir_x = 1;
		p->player.dir_y = 0;
		p->player.plane_x = 0;
		p->player.plane_y = 0.66;
	}
	if (p->life <= 0)
		p->life = 20;
	render_next_frame(p);
	return (0);
}

int	check_hidden_doors(int key_pressed, t_p *p)
{
	if (key_pressed == 31)
	{
		if (p->map[(int)(p->player.pos_x + p->player.dir_x
				* p->player.move_speed)][(int)(p->player.pos_y)] == '3')
			p->map[(int)(p->player.pos_x + p->player.dir_x
					* p->player.move_speed)][(int)(p->player.pos_y)] = '0';
	}
	return (0);
}

void	choose_scope(int key_pressed, t_p *p)
{
	if (key_pressed == 18)
		p->player.scope_preference = 1;
	else if (key_pressed == 19)
		p->player.scope_preference = 2;
	else if (key_pressed == 20)
		p->player.scope_preference = 3;
	else if (key_pressed == 21)
		p->player.scope_preference = 4;
	render_next_frame(p);
}

int	main(int argc, char **argv)
{
	t_p	p;

	if (argc == 2 && ft_strcmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub") == 0)
	{
		parse_info(argv[1], &p);
		p.do_screenshot = 0;
		initialize_general(&p);
	}
	else if (argc == 3 && (ft_strcmp(argv[2], "--save") == 0)
		&& ft_strcmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub") == 0)
	{
		parse_info(argv[1], &p);
		p.do_screenshot = 1;
		initialize_general(&p);
	}
	else
	{
		throw_error(&p, "Invalid options");
		exit(0);
	}
	return (0);
}
