/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:48:30 by jceia             #+#    #+#             */
/*   Updated: 2021/10/25 17:52:57 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static t_object	*parse_cone_from_line_aux(t_object *obj, char **s_split)
{
	t_cone	*cone;

	obj->obj_type = CONE;
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
	char	**s_split;
	int		n;

	n = ft_strwc(line, ' ');
	if (n < 6)
		return (clean_exit(NULL, "Line with incorrect format", NULL, 0));
	s_split = ft_split(line, ' ');
	if (!s_split)
		return (clean_exit(NULL, "Error spliting line", NULL, 0));
	obj = parse_cone_from_line_aux(obj, s_split);
	if (!parse_color(obj, s_split + 5, n - 5))
	{
		ft_str_array_clear(s_split, n);
		return (NULL);
	}
	ft_str_array_clear(s_split, n);
	return (obj);
}
