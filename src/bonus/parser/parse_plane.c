/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:06:26 by jceia             #+#    #+#             */
/*   Updated: 2021/10/20 22:15:20 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_object	*parse_plane_from_line(t_object *obj, char *line)
{
	t_plane	*plane;
	char	**s_split;
	int		n;

	obj->obj_type = PLANE;
	n = ft_strwc(line, ' ');
	if (n < 4)
		return (clean_exit(NULL, "Line with incorrect format", NULL, 0));
	plane = (t_plane *)malloc(sizeof(*plane));
	if (!plane)
		return (clean_exit(NULL, "Error allocating memory", NULL, 0));
	s_split = ft_split(line, ' ');
	if (!s_split)
		return (clean_exit(plane, "Error spliting line", free, 0));
	if (!parse_vec3d(&plane->p, s_split[1]))
		return (clean_exit(plane, "Error parsing vector", free, 0));
	if (!parse_vec3d(&plane->n, s_split[2]))
		return (clean_exit(plane, "Error parsing vector", free, 0));
	if (!parse_color(obj, s_split + 3, n - 3))
		return (clean_exit(plane, "Error parsing rgb color", free, 0));
	plane->n = vec3d_normalize(plane->n);
	ft_str_array_clear(s_split, n);
	obj->data = plane;
	return (obj);
}
