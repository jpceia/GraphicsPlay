/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vec3D.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 08:05:16 by jceia             #+#    #+#             */
/*   Updated: 2021/10/08 08:28:49 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3d	*parse_vec3d(t_vec3d *p, char *s)
{
	int		n;
	char	**s_split;

	n = ft_strwc(s, ',');
	if (n != 3)
		return (clean_exit(NULL, "Incorrect coordinates format", NULL, 0));
	s_split = ft_split(s, ',');
	if (!s_split)
		return (clean_exit(NULL, "Error spliting string", NULL, 0));
	p->x = ft_atof(s_split[0]);
	p->y = ft_atof(s_split[1]);
	p->z = ft_atof(s_split[2]);
	ft_str_array_clear(s_split, n);
	return (p);
}
