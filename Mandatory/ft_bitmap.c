/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stribuzi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:36:47 by stribuzi          #+#    #+#             */
/*   Updated: 2021/04/20 14:38:51 by stribuzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define FILE_HEADER_SIZE 14
#define INFO_HEADER_SIZE 40

void	screenshot_support_1(t_p *p, char *header)
{
	int		size;

	size = p->screen_height * p->screen_width * 4;
	ft_memset(&header[2], (int)(54 + size), 1);
	ft_memset(&header[10], (int) 54, 1);
	ft_memset(&header[14], (int) 40, 1);
	ft_memset(&header[18], (int)p->screen_width, 1);
	ft_memset(&header[22], (int)p->screen_height, 1);
	ft_memset(&header[26], (short) 1, 1);
	ft_memset(&header[28], (short) 32, 1);
	ft_memset(&header[34], (int)size, 1);
}

int	write_screenshot(t_p *p, unsigned char *pixels)
{
	char				header[54];
	int					fd;
	int					stride;
	unsigned char		*file_header;
	unsigned char		*info_header;

	header[0] = 'B';
	header[1] = 'M';
	screenshot_support_1(p, header);
	stride = (p->screen_width * 3) + ((4 - (p->screen_width * 3) % 4) % 4);
	fd = open("./screen.bmp", O_CREAT | O_RDWR, 0666);
	if (fd < 0)
		return (-1);
	file_header = create_bitmap_file_header(p->screen_height, stride);
	info_header = create_bitmap_info_header(p->screen_height, p->screen_width);
	write(fd, file_header, FILE_HEADER_SIZE);
	write(fd, info_header, INFO_HEADER_SIZE);
	write(fd, pixels, p->screen_height * p->screen_width * 4);
	close(fd);
	free(pixels);
	exit(1);
	return (1);
}

unsigned char	*create_bitmap_file_header(int height, int stride)
{
	int				file_size;
	unsigned char	*file_header;
	int				file_header_size;
	int				info_header_size;

	file_header_size = 14;
	info_header_size = 40;
	file_size = file_header_size + info_header_size + (stride * height);
	file_header = malloc(sizeof(unsigned char) * 16);
	if (!(file_header))
		return (NULL);
	ft_bzero(file_header, 16);
	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	file_header[2] = (unsigned char)(file_size);
	file_header[3] = (unsigned char)(file_size >> 8);
	file_header[4] = (unsigned char)(file_size >> 16);
	file_header[5] = (unsigned char)(file_size >> 24);
	file_header[10] = (unsigned char)(file_header_size + info_header_size);
	return (file_header);
}

unsigned char	*create_bitmap_info_header(int height, int width)
{
	unsigned char	*info_header;
	int				info_header_size;

	info_header_size = 40;
	info_header = malloc(sizeof(unsigned char) * 40);
	if (!info_header)
		return (NULL);
	ft_bzero(info_header, 40);
	info_header[0] = (unsigned char)(info_header_size);
	info_header[4] = (unsigned char)(width);
	info_header[5] = (unsigned char)(width >> 8);
	info_header[6] = (unsigned char)(width >> 16);
	info_header[7] = (unsigned char)(width >> 24);
	info_header[8] = (unsigned char)(height);
	info_header[9] = (unsigned char)(height >> 8);
	info_header[10] = (unsigned char)(height >> 16);
	info_header[11] = (unsigned char)(height >> 24);
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(3 * 8);
	return (info_header);
}
