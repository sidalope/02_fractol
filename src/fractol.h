/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abisani <abisani@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 23:18:20 by abisani           #+#    #+#             */
/*   Updated: 2025/12/21 20:15:36 by abisani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <math.h>
# include <limits.h>
# include "printf/ft_printf.h"
# include "../minilibx-linux/mlx.h"


#include <stdio.h>

# define WIDTH 1200
# define HEIGHT 900
# define MAX_ITERATIONS 100
# define COLOR 0x999999

// remember line_len is in bits
typedef struct s_data
{
	void		*mlx;
	void		*window;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	double		res;
	double		min_r;
	double		max_r;
	double		min_i;
	double		max_i;
}				t_data;

#endif
