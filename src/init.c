/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abisani <abisani@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 21:13:35 by abisani           #+#    #+#             */
/*   Updated: 2025/12/22 23:59:59 by abisani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	skip_whitespace(char *str, int *neg_factor)
{
	int		i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
	{
		*neg_factor = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	return (i);
}

static double	ft_atod(char *str)
{
	double	res;
	int		div;
	int		negative;

	res = 0.0;
	div = 10;
	negative = 1;
	str += skip_whitespace(str, &negative);
	while (*str && *str >= '0' && *str <= '9' && *str != '.')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	if (*str == '.')
		str++;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res + ((double)(*str - '0') / div);
		div *= 10;
		str++;
	}
	if (*str && (*str < '0' || *str > '9'))
		return (200);
	return (res * negative);
}

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
void	init(t_data *data, int argc, char *argv[])
{
	data->fractal = get_fractal(argv[1]);
	if (data->fractal == 0)
	{
		ft_printf("%s is invalid. Try 1, 2, mandlebrot or julia.",
			argv[1]);
		error_out("", data);
	}
	if (data->fractal == JULIA && argc == 4)
	{
		data->kr = ft_atod(argv[2]);
		data->ki = ft_atod(argv[3]);
		if (data->kr > 2 || data->ki > 2)
		{
			ft_printf("kr: %f and ki: %f should both be < 2. Try 0.285 0.01\n",
				data->kr, data->ki);
			error_out("", data);
		}
	}
	data->min_r = -2.0;
	data->max_r = 1.0;
	data->min_i = -1.2;
	data->max_i = 1.2;
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "fract'ol");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_len,
			&data->endian);
}
