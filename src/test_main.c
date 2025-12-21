/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abisani <abisani@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:22:57 by abisani           #+#    #+#             */
/*   Updated: 2025/12/21 20:51:54 by abisani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
- The mlx_key_hook (and other hooks) pass void *param to their respective 
	handler, so param prob needs to be a struct when passing multiple 
	arguments.
- mlx_loop_hook is called when no event occurrs (useful for rerendering on zoom?)
- Separate mlx, window, and image

-Init
- create window
- create image
- write to image
- dump image to window
- add hooks
- initiate loop (now to enable closing the window, probably)
	listen for close clicks, resizes(?), zooms

! Remember to check for pointer creation success and
	clean up all pointers. Likely everything is malloced for.
*/

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dest;

	dest = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dest = color;
}

int	key_press(int keycode, void *param)
{
	t_data		*data;

	data = (t_data *) param;
	(void)data;
	if (keycode == 0xff1b)
		exit (0);
	return (0);
}

// 1 and 3 are left and right
// 4 and 5 are zoom in and out
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

// Calculate for this pr and pi whether the imaginary
//		part tends to infinity
// imaginary (a * a) - (bi * bi)
// real 2 * a * bi
int	mandelbrot(double cr, double ci)
{
	int			iter;
	double		tmp_z_i;
	double		z_i;
	double		z_r;

	iter = 0;
	z_i = ci;
	z_r = cr;
	while (iter < MAX_ITERATIONS && ((z_r * z_r) + (z_i * z_i)) <= 4.0)
	{
		tmp_z_i = z_i;
		z_i = (2 * z_r * z_i) + ci;
		z_r = (z_r * z_r) -( tmp_z_i * tmp_z_i) + cr;
		// printf("[%.2f, %.2f]\n",cr,ci);
		iter++;
	}
	return (iter);
}

// Look at every pixel in the window
// Determine whether it is in the set
// Color accordingly

// look at every pixel
// Determine whether it is in the set
// Color accordingly
// mlx_get_screen_size()
// dest = data->addr + (y * data->line_len + x * (data->bpp / 8));
void	render(t_data *data)
{
	int			x;
	int			y;
	double		cr;
	double		ci;
	double		r_factor = (data->max_r - data->min_r)/(WIDTH - 1);
	double		i_factor = (data->max_i - data->min_i)/(HEIGHT - 1);
	int			iter;

	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		ci = data->max_i - (y * i_factor);
		x = 0;
		while (x < WIDTH)
		{
			cr = data->min_r + (x * r_factor);
			iter = mandelbrot(cr, ci);
			// ft_printf("iter: %i ", iter);
			if (iter == MAX_ITERATIONS)
				put_pixel(data, x, y, 0x00000000);
			else
				put_pixel(data, x, y, 0x00F00000 + iter);
			x++;
		}
		// ft_printf("x: %i ", x);
		// ft_printf("\ny: %i \n", y);
		y++;
	}
}


// Resizing; redraw the whole window? What?
int	main(void)
{
	t_data			data;
	// double			x;
	// double			y;

	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, WIDTH, HEIGHT, "fract'ol");
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.line_len, &data.endian);
	data.min_r = -2.0;
	data.max_r = 1.0;
	data.min_i = -1.2;
	data.max_i = 1.2;
	data.res = 0.01;
	render(&data);
	// for (int ii = 0; ii<361; ii++)
	// {
	// 	ft_printf("0");
	// 	x = 30 * sin(ii);
	// 	y = 30 * cos(ii);
	// 	put_pixel(&data, x + 250, y + 250, 0x00FF0000 + x * x);
	// }
	ft_printf("HELLO");
	ft_printf("bpp: %i\n", data.bpp);
	mlx_put_image_to_window(data.mlx, data.window, data.img, 0, 0);
	mlx_hook(data.window, 17, 1L << 17, teardown, NULL);
	mlx_key_hook(data.window, key_press, &data);
	mlx_mouse_hook(data.window, mouse_press, &data);
	mlx_loop(data.mlx);
}
