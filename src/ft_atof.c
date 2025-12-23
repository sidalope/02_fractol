/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abisani <abisani@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 01:06:37 by abisani           #+#    #+#             */
/*   Updated: 2025/12/23 01:42:36 by abisani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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