/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:06:26 by jceia             #+#    #+#             */
/*   Updated: 2022/01/09 17:10:51 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_object	*parse_plane_from_line_aux(t_object *obj, char **s_split)
{
	t_plane	*plane;

	plane = (t_plane *)malloc(sizeof(*plane));
	if (!plane)
		return (clean_exit(NULL, MALLOC_ERR, NULL, 0));
	if (!parse_vec3d(&plane->p, s_split[1])
		|| !parse_vec3d(&plane->n, s_split[2]))
		return (clean_exit(plane, PARSE_VEC_ERR, free, 0));
	plane->n = vec3d_normalize(plane->n);
	obj->data = plane;
	return (obj);
}

t_object	*parse_plane_from_line(t_object *obj, char *line)
{
	t_object	*res;
	char		**s_split;
	int			n;

	obj->obj_type = PLANE;
	n = ft_strwc(line, ' ');
	if (n < 4)
		return (clean_exit(NULL, LINE_FMT_ERR, NULL, 0));
	s_split = ft_split(line, ' ');
	if (!s_split)
		return (clean_exit(NULL, SPLIT_ERR, free, 0));
	res = parse_plane_from_line_aux(obj, s_split);
	if (res)
		res = parse_color(obj, s_split + 3, n - 3);
	ft_str_array_clear(s_split, n);
	if (!res)
		return (NULL);
	return (obj);
}
