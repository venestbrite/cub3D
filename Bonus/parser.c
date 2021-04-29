/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 18:47:08 by stribuzi          #+#    #+#             */
/*   Updated: 2021/04/29 12:26:42 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	check_found(t_p *p, t_found found)
{
	if (found.ceiling_found == 0 || found.east_found == 0
		|| found.floor_found == 0 || found.north_found == 0
		|| found.res_found == 0 || found.south_found == 0
		|| found.sprite_found == 0 || found.west_found == 0
		|| found.spawn_pos == 0)
		throw_error(p, "Something not found!\n");
}

void	count_num_of_sprites_in_line(int *num_of_sprites, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '2')
			num_of_sprites[0]++;
		i++;
	}
}

void	parse_info_support_1(t_p *p, char *line, int i)
{
	i = 0;
	while (line[i])
	{
		if (line[i] == 'R')
			p = find_resolution(p, line);
		else if (line[i] == 'N' && line[i + 1] == 'O')
			p->north_texture = find_texture(line, "NO", p);
		else if (line[i] == 'E' && line[i + 1] == 'A')
			p->east_texture = find_texture(line, "EA", p);
		else if (line[i] == 'W' && line[i + 1] == 'E')
			p->west_texture = find_texture(line, "WE", p);
		else if (line[i] == 'S' && line[i + 1] == 'O')
			p->south_texture = find_texture(line, "SO", p);
		else if (line[i] == 'S' && line[i + 1] != 'O'
			&& line[i + 1] != '0' && line[i + 1] != '1')
			p->sprite_texture = find_texture(line, "S", p);
		else if (line[i] == 'C')
			p->floor_color = find_color(p, line, 'C');
		else if (line[i] == 'F')
			p->ceiling_color = find_color(p, line, 'F');
		i++;
	}
}

void	parse_info_support_2(t_p *p, char *line, int *map_height)
{
	int	i;

	i = 0;
	while (is_space(line[i]) == 1)
		i++;
	if (only_number_and_spaces(line) == 0 && p->map_started != 1
		&& is_parsing_checkable(line[i]) == 0)
		throw_error(p, "Extra Charachters in map!\n");
	if (p->map_started == 1 && only_spaces(line) == 1)
		throw_error(p, "Empty line in map!\n");
	if (only_number_and_spaces(line) == 1 && only_spaces(line) == 0)
	{
		if (p->map_started != 1)
			p->map_started = 1;
		count_num_of_sprites_in_line(&p->num_of_sprites, line);
		map_height[0]++;
	}
}

t_p	parse_info(char *path, t_p *p)
{
	int		fd;
	char	*line;
	int		i;
	int		map_height;

	i = 0;
	map_height = 0;
	set_to_zero(&p->found);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		throw_error(p, "Invalid map file!\n");
	while (get_next_line(fd, &line) > 0)
	{
		parse_info_support_1(p, line, i);
		parse_info_support_2(p, line, &map_height);
		free(line);
	}
	if (only_number_and_spaces(line) == 1 && only_spaces(line) == 0)
		map_height++;
	free(line);
	close(fd);
	find_map(path, map_height, p);
	check_found(p, p->found);
	return (*p);
}
