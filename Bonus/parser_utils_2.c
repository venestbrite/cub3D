/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 16:20:38 by stribuzi          #+#    #+#             */
/*   Updated: 2021/04/29 12:27:12 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*find_texture_support_1(int pos, char *line, char *to_return, t_p *p)
{
	int	tex_len;

	tex_len = 0;
	while (line[pos])
	{
		to_return[tex_len] = line[pos];
		tex_len++;
		pos++;
	}
	to_return[tex_len] = '\0';
	if (ft_strcmp(&to_return[ft_strlen(to_return) - 4], ".png") != 0
		&& ft_strcmp(&to_return[ft_strlen(to_return) - 4], ".xpm") != 0)
		throw_error(p, "Incorrect texture format!\n");
	return (to_return);
}

char	*find_texture(char *line, char *to_check, t_p *p)
{
	int		i;
	int		pos;
	int		tex_len;
	char	*to_return;

	i = 0;
	tex_len = 0;
	check_error_texture(to_check, p);
	while (is_space(line[i]) == 1)
		i++;
	if (line[i++] != to_check[0])
		throw_error(p, "Something went wrong!\n");
	if (line[i] == to_check[1])
		i++;
	while (is_space(line[i]) == 1)
		i++;
	pos = i;
	while (line[i++])
		tex_len++;
	to_return = (char *)malloc(sizeof(char) * tex_len + 1);
	if (!to_return)
		throw_error(p, "MALLOC FAILED!\n");
	find_texture_support_1(pos, line, to_return, p);
	check_if_file_exists(p, to_return);
	return (to_return);
}

void	mini_atoi(int *res, int *i, char *line)
{
	int	entered;

	entered = 0;
	res[0] = 0;
	while (is_space(line[i[0]]) == 1)
		i[0]++;
	if (line[i[0]] == ',')
		i[0]++;
	while (is_space(line[i[0]]) == 1)
		i[0]++;
	while (is_number(line[i[0]]) == 1)
	{
		entered = 1;
		res[0] *= 10;
		res[0] += line[i[0]] - '0';
		i[0]++;
	}
	if (entered == 0)
		res[0] = -1;
}

int	is_spawn_pos(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

void	set_to_non_color(t_color *color)
{
	color->b = -1;
	color->r = -1;
	color->g = -1;
}
