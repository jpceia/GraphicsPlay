/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 20:59:41 by jceia             #+#    #+#             */
/*   Updated: 2021/09/08 14:40:37 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H

# include "geom.h"
# include "color.h"

typedef enum
{
	ISO,
	PARALLEL
}	t_projection;

typedef	struct s_camera
{
	t_projection	projection;
}	t_camera;


typedef	struct s_mouse
{
	float	x;
	float	y;
}	t_mouse;

typedef struct s_map
{
	float	width;
	float	height;
	float	z_min;
	float	z_max;
}	t_map;


typedef struct s_data
{
	void		*mlx;
	void		*win;

	void		*img;
	char		*addr;
	int			width;
	int			height;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_mouse		*mouse;
	t_camera	*camera;
}	t_data;




typedef struct s_vars {

}	t_vars;

void	plot_pixel(t_data *data, t_point2D p, t_color color);

#endif