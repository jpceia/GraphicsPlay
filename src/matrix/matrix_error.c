/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 17:30:19 by jceia             #+#    #+#             */
/*   Updated: 2022/01/09 21:20:08 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "libft.h"
#include <stdio.h>

t_bool	check_matrix_nrows(int nrows, int _nrows)
{
	if (nrows != _nrows)
	{
		fprintf(stderr, "Row number mismatch\n");
		return (false);
	}
	return (true);
}

t_bool	check_matrix_ncols(int ncols, int _ncols)
{
	if (ncols != _ncols)
	{
		fprintf(stderr, "Column number mismatch\n");
		return (false);
	}
	return (true);
}
