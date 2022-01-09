/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:48:30 by jceia             #+#    #+#             */
/*   Updated: 2022/01/09 17:11:12 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_object	*parse_cone_from_line_aux(t_object *obj, char **s_split)
{
	t_cone	*cone;

	cone = (t_cone *)malloc(sizeof(*cone));
	if (!cone)
		return (clean_exit(NULL, MALLOC_ERR, NULL, 0));
	if (!parse_vec3d(&cone->p, s_split[1]))
		return (clean_exit(cone, PARSE_VEC_ERR, free, 0));
	if (!parse_vec3d(&cone->direction, s_split[2]))
		return (clean_exit(cone, PARSE_VEC_ERR, free, 0));
	cone->direction = vec3d_normalize(cone->direction);
	cone->radius = ft_atof(s_split[3]) / 2;
	cone->height = ft_atof(s_split[4]);
	obj->data = cone;
	return (obj);
}

t_object	*parse_cone_from_line(t_object *obj, char *line)
{
	t_object	*res;
	char		**s_split;
	int			n;

	obj->obj_type = CONE;
	n = ft_strwc(line, ' ');
	if (n < 6)
		return (clean_exit(NULL, LINE_FMT_ERR, NULL, 0));
	s_split = ft_split(line, ' ');
	if (!s_split)
		return (clean_exit(NULL, SPLIT_ERR, NULL, 0));
	res = parse_cone_from_line_aux(obj, s_split);
	if (res)
		res = parse_color(obj, s_split + 5, n - 5);
	ft_str_array_clear(s_split, n);
	if (!res)
		return (NULL);
	return (obj);
}
