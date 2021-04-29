/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbasso <fbasso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:43:49 by stribuzi          #+#    #+#             */
/*   Updated: 2021/04/26 15:35:17 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_support(t_p *p)
{
	int	i;

	i = 0;
	if (p->sprite_texture != NULL)
		free(p->sprite_texture);
	while (i < p->map_height)
	{
		if (p->map[i] != NULL)
			free(p->map[i]);
		i++;
	}
	i = 0;
	if (p->z_buffer != NULL)
		free(p->z_buffer);
	if (p->sprite_distance != NULL)
		free(p->sprite_distance);
	if (p->sprite_order != NULL)
		free(p->sprite_order);
}

void	free_program(t_p *p)
{
	if (p->north_texture != NULL)
		free(p->north_texture);
	if (p->south_texture != NULL)
		free(p->south_texture);
	if (p->east_texture != NULL)
		free(p->east_texture);
	if (p->west_texture != NULL)
		free(p->west_texture);
	free_support(p);
}

void	throw_error(t_p *p, char *error)
{
	free_program(p);
	printf("Error\n");
	printf("%s", error);
	exit(0);
}

void	red_button(t_p *p)
{
	free_program(p);
	exit(0);
}

int	close_program(t_p *p)
{
	red_button(p);
	return (0);
}
