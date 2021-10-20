/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:05:28 by jceia             #+#    #+#             */
/*   Updated: 2021/10/20 18:36:06 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_cylinder	*parse_cylinder_from_line_aux(char *line)
{
	t_cylinder	*cylinder;
	char		**s_split;
	int			n;

	n = ft_strwc(line, ' ');
	if (n != 6)
		return (clean_exit(NULL, "Line with incorrect format", NULL, 0));
	cylinder = (t_cylinder *)malloc(sizeof(*cylinder));
	if (!cylinder)
		return (clean_exit(NULL, "Error allocating memory", NULL, 0));
	s_split = ft_split(line, ' ');
	if (!s_split)
		return (clean_exit(cylinder, "Error spliting line", free, 0));
	if (!parse_vec3d(&cylinder->p, s_split[1]))
		return (clean_exit(cylinder, "Error parsing vector", free, 0));
	if (!parse_vec3d(&cylinder->direction, s_split[2]))
		return (clean_exit(cylinder, "Error parsing vector", free, 0));
	cylinder->direction = vec3d_normalize(cylinder->direction);
	cylinder->radius = ft_atof(s_split[3]) / 2;
	cylinder->height = ft_atof(s_split[4]);
	if (!parse_color(&cylinder->color, s_split[5]))
		return (clean_exit(cylinder, "Error parsing rgb color", free, 0));
	ft_str_array_clear(s_split, n);
	return (cylinder);
}

t_object	*parse_cylinder_from_line(t_object *obj, char *line)
{
	obj->obj_type = CYLINDER;
	obj->data = parse_cylinder_from_line_aux(line);
	if (!obj->data)
		return (NULL);
	return (obj);
}
