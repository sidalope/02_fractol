/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_mgmt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abisani <abisani@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 21:09:55 by abisani           #+#    #+#             */
/*   Updated: 2025/12/21 23:40:38 by abisani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** Bind Esc to exit
*/
int	key_press(int keycode, void *param)
{
	t_data		*data;

	data = (t_data *) param;
	(void)data;
	if (keycode == 0xff1b)
	{
		clean_up(data);
		exit (0);
	}
	return (0);
}

// 1 and 3 are left and right
// 4 and 5 are zoom in and out
int	mouse_press(int button, int x, int y, void *param)
{
	(void)x;
	(void)y;
	(void)param;
	ft_printf("\n:%i:\n", button);
	return (0);
}
