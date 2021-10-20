/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 20:25:40 by jceia             #+#    #+#             */
/*   Updated: 2021/10/20 20:25:41 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_rgb	*parse_rgb(t_rgb *color, char *s)
{
	int		n;
	char	**s_split;

	n = ft_strwc(s, ',');
	if (n != 3)
		return (clean_exit(NULL, "Incorrect color format", NULL, 0));
	s_split = ft_split(s, ',');
	if (!s_split)
		return (clean_exit(NULL, "Error spliting string", NULL, 0));
	color->x = (float)ft_atoi(s_split[0]) / 255;
	color->y = (float)ft_atoi(s_split[1]) / 255;
	color->z = (float)ft_atoi(s_split[2]) / 255;
	ft_str_array_clear(s_split, n);
	return (color);
}
