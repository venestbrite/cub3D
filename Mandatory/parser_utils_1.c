/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 18:51:24 by stribuzi          #+#    #+#             */
/*   Updated: 2021/03/30 18:04:59 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	find_resolution_support_1(t_p *p, char *line, int *i)
{
	if (p->found.res_found == 1)
		throw_error(p, "Duplicate resolution!\n");
	else
		p->found.res_found = 1;
	while (is_space(line[i[0]]) == 1)
		i[0]++;
	if (line[i[0]++] != 'R')
		throw_error(p, "Generic error\n");
	while (is_space(line[i[0]]) == 1)
		i[0]++;
}

t_p	*find_resolution(t_p *p, char *line)
{
	int	i;

	i = 0;
	find_resolution_support_1(p, line, &i);
	if (is_number(line[i]) == 1)
		mini_atoi(&p->screen_width, &i, line);
	while (is_space(line[i]) == 1)
		i++;
	if (is_number(line[i]) == 1)
		mini_atoi(&p->screen_height, &i, line);
	else
		throw_error(p, "Res not number");
	while (is_space(line[i]) == 1)
		i++;
	if (p->screen_width < 1 || p->screen_height < 1)
		throw_error(p, "Too small! (i know you get that a lot :( )\n");
	p->z_buffer = malloc(sizeof(double) * p->screen_width);
	if (!(p->z_buffer))
		throw_error(p, "Unable to malloc!\n");
	if (i != ft_strlen(line))
		throw_error(p, "Extra charachters!");
	return (p);
}

void	check_if_file_exists(t_p *p, char *s1)
{
	int	fd;

	fd = open(s1, O_RDONLY);
	if (fd < 0)
		throw_error(p, "One or more files do not exist!");
	close(fd);
}

void	check_error_texture_support(char *to_check, t_p *p)
{
	if (ft_strcmp(to_check, "SO") == 0)
	{
		if (p->found.south_found != 1)
			p->found.south_found = 1;
		else
			throw_error(p, "Error duplicate south!\n");
	}
	if (ft_strcmp(to_check, "S") == 0)
	{
		if (p->found.sprite_found != 1)
			p->found.sprite_found = 1;
		else
			throw_error(p, "Error duplicate sprite!\n");
	}
}

void	check_error_texture(char *to_check, t_p *p)
{
	if (ft_strcmp(to_check, "NO") == 0)
	{
		if (p->found.north_found != 1)
			p->found.north_found = 1;
		else
			throw_error(p, "Error duplicate north!\n");
	}
	if (ft_strcmp(to_check, "EA") == 0)
	{
		if (p->found.east_found != 1)
			p->found.east_found = 1;
		else
			throw_error(p, "Error duplicate east!\n");
	}
	if (ft_strcmp(to_check, "WE") == 0)
	{
		if (p->found.west_found != 1)
			p->found.west_found = 1;
		else
			throw_error(p, "Error duplicate west!\n");
	}
	check_error_texture_support(to_check, p);
}
