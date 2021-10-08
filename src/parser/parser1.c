/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 04:07:35 by jceia             #+#    #+#             */
/*   Updated: 2021/10/08 04:47:48 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "miniRT.h"

int	parse_scenario_item_from_line(t_scenario *scenario, char *line)
{
	if (ft_strwc(line, ' ') == 0)
		return (0);
	if (ft_strncmp(line, "A ", 2) == 0)
		return (parse_ambient_from_line(scenario, line));
	if (ft_strncmp(line, "C ", 2) == 0)
		return (parse_camera_from_line(scenario, line));
	if (ft_strncmp(line, "L ", 2) == 0)
		return (parse_light_from_line(scenario, line));
	return (parse_object_from_line(scenario, line));
}

t_scenario	*parse_scenario_from_file(t_scenario **scenario, char *fname)
{
	int		fd;
	int		status;
	char	*line;

	check_file_extension(fname, "rt");
	fd = open(fname, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_error("Error");
		ft_putendl_error("Error opening file");
		exit(EXIT_FAILURE);
	}
	*scenario = ft_calloc(1, sizeof(t_scenario));
	status = 0;
	while (ft_get_next_line(fd, &line) > 0 && status >= 0)
	{
		status = parse_scenario_item_from_line(*scenario, line);
		free(line);
	}
	free(line);
	close(fd);
	if (status < 0)
		exit(EXIT_FAILURE);
	return (*scenario);
}

int	parse_color(t_rgb *color, char *s)
{
	int		N;
	char	**s_split;

	N = ft_strwc(s, ',');
	if (N != 3)
	{
		ft_putendl_error("Error");
		ft_putendl_error("Incorrect color format");
		return (-1);
	}
	s_split = ft_split(s, ',');
	color->x = (float)ft_atoi(s_split[0]) / 255;
	color->y = (float)ft_atoi(s_split[1]) / 255;
	color->z = (float)ft_atoi(s_split[2]) / 255;
	ft_str_array_clear(s_split, N);
	return (0);
}

int	parse_vec3d(t_vec3d *p, char *s)
{
	int		N;
	char	**s_split;

	N = ft_strwc(s, ',');
	if (N != 3)
	{
		ft_putendl_error("Error");
		ft_putendl_error("Incorrect coordinates format");
		return (-1);
	}
	s_split = ft_split(s, ',');
	p->x = ft_atof(s_split[0]);
	p->y = ft_atof(s_split[1]);
	p->z = ft_atof(s_split[2]);
	ft_str_array_clear(s_split, N);
	return (0);
}
