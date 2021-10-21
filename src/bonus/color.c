/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 02:53:52 by jceia             #+#    #+#             */
/*   Updated: 2021/10/21 01:42:47 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"
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
