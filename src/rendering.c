/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abisani <abisani@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 23:04:33 by abisani           #+#    #+#             */
/*   Updated: 2025/12/23 14:13:49 by abisani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** Colour pixel at (x, y).
*/
static void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dest;

	dest = data->addr + (y * data->line_len + x * data->bpp);
	*(unsigned int *)dest = color;
}

/*
** Choose and perform the fractal calculation.
*/
int	calculate_fractal(double cr, double ci, t_data *data)
{
	int		iter;

	iter = 0;
	if (data->fractal == MANDELBROT)
		iter = mandelbrot(cr, ci);
	else if (data->fractal == JULIA)
		iter = julia(cr, ci, data->kr, data->ki);
	return (iter);
}

/*
** Render the fractal to the current window
*/
void	render(t_data *data)
{
	int			x;
	int			y;
	double		cr;
	double		ci;
	int			iter;

	data->r_factor = (data->max_r - data->min_r) / (WIDTH - 1);
	data->i_factor = (data->max_i - data->min_i) / (HEIGHT - 1);
	y = -1;
	while (++y < HEIGHT)
	{
		ci = data->max_i - y * data->i_factor;
		x = -1;
		while (++x < WIDTH)
		{
			cr = data->min_r + x * data->r_factor;
			iter = calculate_fractal(cr, ci, data);
			if (iter == MAX_ITERATIONS)
				put_pixel(data, x, y, 0x00000000);
			else
				put_pixel(data, x, y, data->colour * iter);
		}
	}
	mlx_put_image_to_window(data->mlx, data->window, data->img, 0, 0);
}
