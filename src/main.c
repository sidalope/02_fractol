/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abisani <abisani@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:22:57 by abisani           #+#    #+#             */
/*   Updated: 2025/12/23 13:57:32 by abisani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	clean_up(t_data *data)
{
	if (!data)
		return ;
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->window)
		mlx_destroy_window(data->mlx, data->window);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}

int	exit_success(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	clean_up(data);
	exit(EXIT_SUCCESS);
	return (0);
}

void	error_out(char *err_msg, t_data *data)
{
	ft_printf("%s", err_msg);
	clean_up(data);
	exit(EXIT_FAILURE);
}

static int	loop_handler(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->render)
	{
		render(data);
		data->render = 0;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data			data;

	init_clean(&data);
	if (argc >= 2 && argc <= 5)
		init(&data, argc, argv);
	else
		print_usage_err(&data);
	render(&data);
	mlx_hook(data.window, 17, 1L << 17, exit_success, &data);
	mlx_key_hook(data.window, key_press, &data);
	mlx_mouse_hook(data.window, mouse_press, &data);
	mlx_loop_hook(data.mlx, loop_handler, &data);
	mlx_loop(data.mlx);
}
