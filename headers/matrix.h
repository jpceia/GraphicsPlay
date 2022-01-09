/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 15:23:30 by jceia             #+#    #+#             */
/*   Updated: 2022/01/09 21:01:10 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include <stdlib.h>
# include "libft.h"
# include "vec.h"

typedef struct s_matrix
{
	int		ncols;
	int		nrows;
	float	*data;
}	t_matrix;

t_bool		check_matrix_nrows(int nrows, int _nrows);
t_bool		check_matrix_ncols(int ncols, int _ncols);

t_matrix	*matrix_empty(int ncols, int nrows);
void		matrix_clear(t_matrix *m);
t_matrix	*matrix_zeros(int ncols, int nrows);
void		matrix_print(t_matrix *m);

t_vec3d		matrix_mul_vec3d(t_matrix *m, const t_vec3d *p);

#endif
