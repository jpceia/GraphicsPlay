/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_geometry.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 07:16:53 by jceia             #+#    #+#             */
/*   Updated: 2021/10/13 10:17:26 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "matrix.h"

t_matrix	*matrix_scaling3d(const t_vec3d *s)
{
	t_matrix	*m;

	m = matrix_zeros(3, 3);
	if (!m)
		return (NULL);
	m->data[0] = s->x;
	m->data[4] = s->y;
	m->data[8] = s->z;
	return (m);
}

t_vec3d	*matrix_mul_vec3d(t_matrix *m, const t_vec3d *p)
{
	t_vec3d	*q;

	q = malloc(sizeof(*q));
	if (!q)
	{
		perror("malloc(3) error");
		return (NULL);
	}
	if (!m)
	{
		free(q);
		return (NULL);
	}
	if (!check_matrix_ncols(m->ncols, 3) || !check_matrix_nrows(m->nrows, 3))
	{
		free(q);
		return (NULL);
	}
	q->x = m->data[0] * p->x + m->data[1] * p->y + m->data[2] * p->z;
	q->y = m->data[3] * p->x + m->data[4] * p->y + m->data[5] * p->z;
	q->z = m->data[6] * p->x + m->data[7] * p->y + m->data[8] * p->z;
	return (q);
}
