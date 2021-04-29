/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 10:01:36 by stribuzi          #+#    #+#             */
/*   Updated: 2021/04/29 12:17:25 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*allocate_map(char *to_return, char *line)
{
	int	i;
	int	len;
	int	pos;

	i = 0;
	len = 0;
	while (is_space(line[i]) == 1)
		i++;
	pos = i;
	while (line[i])
	{
		len++;
		i++;
	}
	to_return = (char *)malloc(sizeof(char) * len + 1);
	if (!to_return)
		return (NULL);
	i = 0;
	while (line[pos])
	{
		to_return[i] = line[pos];
		pos++;
	}
	return (to_return);
}

int	is_valid_map_line(char *line, t_p *p, int k, int map_height)
{
	int	i;
	int	temp;

	i = 0;
	while (is_space(line[i]) == 1)
		i++;
	if (is_valid_map_line_support_1(p, i, k, line) == 0)
		return (0);
	temp = i;
	i = temp;
	if (line[i] != '1' || line[ft_strlen(line) - 1] != '1')
		return (0);
	return (1);
}

t_p	*check_spawn_pos(t_p *p, char *line, int k)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
		{
			if (p->found.spawn_pos == 0)
				p->found.spawn_pos = 1;
			else
				throw_error(p, "Multiple spawn positions!\n");
			p->player.pos_x = (double)k;
			p->player.pos_y = (double)i;
			p->player.initial_direction = line[i];
		}
		i++;
	}
	return (p);
}

void	check_sprites(t_p *p, char *line, int k)
{
	static int	sprite_counter = 0;
	int			i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '2')
		{
			p->sprites[sprite_counter] = malloc(sizeof(int) * 2);
			if (!p->sprites[sprite_counter])
				throw_error(p, "Sprites malloc failed!\n");
			p->sprites[sprite_counter][0] = k;
			p->sprites[sprite_counter][1] = i;
			sprite_counter++;
		}
		i++;
	}
}

void	check_first_and_last_line(t_p *p, int map_height)
{
	int	i;

	i = 0;
	while (i < ft_strlen(p->map[0]))
	{
		if (p->map[0][i] != '1' && is_space(p->map[0][i]) == 0)
			throw_error(p, "Invalid first line! 1234");
		i++;
	}
	i = 1;
	while (i < (ft_strlen(p->map[map_height - 2]) - 1))
	{
		if (p->map[map_height - 2][i] == '0')
			if (p->map[map_height - 1][i] != '1')
				throw_error(p, "Invalid last line\n");
		i++;
	}
	i = 0;
	while (i < ft_strlen(p->map[map_height - 1]))
	{
		if (p->map[map_height - 1][i] != '1'
			&& is_space(p->map[map_height - 1][i]) == 0)
			throw_error(p, "Invalid last line!");
		i++;
	}
}
