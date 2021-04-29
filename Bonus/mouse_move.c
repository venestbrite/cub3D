/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:50:50 by stribuzi          #+#    #+#             */
/*   Updated: 2021/03/30 15:15:46 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_move(int x, int y, t_p *p)
{
	static int	x_tmp;

	if (!y)
		y = 0;
	if (x_tmp == x || ((x <= (x_tmp + 50)) && (x >= (x_tmp - 50))))
	{
		p->right_arrow = 0;
		p->left_arrow = 0;
		return (0);
	}
	if (x_tmp > x)
	{
		p->left_arrow = 1;
		p->right_arrow = 0;
	}
	else
	{
		p->left_arrow = 0;
		p->right_arrow = 1;
	}
	x_tmp = x;
	return (0);
}
