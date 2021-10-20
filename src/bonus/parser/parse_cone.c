/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:48:30 by jceia             #+#    #+#             */
/*   Updated: 2021/10/20 15:55:15 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_object	*parse_cone_from_line(t_object *obj, char *line)
{
	t_cone	*cone;
	char	**s_split;
	int		n;

	obj->obj_type = CONE;
	n = ft_strwc(line, ' ');
	if (n != 6)
		return (clean_exit(NULL, "Line with incorrect format", NULL, 0));
	cone = (t_cone *)malloc(sizeof(*cone));
	if (!cone)
		return (clean_exit(NULL, "Error allocating memory", NULL, 0));
	s_split = ft_split(line, ' ');
	if (!s_split)
		return (clean_exit(cone, "Error spliting line", free, 0));
	if (!parse_vec3d(&cone->p, s_split[1]))
		return (clean_exit(cone, "Error parsing vector", free, 0));
	if (!parse_vec3d(&cone->direction, s_split[2]))
		return (clean_exit(cone, "Error parsing vector", free, 0));
	cone->direction = vec3d_normalize(cone->direction);
	cone->radius = ft_atof(s_split[3]) / 2;
	cone->height = ft_atof(s_split[4]);
	if (!parse_color(&cone->color, s_split[5]))
		return (clean_exit(cone, "Error parsing rgb color", free, 0));
	ft_str_array_clear(s_split, n);
	obj->data = cone;
	return (obj);
}
