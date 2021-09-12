/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 20:59:41 by jceia             #+#    #+#             */
/*   Updated: 2021/09/12 15:12:08 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H

typedef	enum e_coord
{
	COORD_X,
	COORD_Y,
	COORD_Z
}	t_coord;

typedef struct s_vec3D
{
	float	x;
	float	y;
	float	z;
}	t_vec3D;

typedef t_vec3D t_rgb;

typedef enum
{
	PROJ,
	PARALLEL
}	t_projection;

typedef	struct s_mouse
{
	float	x;
	float	y;
}	t_mouse;


typedef struct s_data
{
	void		*mlx;
	void		*win;

	void		*img;
	char		*addr;
	int			width;
	int			height;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_mouse		*mouse;
}	t_data;


typedef struct s_vars {

}	t_vars;

/*
 * MLX
 */
void	plot_pixel(t_data *data, float x, float y, t_rgb color);
void	image_from_matrix(t_data *data, t_rgb *buf);

/*
 * 3D Vec
 */

typedef struct s_ray3D
{
	t_vec3D	origin;
	t_vec3D	direction;
}	t_ray3D;

t_vec3D	vec3D_create(float x, float y, float z);
t_vec3D	vec3D_origin(void);
t_vec3D	vec3D_subtract(t_vec3D q, t_vec3D p);
t_vec3D	vec3D_add(t_vec3D p, t_vec3D v);
float	vec3D_coord(t_vec3D p, t_coord coord);

t_vec3D	vec3D_scalar_mul(t_vec3D v, float l);
t_vec3D	vec3D_normalize(t_vec3D v);
float	vec3D_dot_product(t_vec3D u, t_vec3D v);
t_vec3D	vec3D_cross_product(t_vec3D u, t_vec3D v);
t_vec3D	vec3D_interpolate(t_vec3D p, t_vec3D q, float t);

float	vec3D_norm_squared(t_vec3D v);
float	vec3D_norm(t_vec3D v);
float	vec3D_angle(t_vec3D u, t_vec3D v);

/*
 * 3D Ray
 */
t_ray3D	ray3D_from_two_points(t_vec3D p, t_vec3D q);
t_vec3D	ray3D_at(const t_ray3D *ray, float t);

/*
 * Color
 */

int		create_trgb(t_rgb color);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);

#endif