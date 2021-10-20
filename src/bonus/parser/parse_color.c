/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 21:05:04 by jceia             #+#    #+#             */
/*   Updated: 2021/10/20 23:37:12 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_object	*parse_color(t_object *obj, char **s_split, int n)
{
	if (!parse_rgb(&obj->color, s_split[0]))
		return (NULL);
	if (n > 1)
		obj->surf.k_ambient = ft_atof(s_split[1]);
	if (n > 2)
		obj->surf.k_diffusion = ft_atof(s_split[2]);
	if (n > 3)
		obj->surf.k_specular = ft_atof(s_split[3]);
	if (n > 4)
		obj->surf.shininess = ft_atof(s_split[4]);
	if (n > 5)
		obj->surf.k_mirror = ft_atof(s_split[5]);
	if (n > 6)
		obj->surf.k_wrinkle = ft_atof(s_split[6]);
	return (obj);
}
