/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 10:58:52 by jceia             #+#    #+#             */
/*   Updated: 2021/09/08 15:56:48 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "geom.h"
# include "libft.h"

/*
 * 3D Objects
 */

typedef enum e_object_type {
	SPHERE,
	PLANE,
	CYLINDER
}	t_object_type;

typedef struct s_ambient_light
{
	float	ratio;
	t_color	color;
}	t_ambient_light;

typedef struct s_camera
{
	t_point3D	orig;
	t_vector3D	direction;
	float		fov;
}	t_camera;

typedef struct s_light
{
	t_point3D	orig;
	float		ratio;
	t_color		color;
}	t_light;

typedef struct s_sphere
{
	t_point3D	center;
	float		radius;
	t_color		color;
}	t_sphere;

typedef struct s_plane
{
	t_point3D	p;
	t_vector3D	n;
	t_color		color;
}	t_plane;

typedef struct s_cylinder
{
	t_point3D	p;
	t_vector3D	n;
	float		radius;
	float		height;
	t_color		color;
}	t_cylinder;

typedef struct s_object
{
	t_object_type	obj_type;
	void			*data;
}	t_object;

typedef struct s_scenario
{
	t_ambient_light	ambient;
	t_list			*cameras;
	t_list			*lights;
	t_list			*objects;
}	t_scenario;

/*
 * Parser
 */

int		check_file_extension(char *fname, char const *ext);
int		exit_invalid_line(char *line);
int		exit_malloc_fail(void);
int		exit_free(void *p);
void	parse_scenario_from_file(t_scenario *scenario, char *fname);
int		parse_color(t_color *color, char *s);
int		parse_point3D(t_point3D	*p, char *s);
int		parse_ambient_from_line(t_scenario *scenario, char *line);
int		parse_camera_from_line(t_scenario *scenario, char *line);
int		parse_light_from_line(t_scenario *scenario, char *line);
int		parse_object_from_line(t_scenario *scenario, char *line);
int		parse_sphere_from_line(t_object *obj, char *line);
int		parse_plane_from_line(t_object *obj, char *line);
int		parse_cyclinder_from_line(t_object *obj, char *line);

/*
 * Clear
 */
void	scenario_init(t_scenario *scenario);
void	clear_scenario(t_scenario *scenario);

#endif
