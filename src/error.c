/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 04:07:55 by jceia             #+#    #+#             */
/*   Updated: 2021/10/08 02:40:23 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	check_file_extension(char *fname, char *ext)
{
	char	**s_split;
	int		n;

	n = ft_strwc(fname, '.');
	if (n < 1)
	{
		ft_putendl_error("Error");
		ft_putendl_error("File has no extension");
		return (-1);
	}
	s_split = ft_split(fname, '.');
	if (ft_strcmp(s_split[n - 1], ext) != 0)
	{
		ft_str_array_clear(s_split, n);
		ft_putendl_error("Error");
		ft_putstr_error("File extension needs to be .");
		ft_putendl_error(ext);
		return (-1);
	}
	ft_str_array_clear(s_split, n);
	return (0);
}

int	exit_invalid_line(char *line)
{
	ft_putendl_error("Error");
	ft_putendl_error("Incorrect line format:");
	ft_putchar_error('\t');
	ft_putendl_error(line);
	return (-1);
}

int	exit_malloc_fail(void)
{
	ft_putendl_error("Error");
	ft_putendl_error("Error allocating memory");
	return (-1);
}

int	exit_free(void *p)
{
	free(p);
	p = NULL;
	return (-1);
}
