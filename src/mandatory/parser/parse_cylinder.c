/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:05:28 by jceia             #+#    #+#             */
/*   Updated: 2021/10/25 19:10:13 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_object	*parse_cylinder_from_line_aux(t_object *obj, char **s_split)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)malloc(sizeof(*cylinder));
	if (!cylinder)
		return (clean_exit(NULL, MALLOC_ERR, NULL, 0));
	if (!parse_vec3d(&cylinder->p, s_split[1]))
		return (clean_exit(cylinder, PARSE_VEC_ERR, free, 0));
	if (!parse_vec3d(&cylinder->direction, s_split[2]))
		return (clean_exit(cylinder, PARSE_VEC_ERR, free, 0));
	cylinder->direction = vec3d_normalize(cylinder->direction);
	cylinder->radius = ft_atof(s_split[3]) / 2;
	cylinder->height = ft_atof(s_split[4]);
	if (!parse_rgb(&obj->color, s_split[5]))
		return (clean_exit(cylinder, PARSE_RGB_ERR, free, 0));
	obj->data = cylinder;
	return (obj);
}

t_object	*parse_cylinder_from_line(t_object *obj, char *line)
{
	t_object	*res;
	char		**s_split;
	int			n;

	obj->obj_type = CYLINDER;
	n = ft_strwc(line, ' ');
	if (n != 6)
		return (clean_exit(NULL, LINE_FMT_ERR, NULL, 0));
	s_split = ft_split(line, ' ');
	if (!s_split)
		return (clean_exit(NULL, SPLIT_ERR, NULL, 0));
	res = parse_cylinder_from_line_aux(obj, s_split);
	ft_str_array_clear(s_split, n);
	if (!res)
		return (NULL);
	return (obj);
}
