/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abisani <abisani@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 23:06:04 by abisani           #+#    #+#             */
/*   Updated: 2025/12/22 00:34:21 by abisani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	julia(double z_r, double z_i, double kr, double ki)
{
	int			iter;
	double		tmp_z_i;

	iter = 0;
	while (iter < MAX_ITERATIONS && ((z_r * z_r) + (z_i * z_i)) <= 4.0)
	{
		tmp_z_i = z_i;
		z_i = (2 * z_r * z_i) + ki;
		z_r = (z_r * z_r) - (tmp_z_i * tmp_z_i) + kr;
		iter++;
	}
	return (iter);
}

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
		z_r = (z_r * z_r) - (tmp_z_i * tmp_z_i) + cr;
		iter++;
	}
	return (iter);
}
