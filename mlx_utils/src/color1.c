/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 02:53:52 by jceia             #+#    #+#             */
/*   Updated: 2021/09/08 14:00:26 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

int	create_trgb(t_color color)
{
	return (((int)(255.999 * color.t)) << 24
		| ((int)(255.999 * color.r)) << 16
		| ((int)(255.999 * color.g)) << 8
		| ((int)(255.999 * color.b)));
}

int	get_t(int trgb)
{
	return (trgb & (0xFF << 24));
}

int	get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

int	get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}
