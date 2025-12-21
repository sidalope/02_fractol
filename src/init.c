/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abisani <abisani@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 21:13:35 by abisani           #+#    #+#             */
/*   Updated: 2025/12/22 00:49:50 by abisani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
}

// TODO Check for mlx object creation success
// TODO Add proper argument parsing
// TODO Check that kr and ki should be doubles and that atoi in init() is parsing them correctly
void	init(t_data *data, int argc, char *argv[])
{
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "fract'ol");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_len,
			&data->endian);
	data->fractal = get_fractal(argv[1]);
	if (data->fractal == 0)
	{
		ft_printf("%s is invalid. Try 1, 2, mandlebrot or julia.",
			argv[1]);
		error_out("", data);
	}
	if (data->fractal == JULIA && argc == 3)
	{
		data->kr = atoi(argv[2]);
		data->ki = atoi(argv[3]);
	}
	data->min_r = -2.0;
	data->max_r = 1.0;
	data->min_i = -1.2;
	data->max_i = 1.2;
}
