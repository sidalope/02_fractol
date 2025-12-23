/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abisani <abisani@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 23:18:20 by abisani           #+#    #+#             */
/*   Updated: 2025/12/23 13:53:31 by abisani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

# define WIDTH 1200
# define HEIGHT 900
# define MAX_ITERATIONS 50
# define COLOUR 0x00F0cfff

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
	int			fractal;
	double		i_factor;
	double		r_factor;
	double		min_r;
	double		max_r;
	double		min_i;
	double		max_i;
	double		kr;
	double		ki;
	int			render;
	int			colour;
}				t_data;

enum e_fractals
{
	MANDELBROT = 1,
	JULIA = 2
};

// Utils
double	ft_atof(char *str);
int		parse_hex_int(char *str);
void	print_usage_err(t_data *data);

// Exit and Error handling
void	clean_up(t_data *data);
int		exit_success(void *data);
void	error_out(char *err_msg, t_data *data);

// Window management & IO
int		key_press(int keycode, void *param);
int		mouse_press(int button, int x, int y, void *param);

// Rendering
void	render(t_data *data);

// Initialisation
void	init_clean(t_data *data);
void	init(t_data *data, int argc, char *argv[]);

// Fractals
int		mandelbrot(double cr, double ci);
int		julia(double z_r, double z_i, double kr, double ki);

#endif
