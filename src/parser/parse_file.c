/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 19:29:47 by jceia             #+#    #+#             */
/*   Updated: 2022/01/09 21:15:13 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "libft.h"
#include "miniRT.h"

int	check_file_extension(char *fname, const char *ext)
{
	char	**s_split;
	int		n;

	n = ft_strwc(fname, '.');
	if (n < 1)
	{
		perror("File has no extension");
		return (-1);
	}
	s_split = ft_split(fname, '.');
	if (ft_strcmp(s_split[n - 1], ext) != 0)
	{
		ft_str_array_clear(s_split, n);
		perror("Unexpected file extension");
		return (-1);
	}
	ft_str_array_clear(s_split, n);
	return (0);
}

t_data	*parse_data_from_fd(t_data *vars, int fd)
{
	int		status;
	char	*line;
	char	*err_msg;

	status = 1;
	err_msg = NULL;
	while ((status > 0) && !err_msg)
	{
		status = ft_get_next_line(fd, &line);
		if (status == -1)
			err_msg = "Error reading the file";
		if (status == 1)
			if (!parse_data_item_from_line(vars, line))
				err_msg = "Error parsing line";
		free(line);
	}
	if (err_msg)
	{
		fprintf(stderr, "%s\n", err_msg);
		return (NULL);
	}
	return (vars);
}

t_data	*parse_data_from_file(t_data *vars, char *fname)
{
	int		fd;

	if (check_file_extension(fname, "rt") < 0)
		return (NULL);
	fd = open(fname, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (NULL);
	}
	if (!parse_data_from_fd(vars, fd))
		return (NULL);
	if (close(fd) < 0)
	{
		perror("Error closing file");
		return (NULL);
	}
	return (vars);
}
