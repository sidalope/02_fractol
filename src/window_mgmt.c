/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_mgmt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abisani <abisani@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 21:09:55 by abisani           #+#    #+#             */
/*   Updated: 2025/12/23 00:20:18 by abisani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	move(double cr, double ci, t_data *data)
{
	data->max_r = data->max_r + cr;
	data->min_r = data->min_r + cr;
	data->max_i = data->max_i + ci;
	data->min_i = data->min_i + ci;
}

/*
** Zoom in by a factor of zoom.
*/
static void	zoom(double zoom, t_data *data)
{
	data->max_r = data->max_r * zoom;
	data->min_r = data->min_r * zoom;
	data->max_i = data->max_i * zoom;
	data->min_i = data->min_i * zoom;
}

/*
** Bind Esc to exit
*/
int	key_press(int keycode, void *param)
{
	t_data		*data;
	double		r_tenth;
	double		i_tenth;

	data = (t_data *) param;
	r_tenth = (data->max_r - data->min_r) / 10;
	i_tenth = (data->max_i - data->min_i) / 10;
	if (keycode == 0xff1b)
	{
		clean_up(data);
		exit (0);
	}
	else if (keycode == 0xff51)
		move(-r_tenth, 0, data);
	else if (keycode == 0xff52)
		move(0, i_tenth, data);
	else if (keycode == 0xff53)
		move(r_tenth, 0, data);
	else if (keycode == 0xff54)
		move(0, -i_tenth, data);
	render(data);
	return (0);
}

// TODO: This zoom function will eventually slow down to nothing. Right?
int	mouse_press(int button, int x, int y, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	(void)x;
	(void)y;
	if (button == 4)
		zoom(0.95, data);
	if (button == 5)
		zoom(1.05, data);
	render(data);
	return (0);
}
