/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_finder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 18:47:44 by stribuzi          #+#    #+#             */
/*   Updated: 2021/04/29 12:14:19 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	find_map_support_1(t_p *p, int map_height, int *fd, char *path)
{
	p->sprites = (int **)malloc(sizeof(int *) * p->num_of_sprites);
	if (!(p->sprites))
		throw_error(p, "Malloc failed!\n");
	if (map_height < 3)
		throw_error(p, "Error map too short! once again.. im sorry :(");
	fd[0] = open(path, O_RDONLY);
	p->map = (char **)malloc(sizeof(char *) * map_height);
	if (!(p->map))
		throw_error(p, "Map malloc failed!\n");
}

void	find_map_support_2(t_p *p, char *line, int *k, int map_height)
{
	if (p->found.ceiling_found != 1 || p->found.east_found != 1
		|| p->found.floor_found != 1 || p->found.north_found != 1
		|| p->found.res_found != 1 || p->found.south_found != 1
		|| p->found.west_found != 1)
		throw_error(p, "Map not last!\n");
	if (is_valid_map_line(line, p, *k, map_height) == 0)
		throw_error(p, "Map not surrounded by walls!\n");
	p->map[k[0]] = ft_strdup(line);
	if (!p->map[k[0]])
		throw_error(p, "STRDUP failed!\n");
	p = check_spawn_pos(p, line, k[0]);
	check_sprites(p, line, k[0]);
	k[0]++;
}

void	find_map(char *path, int map_height, t_p *p)
{
	int		fd;
	char	*line;
	int		k;

	find_map_support_1(p, map_height, &fd, path);
	k = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (only_number_and_spaces(line) == 1 && only_spaces(line) == 0)
			find_map_support_2(p, line, &k, map_height);
		free(line);
	}
	if (only_number_and_spaces(line) == 1 && only_spaces(line) == 0)
	{
		if (is_valid_map_line(line, p, k, map_height) == 0)
			throw_error(p, "Map not surrounded by walls!\n");
		p->map[k] = ft_strdup(line);
		if (!p->map[k])
			throw_error(p, "STRDUP failed!\n");
		k++;
	}
	check_first_and_last_line(p, map_height);
	free(line);
	close(fd);
}

void	set_to_zero(t_found *found)
{
	found->north_found = 0;
	found->south_found = 0;
	found->sprite_found = 0;
	found->east_found = 0;
	found->west_found = 0;
	found->floor_found = 0;
	found->ceiling_found = 0;
	found->spawn_pos = 0;
	found->res_found = 0;
}
