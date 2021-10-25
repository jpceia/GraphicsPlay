/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_triangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 22:08:52 by jceia             #+#    #+#             */
/*   Updated: 2021/10/25 18:02:50 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_object	*parse_triangle_from_line(t_object *obj, char *line)
{
	t_triangle	*triangle;
	char		**s_split;
	int			n;

	obj->obj_type = TRIANGLE;
	n = ft_strwc(line, ' ');
	if (n < 5)
		return (clean_exit(NULL, LINE_FMT_ERR, NULL, 0));
	triangle = (t_triangle *)malloc(sizeof(*triangle));
	if (!triangle)
		return (clean_exit(NULL, MALLOC_ERR, NULL, 0));
	s_split = ft_split(line, ' ');
	if (!s_split)
		return (clean_exit(triangle, SPLIT_ERR, free, 0));
	if (!parse_vec3d(&triangle->p1, s_split[1]))
		return (clean_exit(triangle, PARSE_VEC_ERR, free, 0));
	if (!parse_vec3d(&triangle->p2, s_split[2]))
		return (clean_exit(triangle, PARSE_VEC_ERR, free, 0));
	if (!parse_vec3d(&triangle->p3, s_split[3]))
		return (clean_exit(triangle, PARSE_VEC_ERR, free, 0));
	if (!parse_color(obj, s_split + 4, n - 4))
		return (clean_exit(triangle, PARSE_COLOR_ERR, free, 0));
	ft_str_array_clear(s_split, n);
	obj->data = triangle;
	return (obj);
}
