/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 10:58:52 by jceia             #+#    #+#             */
/*   Updated: 2021/10/20 21:34:00 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include "miniRT.h"
# include "libft.h"

# define N_ANTIALIAS		3
# define BRIGHTNESS_RATIO	2
# ifdef OS_Linux
#  define K_LEFT_ARROW	65361
#  define K_RIGHT_ARROW	65363
#  define K_UP_ARROW	65362
#  define K_DOWN_ARROW	65364
#  define K_ESC			65307
#  define K_A			97
#  define K_D			100
#  define K_W			119
#  define K_S			115
# else
#  define K_LEFT_ARROW	123
#  define K_RIGHT_ARROW	124
#  define K_UP_ARROW	126
#  define K_DOWN_ARROW	125
#  define K_ESC			53
#  define K_A			0
#  define K_D			2
#  define K_W			13
#  define K_S			1
# endif

/*
 * 3D Objects
 */

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

/*
 * Parser
 */
t_object	*parse_color(t_object *obj, char **s_split, int n);

t_object	*parse_triangle_from_line(t_object *obj, char *line);
t_object	*parse_disk_from_line(t_object *obj, char *line);
t_object	*parse_cone_from_line(t_object *obj, char *line);

/*
 * Raytracer (Core)
 */

t_rgb		raytrace_pixel(int i, int j, int n, t_data *vars);

t_bool		hit_triangle(const t_ray3d *ray, const t_triangle *triangle,
				float t_min, t_hit_record *record);
t_bool		hit_disk(const t_ray3d *ray, const t_disk *disk,
				float t_min, t_hit_record *record);
t_bool		hit_cone(const t_ray3d *ray, const t_cone *cone,
				float t_min, t_hit_record *record);

#endif
