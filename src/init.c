/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abisani <abisani@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 21:13:35 by abisani           #+#    #+#             */
/*   Updated: 2025/12/23 14:11:41 by abisani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** Initialize t_data structure to safe default values.
** Sets all pointers to NULL and numeric fields to 0.
*/
void	init_clean(t_data *data)
{
	data->mlx = NULL;
	data->window = NULL;
	data->img = NULL;
	data->addr = NULL;
	data->fractal = 0;
	data->min_r = 0;
	data->max_r = 0;
	data->min_i = 0;
	data->max_i = 0;
	data->kr = 0;
	data->ki = 0;
	data->render = 0;
}

/*
** Get fractal type from string argument.
*/
static int	get_fractal(char *fract)
{
	if (ft_strncmp(fract, "mandelbrot", 11) == 0)
		return (MANDELBROT);
	else if (ft_strncmp(fract, "julia", 6) == 0)
		return (JULIA);
	else if (ft_atoi(fract) == MANDELBROT)
		return (MANDELBROT);
	else if (ft_atoi(fract) == JULIA)
		return (JULIA);
	return (0);
}

/*
** Initialise mlx pointer, window, img, and img data.
** Immediately translate bits per pixel into bytes per pixel.
*/
static void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		error_out("Error initialising mlx pointer\n", data);
	data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "fract'ol");
	if (!data->window)
		error_out("Error creating mlx window\n", data);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
		error_out("Error creating mlx image\n", data);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_len,
			&data->endian);
	if (!data->addr)
		error_out("Error initialising image for editing\n", data);
	data->bpp /= 8;
	data->min_r = -2.0;
	data->max_r = 1.0;
	data->min_i = -1.2;
	data->max_i = 1.2;
}

static void	init_fractal(t_data *data, int argc, char *argv[])
{
	data->colour = COLOUR;
	data->kr = 0;
	data->ki = 0;
	data->fractal = get_fractal(argv[1]);
	if (data->fractal == 0)
		print_usage_err(data);
	else if (data->fractal == MANDELBROT)
	{
		if (argc == 3)
			data->colour = parse_hex_int(argv[2]);
		else if (argc != 2)
			print_usage_err(data);
	}
	else if (data->fractal == JULIA && (argc == 4 || argc == 5))
	{
		data->kr = ft_atof(argv[2]);
		data->ki = ft_atof(argv[3]);
		if (data->kr > 2 || data->ki > 2)
			print_usage_err(data);
		if (argc == 5)
			data->colour = parse_hex_int(argv[4]);
	}
	else if (data->fractal == JULIA)
		print_usage_err(data);
}

/*
** Parse arguments, and init complex plane mapping and mlx.
*/
void	init(t_data *data, int argc, char *argv[])
{
	init_fractal(data, argc, argv);
	if (data->colour == -1)
		print_usage_err(data);
	init_mlx(data);
}
