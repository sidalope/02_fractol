/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abisani <abisani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:22:57 by abisani           #+#    #+#             */
/*   Updated: 2025/12/10 12:35:04 by abisani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
- The mlx_key_hook (and other hooks) pass void *param to their respective 
	- handler, so param prob needs to be a struct when passing multiple 
		arguments.
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

void	put_pixel(t_img_data *data, int x, int y, int color)
{
	char	*dest;

	dest = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dest = color;
}

int	key_press(int keycode, void *param)
{
	t_img_data		*data;

	data = (t_img_data *) param;
	(void)data;
	if (keycode == 0xff1b)
		exit (0);
	return (0);
}

int	mouse_press(int button, int x, int y, void *param)
{
	(void)x;
	(void)y;
	(void)param;
	ft_printf("\n:%i:\n", button);
	return (0);
}

int	teardown(void)
{
	exit (0);
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
	window = mlx_new_window(mlx, 1000, 600, "Hello world!");
	// tmp_img.img = mlx_new_image(mlx, 1920, 1080);
	img.img = mlx_new_image(mlx, 1000, 600);
	// tmp_img.img = mlx_get_data_addr(img.img, &img.bpp,\&img.line_len, &img.endian);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	for (double i = 0; i<361; i+= 0.1)
	{
		ft_printf("1");
		v = 60 * sin(i);
		n = 60 * cos(i);
		for (int ii = 0; ii<361; ii++)
		{
			ft_printf("0");
			x = 30 * sin(ii);
			y = 30 * cos(ii);
			put_pixel(&img, x + v + 250, y + n + 250, 0x00FF0000 + 10 * x);
		}
	}
	ft_printf("HELLO");
	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	mlx_hook(window, 17, 1L << 17, teardown, NULL);
	mlx_key_hook(window, key_press, &img);
	mlx_mouse_hook(window, mouse_press, &img);
	mlx_loop(mlx);
}
