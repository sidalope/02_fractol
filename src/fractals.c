/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abisani <abisani@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 23:06:04 by abisani           #+#    #+#             */
/*   Updated: 2025/12/23 02:22:43 by abisani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** Calculate Julia set escape iterations for (zr, zi).
** z = z*z + c, where c is user supplied and fixed (kr, ki).
*/
int	julia(double zr, double zi, double kr, double ki)
{
	int			iter;
	double		zr_2;
	double		zi_2;

	iter = 0;
	while (iter < MAX_ITERATIONS)
	{
		zr_2 = zr * zr;
		zi_2 = zi * zi;
		if ((zr_2 + zi_2) > 4.0)
			break ;
		zi = (2 * zr * zi) + ki;
		zr = zr_2 - zi_2 + kr;
		iter++;
	}
	return (iter);
}

/*
** Calculate Mandelbrot set escape iterations for (cr, ci).
** z = z*z + c, where z starts at 0 and c = cr + ci*i.
** Imaginary: (a * a) - (bi * bi)
** Real: 2 * a * bi
*/
int	mandelbrot(double cr, double ci)
{
	int			iter;
	double		zi;
	double		zr;
	double		zr_2;
	double		zi_2;

	iter = 0;
	zr = cr;
	zi = ci;
	while (iter < MAX_ITERATIONS)
	{
		zr_2 = zr * zr;
		zi_2 = zi * zi;
		if ((zr_2 + zi_2) > 4.0)
			break ;
		zi = (2 * zr * zi) + ci;
		zr = zr_2 - zi_2 + cr;
		iter++;
	}
	return (iter);
}
