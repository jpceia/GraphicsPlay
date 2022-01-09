/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:17:16 by jceia             #+#    #+#             */
/*   Updated: 2022/01/09 20:59:30 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "matrix.h"

t_matrix	*matrix_empty(int nrows, int ncols)
{
	t_matrix	*m;

	if (nrows <= 0 || ncols <= 0)
		return (NULL);
	m = (t_matrix *)malloc(sizeof(*m));
	m->nrows = nrows;
	m->ncols = ncols;
	if (!m)
		return (m);
	m->data = (float *)malloc(nrows * ncols * sizeof(*(m->data)));
	if (!(m->data))
	{
		free(m);
		return (NULL);
	}
	return (m);
}

void	matrix_clear(t_matrix *m)
{
	if (m)
	{
		if (m->data)
			free(m->data);
		free(m);
		m = NULL;
	}
}

t_matrix	*matrix_zeros(int nrows, int ncols)
{
	int			idx;
	t_matrix	*m;

	m = matrix_empty(nrows, ncols);
	if (!m)
		return (NULL);
	idx = 0;
	while (idx < nrows * ncols)
		m->data[idx++] = 0;
	return (m);
}
