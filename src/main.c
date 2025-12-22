/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abisani <abisani@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:22:57 by abisani           #+#    #+#             */
/*   Updated: 2025/12/22 11:26:57 by abisani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/**
- The mlx_key_hook (and other hooks) pass void *param to their respective 
	handler, so param prob needs to be a struct when passing multiple 
	arguments.
- mlx_loop_hook is called when no event occurrs (useful for rerendering on zoom?)
- Separate mlx, window, and image

-Init
- create window
- create image
- write to image
- dump image to window
- add hooks
- initiate loop (now to enable closing the window, probably)
	listen for close clicks, resizes(?), zooms

! Remember to check for pointer creation success and
	clean up all pointers. Likely everything is malloced for.
*/

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

// Resizing; redraw the whole window? What?
int	main(int argc, char *argv[])
{
	t_data			data;

	init_clean(&data);
	if (argc == 2 || argc == 4)
		init(&data, argc, argv);
	else
		error_out("Try ./fractol [1, 2, mandlebrot or julia]\n", &data);
	render(&data);
	mlx_put_image_to_window(data.mlx, data.window, data.img, 0, 0);
	mlx_hook(data.window, 17, 1L << 17, exit_success, NULL);
	mlx_key_hook(data.window, key_press, &data);
	mlx_mouse_hook(data.window, mouse_press, &data);
	mlx_loop(data.mlx);
}
