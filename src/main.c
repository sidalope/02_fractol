/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abisani <abisani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:22:57 by abisani           #+#    #+#             */
/*   Updated: 2025/12/10 10:32:27 by abisani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
- The mlx_key_hook (and other hooks) pass void *param to their respective 
	- handler, so param prob needs to be a struct when passing multiple arguments.
	- mlx_loop_hook is called when no event occurrs.
- Separate mlx, window, and image

-Init
- create window
- initiate loop (now to enable closing the window, probably)
	listen for close clicks, resizes(?), zooms
- create image
- write to image
- dump image to window

! Remember to check for pointer creation success and
	clean up all pointers. Likely everything is malloced for.
*/

# include <stdio.h>

typedef struct s_img_data
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_img_data;

void	put_pixel(t_img_data *data, int x, int y, int color)
{
	char	*dest;

	dest = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dest = color;
}

int	main(void)
{
	void		*mlx;
	void		*window;
	t_img_data	img;
	double			x;
	double			y;
	double			v;
	double			n;
	// t_img_data	tmp_img;
	
	mlx = mlx_init();
	window = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	// tmp_img.img = mlx_new_image(mlx, 1920, 1080);
	img.img = mlx_new_image(mlx, 1920, 1080);
	// tmp_img.img = mlx_get_data_addr(img.img, &img.bpp,\&img.line_len, &img.endian);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	for (double i = 0; i<361; i+= 0.1)
	{
		printf("1");
		v = 300 * sin(i);
		n = 300 * cos(i);
		for (int ii = 0; ii<361; ii++)
		{
			printf("0");
			x = 30 * sin(ii);
			y = 30 * cos(ii);
			put_pixel(&img, x + v + 500.0, y + n + 500.0, 0x00FF0000 * x);
		}
	}
	printf("HELLO");
	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	mlx_loop(mlx);
}
