/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 12:26:46 by jceia             #+#    #+#             */
/*   Updated: 2021/10/20 16:40:11 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "miniRT.h"

t_data	*parse_object_from_line(t_data *vars, char *line)
{
	t_object	*obj;

	obj = (t_object *)malloc(sizeof(*obj));
	if (!obj)
		return (clean_exit(NULL, "Error allocating memory", NULL, 0));
	if (strncmp(line, "sp ", 3) == 0)
	{
		if (!parse_sphere_from_line(obj, line))
			return (clean_exit(obj, "Unable to parse sphere object", free, 0));
	}
	else if (strncmp(line, "pl ", 3) == 0)
	{
		if (!parse_plane_from_line(obj, line))
			return (clean_exit(obj, "Unable to parse plane object", free, 0));
	}
	else if (strncmp(line, "cy ", 3) == 0)
	{
		if (!parse_cylinder_from_line(obj, line))
			return (clean_exit(obj, "Unable to parse cylinder obj", free, 0));
	}
	else
		return (clean_exit(obj, "Unrecognized object type", free, 0));
	ft_lstpush_front(&vars->objects, obj);
	return (vars);
}
