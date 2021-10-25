/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:06:26 by jceia             #+#    #+#             */
/*   Updated: 2021/10/25 18:02:54 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_object	*parse_plane_from_line(t_object *obj, char *line)
{
	t_plane	*plane;
	char	**s_split;
	int		n;

	obj->obj_type = PLANE;
	n = ft_strwc(line, ' ');
	if (n != 4)
		return (clean_exit(NULL, LINE_FMT_ERR, NULL, 0));
	plane = (t_plane *)malloc(sizeof(*plane));
	if (!plane)
		return (clean_exit(NULL, MALLOC_ERR, NULL, 0));
	s_split = ft_split(line, ' ');
	if (!s_split)
		return (clean_exit(plane, SPLIT_ERR, free, 0));
	if (!parse_vec3d(&plane->p, s_split[1]))
		return (clean_exit(plane, PARSE_VEC_ERR, free, 0));
	if (!parse_vec3d(&plane->n, s_split[2]))
		return (clean_exit(plane, PARSE_VEC_ERR, free, 0));
	if (!parse_rgb(&obj->color, s_split[3]))
		return (clean_exit(plane, PARSE_RGB_ERR, free, 0));
	plane->n = vec3d_normalize(plane->n);
	ft_str_array_clear(s_split, n);
	obj->data = plane;
	return (obj);
}
