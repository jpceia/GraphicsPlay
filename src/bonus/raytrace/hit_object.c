/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:43:51 by jceia             #+#    #+#             */
/*   Updated: 2021/10/20 17:07:09 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_bool	hit_object(const t_ray3d *ray, t_object *obj,
		float t_min, t_hit_record *record)
{
	record->obj = obj;
	if (obj->obj_type == SPHERE)
		return (hit_sphere(ray, obj->data, t_min, record));
	if (obj->obj_type == PLANE)
		return (hit_plane(ray, obj->data, t_min, record));
	if (obj->obj_type == CYLINDER)
		return (hit_cylinder(ray, obj->data, t_min, record));
	if (obj->obj_type == TRIANGLE)
		return (hit_triangle(ray, obj->data, t_min, record));
	if (obj->obj_type == DISK)
		return (hit_disk(ray, obj->data, t_min, record));
	if (obj->obj_type == CONE)
		return (hit_cone(ray, obj->data, t_min, record));
	return (false);
}
