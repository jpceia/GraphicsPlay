/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_triangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:08:52 by jceia             #+#    #+#             */
/*   Updated: 2022/01/09 17:11:01 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_object	*parse_triangle_from_line_aux(t_object *obj, char **s_split)
{
	t_triangle	*triangle;

	triangle = (t_triangle *)malloc(sizeof(*triangle));
	if (!triangle)
		return (clean_exit(NULL, MALLOC_ERR, NULL, 0));
	if (!parse_vec3d(&triangle->p1, s_split[1])
		|| !parse_vec3d(&triangle->p2, s_split[2])
		|| !parse_vec3d(&triangle->p3, s_split[3]))
		return (clean_exit(triangle, PARSE_VEC_ERR, free, 0));
	obj->data = triangle;
	return (obj);
}

t_object	*parse_triangle_from_line(t_object *obj, char *line)
{
	t_object	*res;
	char		**s_split;
	int			n;

	obj->obj_type = TRIANGLE;
	n = ft_strwc(line, ' ');
	if (n < 5)
		return (clean_exit(NULL, LINE_FMT_ERR, NULL, 0));
	s_split = ft_split(line, ' ');
	if (!s_split)
		return (clean_exit(NULL, SPLIT_ERR, NULL, 0));
	res = parse_triangle_from_line_aux(obj, s_split);
	if (res)
		res = parse_color(obj, s_split + 4, n - 4);
	ft_str_array_clear(s_split, n);
	if (!res)
		return (NULL);
	return (obj);
}
