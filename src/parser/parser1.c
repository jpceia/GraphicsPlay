/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 04:07:35 by jceia             #+#    #+#             */
/*   Updated: 2021/10/08 07:55:53 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "libft.h"
#include "miniRT.h"

// OK
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

// OK
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

t_data	*parse_data_from_file(t_data **vars, char *fname)
{
	int		fd;
	int		status;
	char	*line;
	char	*err_msg;

	if (check_file_extension(fname, "rt") < 0)
		return (NULL);
	fd = open(fname, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (NULL);
	}
	*vars = ft_calloc(1, sizeof(t_data));
	if (!*vars)
	{
		perror("Error allocating memory");
		return (NULL);
	}
	status = 1;
	err_msg = NULL;
	while ((status > 0) && !err_msg)
	{
		status = ft_get_next_line(fd, &line);
		if (status == -1)
			err_msg = "Error reading the file";
		if (status == 1)
		{
			if (!parse_data_item_from_line(*vars, line))
				err_msg = "Error parsing line"; 
		}
		free(line);
	}
	close(fd);
	if (err_msg)
	{
		perror(err_msg);
		return (NULL);
	}
	return (*vars);
}

t_rgb	*parse_color(t_rgb *color, char *s)
{
	int		n;
	char	**s_split;

	n = ft_strwc(s, ',');
	if (n != 3)
	{
		perror("Incorrect color format");
		return (NULL);
	}
	s_split = ft_split(s, ',');
	color->x = (float)ft_atoi(s_split[0]) / 255;
	color->y = (float)ft_atoi(s_split[1]) / 255;
	color->z = (float)ft_atoi(s_split[2]) / 255;
	ft_str_array_clear(s_split, n);
	return (color);
}

t_vec3d	*parse_vec3d(t_vec3d *p, char *s)
{
	int		n;
	char	**s_split;

	n = ft_strwc(s, ',');
	if (n != 3)
	{
		perror("Incorrect coordinates format");
		return (NULL);
	}
	s_split = ft_split(s, ',');
	p->x = ft_atof(s_split[0]);
	p->y = ft_atof(s_split[1]);
	p->z = ft_atof(s_split[2]);
	ft_str_array_clear(s_split, n);
	return (p);
}
