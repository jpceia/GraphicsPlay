/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 12:26:46 by jceia             #+#    #+#             */
/*   Updated: 2021/10/25 18:05:23 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static t_object	*empty_object(void)
{
	t_object	*obj;

	obj = (t_object *)malloc(sizeof(*obj));
	if (!obj)
		return (clean_exit(NULL, MALLOC_ERR, NULL, 0));
	ft_memset(obj, 0, sizeof(*obj));
	obj->surf.shininess = 1;
	obj->surf.k_ambient = 1;
	obj->surf.k_diffusion = 1;
	return (obj);
}

t_data	*parse_object_from_line(t_data *vars, char *line)
{
	t_object	*obj;
	t_object	*res;

	obj = empty_object();
	if (!obj)
		return (NULL);
	if (strncmp(line, "sp ", 3) == 0)
		res = parse_sphere_from_line(obj, line);
	else if (strncmp(line, "pl ", 3) == 0)
		res = parse_plane_from_line(obj, line);
	else if (strncmp(line, "cy ", 3) == 0)
		res = parse_cylinder_from_line(obj, line);
	else if (strncmp(line, "tr ", 3) == 0)
		res = parse_triangle_from_line(obj, line);
	else if (strncmp(line, "di ", 3) == 0)
		res = parse_disk_from_line(obj, line);
	else if (strncmp(line, "co ", 3) == 0)
		res = parse_cone_from_line(obj, line);
	else
		return (clean_exit(obj, UNKNOWN_OBJ_ERR, free, 0));
	if (!res)
		return (clean_exit(obj, PARSE_OBJ_ERR, free, 0));
	ft_lstpush_front(&vars->objects, obj);
	return (vars);
}
