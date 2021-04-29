/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 10:01:24 by stribuzi          #+#    #+#             */
/*   Updated: 2021/03/30 16:27:24 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	check_num_of_commas(t_p *p, char *line)
{
	int	num_of_commas;
	int	i;

	num_of_commas = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == ',')
			num_of_commas++;
		i++;
	}
	if (num_of_commas != 2)
		throw_error(p, "Invalid color!\n");
}

void	check_color_error_1(char to_check, t_p *p, char *line, int *i)
{
	if (to_check == 'F')
	{
		if (p->found.floor_found == 0)
			p->found.floor_found = 1;
		else
			throw_error(p, "Error duplicate floooooor!\n");
	}
	if (to_check == 'C')
	{
		if (p->found.ceiling_found == 0)
			p->found.ceiling_found = 1;
		else
			throw_error(p, "Error duplicate ceeeeieling!\n");
	}
	i[0] = 0;
	while (is_space(line[i[0]]) == 1)
		i[0]++;
	if (line[i[0]] != to_check)
		throw_error(p, "Error not correct color check letter\n");
	i[0]++;
}

int	find_color(t_p *p, char *line, char to_check)
{
	int		i;
	t_color	color;

	set_to_non_color(&color);
	check_num_of_commas(p, line);
	check_color_error_1(to_check, p, line, &i);
	mini_atoi(&color.r, &i, line);
	mini_atoi(&color.g, &i, line);
	mini_atoi(&color.b, &i, line);
	if (color.r > 255 || color.g > 255 || color.b > 255
		|| color.r < 0 || color.g < 0 || color.b < 0)
		throw_error(p, "Invalid range\n");
	while (is_space(line[i]) == 1)
		i++;
	if (i != ft_strlen(line))
		throw_error(p, "Error Something else \n");
	return (color_to_int(color.r, color.g, color.b));
}

int	only_number_and_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (is_number(line[i]) == 0 && is_space(line[i])
			== 0 && is_spawn_pos(line[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	only_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (is_space(line[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
