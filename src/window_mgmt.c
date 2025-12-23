/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_mgmt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abisani <abisani@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 21:09:55 by abisani           #+#    #+#             */
/*   Updated: 2025/12/23 02:42:39 by abisani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** Pan the fractal view by offset (cr, ci) in complex plane.
** Shifts all viewport bounds by the same amount.
*/
static void	move(double cr, double ci, t_data *data)
{
	data->max_r = data->max_r + cr;
	data->min_r = data->min_r + cr;
	data->max_i = data->max_i + ci;
	data->min_i = data->min_i + ci;
}

/*
** Zoom viewport by a given factor.
** Factor < 1.0 zooms in, > 1.0 zooms out.
** Preserves center point of current view.
*/
static void	zoom(double zoom, t_data *data)
{
	double	center_r;
	double	center_i;
	double	new_range_r;
	double	new_range_i;

	center_r = (data->max_r + data->min_r) / 2.0;
	center_i = (data->max_i + data->min_i) / 2.0;
	new_range_r = ((data->max_r - data->min_r) * zoom) / 2.0;
	new_range_i = ((data->max_i - data->min_i) * zoom) / 2.0;
	data->max_r = center_r + new_range_r;
	data->min_r = center_r - new_range_r;
	data->max_i = center_i + new_range_i;
	data->min_i = center_i - new_range_i;
}

/*
** Handle keyboard events.
** ESC (0xff1b): exit program with cleanup.
** Arrow keys (0xff51-54): pan view by 1/10th of range.
** Re-renders fractal after movement.
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
	data->render = 1;
	return (0);
}

/*
** Bind mouse wheel scrolling to zoom.
** Re-renders fractal after zoom.
*/
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
	data->render = 1;
	return (0);
}
