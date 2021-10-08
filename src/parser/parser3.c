/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 12:26:46 by jceia             #+#    #+#             */
/*   Updated: 2021/10/08 02:25:23 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "miniRT.h"

int	parse_object_from_line(t_scenario *scenario, char *line)
{
	t_object	*obj;
	int			status;	

	obj = (t_object *)malloc(sizeof(*obj));
	if (!obj)
		return (exit_malloc_fail());
	if (strncmp(line, "sp ", 3) == 0)
		status = parse_sphere_from_line(obj, line);
	else if (strncmp(line, "pl ", 3) == 0)
		status = parse_plane_from_line(obj, line);
	else if (strncmp(line, "cy ", 3) == 0)
		status = parse_plane_from_line(obj, line);
	else
		status = -1;
	if (status < 0)
		return (exit_free(obj));
	ft_lstpush_front(&scenario->objects, obj);
	return (0);
}

int	parse_sphere_from_line(t_object *obj, char *line)
{
	t_sphere	*sphere;
	char		**s_split;
	int			status;
	int			N;

	obj->obj_type = SPHERE;
	N = ft_strwc(line, ' ');
	if (N != 4)
		return (exit_invalid_line(line));
	sphere = (t_sphere *)malloc(sizeof(*sphere));
	if (!sphere)
		return (exit_malloc_fail());
	s_split = ft_split(line, ' ');
	if (!s_split)
		return (-1);
	status = parse_vec3d(&sphere->center, s_split[1]);
	sphere->radius = ft_atof(s_split[2]) / 2;
	status += parse_color(&sphere->color, s_split[3]);
	ft_str_array_clear(s_split, N);
	if (status < 0)
		return (exit_free(sphere));
	obj->data = sphere;
	return (0);
}

int	parse_plane_from_line(t_object *obj, char *line)
{
	t_plane	*plane;
	char	**s_split;
	int		status;
	int		N;

	obj->obj_type = PLANE;
	N = ft_strwc(line, ' ');
	if (N != 4)
		return (exit_invalid_line(line));
	plane = (t_plane *)malloc(sizeof(*plane));
	if (!plane)
		return (exit_malloc_fail());
	s_split = ft_split(line, ' ');
	if (!s_split)
		return (-1);
	status = parse_vec3d(&plane->p, s_split[1]);
	status += parse_vec3d(&plane->n, s_split[2]);
	status += parse_color(&plane->color, s_split[3]);
	ft_str_array_clear(s_split, N);
	if (status < 0)
		return (exit_free(plane));
	obj->data = plane;
	return (0);
}

int	parse_cyclinder_from_line(t_object *obj, char *line)
{
	t_cylinder	*cylinder;
	char		**s_split;
	int			status;
	int			N;

	obj->obj_type = CYLINDER;
	N = ft_strwc(line, ' ');
	if (N != 6)
		return (exit_invalid_line(line));
	cylinder = (t_cylinder *)malloc(sizeof(*cylinder));
	if (!cylinder)
		return (exit_malloc_fail());
	s_split = ft_split(line, ' ');
	if (!s_split)
		return (-1);
	status = parse_vec3d(&cylinder->p, s_split[1]);
	status += parse_vec3d(&cylinder->n, s_split[2]);
	cylinder->radius = ft_atof(s_split[3]) / 2;
	cylinder->height = ft_atof(s_split[4]);
	status += parse_color(&cylinder->color, s_split[5]);
	ft_str_array_clear(s_split, N);
	if (status < 0)
		return (exit_free(cylinder));
	obj->data = cylinder;
	return (0);
}
