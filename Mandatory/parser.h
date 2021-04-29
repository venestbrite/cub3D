/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 09:30:06 by stribuzi          #+#    #+#             */
/*   Updated: 2021/03/30 09:31:00 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "cub3d.h"

void	check_error_texture(char *to_check, t_p *p);
void	check_if_file_exists(t_p *p, char *s1);
t_p		*find_resolution(t_p *p, char *line);
char	*find_texture(char *line, char *to_check, t_p *p);
int		is_spawn_pos(char c);
void	set_to_non_color(t_color *color);
int		find_color(t_p *p, char *line, char to_check);
void	check_if_file_exists(t_p *p, char *s1);
void	check_error_texture(char *to_check, t_p *p);
int		only_number_and_spaces(char *line);
int		only_spaces(char *line);
char	*allocate_map(char *to_return, char *line);
int		is_valid_map_line(char *line, t_p *p, int k, int map_height);
t_p		*check_spawn_pos(t_p *p, char *line, int k);
void	check_sprites(t_p *p, char *line, int k);
void	check_first_and_last_line(t_p *p, int map_height);
void	find_map(char *path, int map_height, t_p *p);
void	set_to_zero(t_found *found);

#endif
