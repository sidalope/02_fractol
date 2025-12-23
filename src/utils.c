/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abisani <abisani@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 13:02:26 by abisani           #+#    #+#             */
/*   Updated: 2025/12/23 14:10:48 by abisani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** Skip whitespace and detect sign in string.
** Sets neg_factor to -1 if negative sign found, otherwise 1.
** Returns index of first non-whitespace, non-sign character.
*/
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

/*
** Convert string to double.
** Returns 200 on invalid input, otherwise the parsed double.
*/
double	ft_atof(char *str)
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

/*
** Parse hexadecimal string as integer.
** Returns -1 on failure.
*/
int	parse_hex_int(char *str)
{
	int		colour;
	int		str_len;

	colour = 0;
	if (ft_strncmp(str, "0x", 2) == 0)
		str += 2;
	str_len = ft_strlen(str);
	if (str_len != 6)
		return (-1);
	while (*str)
	{
		colour = colour * 16;
		if (*str >= '0' && *str <= '9')
			colour += *str - '0';
		else if (*str >= 'a' && *str <= 'f')
			colour += *str - 'a' + 10;
		else if (*str >= 'A' && *str <= 'F')
			colour += *str - 'A' + 10;
		else
			return (-1);
		str++;
	}
	return (colour);
}

/*
** Print the fractol usage message
*/
void	print_usage_err(t_data *data)
{
	ft_printf("Usage: ./fractol [mandelbrot|julia|1|2] [kr ki] [0xRRGGBB]\n\n");
	ft_printf("Examples:\n");
	ft_printf("	./fractol mandelbrot\n");
	ft_printf("	./fractol mandelbrot 0xFF5733\n");
	ft_printf("	./fractol julia -0.7 0.27015\n");
	ft_printf("	./fractol julia -0.4 0.6 0x00AAFF\n\n");
	ft_printf("Julia parameters (kr ki) should be less thank 2.\n");
	ft_printf("Possible parameters (kr ki):\n");
	ft_printf("	-0.7 0.27015   (Dendrite spiral)\n");
	ft_printf("	-0.4 0.6       (Swirling clouds)\n");
	ft_printf("	0.285 0.01     (Douady rabbit)\n");
	ft_printf("	-0.8 0.156     (Siegel disk)\n");
	error_out("", data);
}
