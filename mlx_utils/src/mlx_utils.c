/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   mlx_utils.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: jceia <jceia@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2021/09/01 20:28:58 by jceia			 #+#	#+#			 */
/*   Updated: 2021/09/02 00:22:11 by jceia			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "mlx_utils.h"
#include "libft.h"
#include <stdio.h>

/*
 * TODO
 * add_shape
 * is a function that accepts a double (distance) and a int (color) as
 * arguments, 0 will add no shading to the color, whilst 1 will make the
 * color completely dark. 0.5 will dim it halfway, and .25 a quarter way.
 * You get the point.
 */
void	plot_pixel(t_data *data, t_point2D p, t_color color)
{
	int		x;
	int		y;
	char	*dst;

	x = (int)(p.x + 0.5);
	y = (int)(p.y + 0.5);
	if (x < 0 || x > data->width || y < 0 || y > data->height)
		return;
	dst = data->addr + (y*data->line_length + x*(data->bits_per_pixel / 8));
	*(unsigned int *)dst += create_trgb(color);
}
