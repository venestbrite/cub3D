/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 14:26:17 by stribuzi          #+#    #+#             */
/*   Updated: 2021/03/30 18:15:56 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned int)(s1[i] - s2[i]));
		}
		i++;
	}
	return (0);
}

int	is_number(char c)
{
	if (c <= '9' && c >= '0')
		return (1);
	return (0);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}

char	*ft_strdup_life(t_p *p)
{
	char	*s2;
	int		i;
	int		num_of_lines;
	char	*s1;
	int		j;

	i = 0;
	s1 = "LIFE BAR: ";
	num_of_lines = p->life * 2;
	s2 = (char *)malloc(sizeof(char) * (10 + num_of_lines + 1));
	if (s2 == NULL || num_of_lines == 0)
		throw_error(p, "LIFE MALLOC FAILED!\n");
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	j = 0;
	while (j++ < num_of_lines)
		s2[i++] = '|';
	s2[i] = '\0';
	return (s2);
}
