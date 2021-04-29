/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 09:27:20 by stribuzi          #+#    #+#             */
/*   Updated: 2021/03/30 16:32:17 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "cub3d.h"

unsigned char	*fill_pixels(t_p *p, unsigned char *pixels, int x, int y);
void			render_support_1(t_p *p, int x);
void			render_support_2(t_p *p);
void			calculate_wall_hit_support_1(t_p *p);
void			calculate_wall_hit(t_p *p);
void			calculate_wall_pos(t_p *p, int x);
unsigned char	*while_player_draw(t_p *p, unsigned char *pixels, int x);
void			render_support_3(t_p *p);
int				render_next_frame(t_p *p);

#endif
