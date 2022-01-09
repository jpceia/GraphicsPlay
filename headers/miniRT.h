/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 10:58:52 by jceia             #+#    #+#             */
/*   Updated: 2022/01/09 17:41:23 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "vec.h"
# include "matrix.h"

# define WIN_WIDTH			1080
# define WIN_HEIGHT			720

# define BRIGHTNESS_RATIO	2

# define MALLOC_ERR			"malloc(3) failed"
# define LINE_FMT_ERR		"Line format error"
# define SPLIT_ERR			"ft_split failed"
# define PARSE_LINE_ERR		"Error parsing line"
# define PARSE_VEC_ERR		"Error parsing vector"
# define PARSE_RGB_ERR		"Error parsing RGB"
# define PARSE_COLOR_ERR	"Error parsing color"
# define PARSE_OBJ_ERR		"Error parsing object"
# define UNKNOWN_OBJ_ERR	"Unkown object type"

/*
 * 3D Ray
 */
typedef struct s_ray3d
{
	t_vec3d	origin;
	t_vec3d	direction;
}	t_ray3d;

t_ray3d		ray3d_create(t_vec3d origin, t_vec3d direction);
t_ray3d		ray3d_from_two_points(t_vec3d p, t_vec3d q);
t_vec3d		ray3d_at(const t_ray3d *ray, float t);
t_ray3d		ray3d_reflected(const t_ray3d *ray, t_vec3d normal);

/*
 * Color
 */
typedef t_vec3d	t_rgb;

typedef struct s_surf_props
{
	float	shininess;
	float	k_ambient;
	float	k_diffusion;
	float	k_specular;
	float	k_mirror;
	float	k_wrinkle;
}	t_surf_props;

int			create_trgb(t_rgb color);

/*
 * 3D Objects
 */
typedef enum e_object_type {
	PLANE,
	TRIANGLE,
	DISK,
	SPHERE,
	CYLINDER,
	CONE
}	t_obj_type;

typedef enum e_proj
{
	PROJ,
	PARALLEL
}	t_proj;

typedef struct s_ambient_light
{
	float	ratio;
	t_rgb	color;
}	t_ambient_light;

typedef struct s_camera
{
	t_vec3d		origin;
	t_vec3d		direction;
	float		fov;
	t_matrix	*basis;
	int			pixels_width;
	int			pixels_height;
	float		view_width;
	float		view_height;
	t_proj		proj_type;
}	t_camera;

typedef struct s_light
{
	t_vec3d	origin;
	float	ratio;
	t_rgb	color;
}	t_light;

typedef struct s_sphere
{
	t_vec3d	center;
	float	radius;
}	t_sphere;

typedef struct s_plane
{
	t_vec3d	p;
	t_vec3d	n;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3d	p;
	t_vec3d	direction;
	float	radius;
	float	height;
}	t_cylinder;

typedef struct s_triangle
{
	t_vec3d	p1;
	t_vec3d	p2;
	t_vec3d	p3;
	t_rgb	color;
}	t_triangle;

typedef struct s_disk
{
	t_vec3d	center;
	t_vec3d	n;
	float	radius;
	t_rgb	color;
}	t_disk;

typedef struct s_cone
{
	t_vec3d	p;
	t_vec3d	direction;
	float	radius;
	float	height;
	t_rgb	color;
}	t_cone;

typedef struct s_object
{
	t_obj_type		obj_type;
	void			*data;
	t_rgb			color;
	t_surf_props	surf;
}	t_object;

typedef struct s_data
{
	int		width;
	int		height;
	char	*file_name;
	t_ambient_light
			ambient;
	t_camera
			*camera;
	t_list	*lights;
	t_list	*objects;
	t_rgb	*buf;

	int		n_reflections;
	int		n_antialias;
}	t_data;

typedef struct s_args
{
	char	*scene_fname;
	char	*output_fname;
	char	*title;
	int		width;
	int		height;
	int		n_reflections;
	int		n_antialias;
}	t_args;

/*
 * Parser
 */
int			check_file_extension(char *fname, char const *ext);
t_data		*parse_data_from_file(t_data *vars, char *fname);
t_data		*parse_data_item_from_line(t_data *vars, char *line);
t_rgb		*parse_rgb(t_rgb *color, char *s);
t_object	*parse_color(t_object *obj, char **s_split, int n);
t_vec3d		*parse_vec3d(t_vec3d *p, char *s);
t_data		*parse_ambient_from_line(t_data *vars, char *line);
t_data		*parse_camera_from_line(t_data *vars, char *line);
t_data		*parse_light_from_line(t_data *vars, char *line);
t_data		*parse_object_from_line(t_data *vars, char *line);
t_object	*parse_sphere_from_line(t_object *obj, char *line);
t_object	*parse_plane_from_line(t_object *obj, char *line);
t_object	*parse_cylinder_from_line(t_object *obj, char *line);
t_object	*parse_triangle_from_line(t_object *obj, char *line);
t_object	*parse_disk_from_line(t_object *obj, char *line);
t_object	*parse_cone_from_line(t_object *obj, char *line);

/*
 * UTILS
 */

void		data_init(t_data *vars, const t_args *args);
void		data_draw_image(t_data *vars);
void 		create_bmp(const char *fname, int width, int height, t_rgb *pixels);

t_vec3d		vec3d_random(void);


/*
 * Clear
 */
void		data_clean(void *vars);
void		*clean_exit(void *ptr, char *msg, void (*del)(void *), int do_exit);

/*
 * Camera
 */
void		calculate_camera_params(t_camera *cam,
				int win_width, int win_height);
void		camera_clean(void *ptr);

/*
 * 2nd degree equations
 */

typedef struct s_float_pair
{
	float		min;
	float		max;
}	t_float_pair;

typedef struct s_deg2_eq_coefs
{
	float	a;
	float	b;
	float	c;
}	t_deg2_eq_coefs;

t_bool		deg2_eq_solutions(const t_deg2_eq_coefs *params, t_float_pair *t);

/*
 * Raytracer (Core)
 */
typedef struct s_hit_record
{
	t_vec3d			p;
	t_vec3d			normal;
	t_vec3d			reflected;
	t_object		*obj;
	t_rgb			color;
	t_surf_props	surf;
	float			t;
}	t_hit_record;

void		raytrace_scenario(t_data *vars);
		
t_rgb		hit_color(
				const t_hit_record *record,
				const t_data *vars,
				int n_reflections);

t_rgb		raytrace_single(
				const t_ray3d *ray,
				const t_data *vars,
				int n_reflections);

t_rgb		raytrace_pixel(int i, int j, int n, t_data *vars);

t_bool		raytrace_hit(const t_ray3d *ray, const t_data *vars,
				float t_min, t_hit_record *record);

t_bool		hit_object(const t_ray3d *ray, t_object *obj,
				float t_min, t_hit_record *record);

t_bool		hit_sphere(const t_ray3d *ray, const t_sphere *sphere,
				float t_min, t_hit_record *record);
t_bool		hit_plane(const t_ray3d *ray, const t_plane *plane,
				float t_min, t_hit_record *record);
t_bool		hit_cylinder(const t_ray3d *ray, const t_cylinder *cyclinder,
				float t_min, t_hit_record *record);
t_bool		hit_triangle(const t_ray3d *ray, const t_triangle *triangle,
				float t_min, t_hit_record *record);
t_bool		hit_disk(const t_ray3d *ray, const t_disk *disk,
				float t_min, t_hit_record *record);
t_bool		hit_cone(const t_ray3d *ray, const t_cone *cone,
				float t_min, t_hit_record *record);



#endif
