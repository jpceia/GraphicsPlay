/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 02:53:52 by jceia             #+#    #+#             */
/*   Updated: 2022/01/09 17:10:13 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>

int	create_trgb(t_rgb v)
{
	return (
		(0) << 24
		| ((int)(255 * atan(fmaxf(v.x, 0) * BRIGHTNESS_RATIO) * 2 / M_PI)) << 16
		| ((int)(255 * atan(fmaxf(v.y, 0) * BRIGHTNESS_RATIO) * 2 / M_PI)) << 8
		| ((int)(255 * atan(fmaxf(v.z, 0) * BRIGHTNESS_RATIO) * 2 / M_PI))
	);
}
