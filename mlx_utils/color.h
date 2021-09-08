/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 23:28:12 by jceia             #+#    #+#             */
/*   Updated: 2021/09/08 14:39:36 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef struct s_color
{
	float	t;
	float	r;
	float	g;
	float	b;
}	t_color;

int		create_trgb(t_color color);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);

t_color color_interp(t_color c1, t_color c2, float t);
t_color color_create(float t, float r, float g, float b);

#endif