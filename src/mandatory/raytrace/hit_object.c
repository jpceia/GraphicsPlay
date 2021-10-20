/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 17:05:21 by jceia             #+#    #+#             */
/*   Updated: 2021/10/20 23:35:03 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_bool	hit_object(const t_ray3d *ray, t_object *obj,
		float t_min, t_hit_record *record)
{
	record->obj = obj;
	record->color = obj->color;
	record->surf = obj->surf;
	if (obj->obj_type == SPHERE)
		return (hit_sphere(ray, obj->data, t_min, record));
	if (obj->obj_type == PLANE)
		return (hit_plane(ray, obj->data, t_min, record));
	if (obj->obj_type == CYLINDER)
		return (hit_cylinder(ray, obj->data, t_min, record));
	return (false);
}
