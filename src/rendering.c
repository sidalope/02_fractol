/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abisani <abisani@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 23:04:33 by abisani           #+#    #+#             */
/*   Updated: 2025/12/22 22:55:31 by abisani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** Colour a pixel at x and y.
*/
static void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dest;

	dest = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dest = color;
}

// TODO: This could actually return a pointer to a function for speeeeed?
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

void	render(t_data *data)
{
	int			x;
	int			y;
	double		cr;
	double		ci;
	int			iter;

	x = 0;
	y = 0;
	mlx_clear_window(data->mlx, data->window);
	while (y < HEIGHT)
	{
		ci = data->max_i - (y * (data->max_i - data->min_i) / (HEIGHT - 1));
		x = 0;
		while (x < WIDTH)
		{
			cr = data->min_r + (x * (data->max_r - data->min_r) / (WIDTH - 1));
			iter = calculate_fractal(cr, ci, data);
			if (iter == MAX_ITERATIONS)
				put_pixel(data, x, y, 0x00000000);
			else
				put_pixel(data, x, y, COLOUR * iter);
			x++;
		}
		y++;
	}
}
