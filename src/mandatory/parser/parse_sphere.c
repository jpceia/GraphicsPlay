/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:05:57 by jceia             #+#    #+#             */
/*   Updated: 2021/10/25 19:23:00 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_object	*parse_sphere_from_line_aux(t_object *obj, char **s_split)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)malloc(sizeof(*sphere));
	if (!sphere)
		return (clean_exit(NULL, MALLOC_ERR, NULL, 0));
	if (!parse_vec3d(&sphere->center, s_split[1]))
		return (clean_exit(sphere, PARSE_VEC_ERR, free, 0));
	sphere->radius = ft_atof(s_split[2]) / 2;
	if (!parse_rgb(&obj->color, s_split[3]))
		return (clean_exit(sphere, PARSE_RGB_ERR, free, 0));
	obj->data = sphere;
	return (obj);
}

t_object	*parse_sphere_from_line(t_object *obj, char *line)
{
	t_object	*res;
	char		**s_split;
	int			n;

	obj->obj_type = SPHERE;
	n = ft_strwc(line, ' ');
	if (n != 4)
		return (clean_exit(NULL, LINE_FMT_ERR, NULL, 0));
	s_split = ft_split(line, ' ');
	if (!s_split)
		return (clean_exit(NULL, SPLIT_ERR, NULL, 0));
	res = parse_sphere_from_line_aux(obj, s_split);
	ft_str_array_clear(s_split, n);
	if (!res)
		return (NULL);
	return (obj);
}
