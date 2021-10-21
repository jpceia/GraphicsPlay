/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 02:53:52 by jceia             #+#    #+#             */
/*   Updated: 2021/10/21 01:38:27 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>

int	create_trgb(t_rgb v)
{
	return (
		(0) << 24
		| ((int)(255 * fminf(fmaxf(v.x, 0), 1))) << 16
		| ((int)(255 * fminf(fmaxf(v.y, 0), 1))) << 8
		| ((int)(255 * fminf(fmaxf(v.z, 0), 1)))
	);
}
