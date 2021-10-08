/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 04:07:35 by jceia             #+#    #+#             */
/*   Updated: 2021/10/08 08:56:28 by jceia            ###   ########.fr       */
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

t_data	*parse_data_item_from_line(t_data *vars, char *line)
{
	if (ft_strwc(line, ' ') == 0)
		return (vars);
	if (ft_strncmp(line, "A ", 2) == 0)
		return (parse_ambient_from_line(vars, line));
	if (ft_strncmp(line, "C ", 2) == 0)
		return (parse_camera_from_line(vars, line));
	if (ft_strncmp(line, "L ", 2) == 0)
		return (parse_light_from_line(vars, line));
	return (parse_object_from_line(vars, line));
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
		return (clean_exit(vars, err_msg, mlx_data_clean, 0));
	return (vars);
}

t_data	*parse_data_from_file(t_data *vars, char *fname)
{
	int		fd;

	if (check_file_extension(fname, "rt") < 0)
		return (NULL);
	fd = open(fname, O_RDONLY);
	if (fd < 0)
		return (clean_exit(NULL, "Error opening file", NULL, 0));
	if (!parse_data_from_fd(vars, fd))
		return (clean_exit(vars, "Error parsing file", mlx_data_clean, 0));
	if (close(fd) < 0)
		perror("Error closing file");
	return (vars);
}
