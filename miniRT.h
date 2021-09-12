/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 10:58:52 by jceia             #+#    #+#             */
/*   Updated: 2021/09/12 15:20:15 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx_utils.h"
# include "libft.h"

# define WIN_WIDTH	800
# define WIN_HEIGHT	480

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

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
	t_rgb	color;
}	t_ambient_light;

typedef struct s_camera
{
	t_vec3D	origin;
	t_vec3D	direction;
	float	fov;
	t_vec3D	basis_x;
	t_vec3D	basis_y;
	int		pixels_width;
	int		pixels_height;
	float	view_width;
	float	view_height;
}	t_camera;

typedef struct s_light
{
	t_vec3D	origin;
	float	ratio;
	t_rgb	color;
}	t_light;

typedef struct s_sphere
{
	t_vec3D	center;
	float	radius;
	t_rgb	color;
}	t_sphere;

typedef struct s_plane
{
	t_vec3D	p;
	t_vec3D	n;
	t_rgb	color;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3D	p;
	t_vec3D	n;
	float	radius;
	float	height;
	t_rgb	color;
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
int		parse_color(t_rgb *color, char *s);
int		parse_vec3D(t_vec3D *p, char *s);
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

/*
 * Camera
 */
void	calculate_camera_params(t_camera *cam, int win_width, int win_height);
void	calculate_camera_list_params(t_list *cam_list,
			int win_width, int win_height);

/*
 * Raytracer (Core)
 */

typedef struct s_hit_record
{
	t_vec3D		p;
	t_vec3D		n;
	t_object	*obj;
	t_rgb		base_color;
	float		t;
}	t_hit_record;

t_rgb	hit_color(const t_hit_record *hit_record, const t_scenario *scenario);
t_bool	hit_object(const t_ray3D *ray, t_object *obj, t_hit_record *record);
void	raytrace_scenario(const t_scenario *scenario, t_rgb *buf);
t_rgb	raytrace_single_ray(const t_ray3D *ray, const t_scenario *scenario);

#endif
