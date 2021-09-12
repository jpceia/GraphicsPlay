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

/*
 * TODO
 * add_shape
 * is a function that accepts a double (distance) and a int (color) as
 * arguments, 0 will add no shading to the color, whilst 1 will make the
 * color completely dark. 0.5 will dim it halfway, and .25 a quarter way.
 * You get the point.
 */
void	plot_pixel(t_data *data, float x, float y, t_rgb color)
{
	int		i;
	int		j;
	char	*dst;

	i = (int)(x + 0.5);
	j = (int)(y + 0.5);
	if (i < 0 || i > data->width || j < 0 || j > data->height)
		return;
	dst = data->addr + (j*data->line_length + i*(data->bits_per_pixel / 8));
	*(unsigned int *)dst += create_trgb(color);
}
