/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 12:29:55 by jceia             #+#    #+#             */
/*   Updated: 2021/10/08 04:58:28 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>  // O_RDONLY
#include "libft.h"
#include "miniRT.h"
#include <stdio.h>

int	parse_ambient_from_line(t_scenario *scenario, char *line)
{
	int		n;
	int		status;
	char	**s_split;

	n = ft_strwc(line, ' ');
	if (n != 3)
		exit_invalid_line(line);
	s_split = ft_split(line, ' ');
	if (!s_split)
		return (-1);
	scenario->ambient.ratio = ft_atof(s_split[1]);
	status = parse_color(&scenario->ambient.color, s_split[2]);
	ft_str_array_clear(s_split, n);
	if (status < 0)
		return (-1);
	return (0);
}

int	parse_camera_from_line(t_scenario *scenario, char *line)
{
	t_camera	*camera;
	char		**s_split;
	int			status;
	int			n;

	n = ft_strwc(line, ' ');
	if (n != 4)
		return (exit_invalid_line(line));
	camera = (t_camera *)malloc(sizeof(*camera));
	if (!camera)
		return (exit_malloc_fail());
	s_split = ft_split(line, ' ');
	if (!s_split)
		return (-1);
	status = parse_vec3d(&camera->origin, s_split[1]);
	status += parse_vec3d(&camera->direction, s_split[2]);
	camera->fov = ft_atof(s_split[3]);
	ft_str_array_clear(s_split, n);
	if (status < 0)
		return (exit_free(camera));
	ft_lstpush_front(&scenario->cameras, camera);
	return (0);
}

int	parse_light_from_line(t_scenario *scenario, char *line)
{
	t_light	*light;
	char	**s_split;
	int		status;
	int		n;

	n = ft_strwc(line, ' ');
	if (n < 3 || n > 4)
		exit_invalid_line(line);
	light = (t_light *)malloc(sizeof(*light));
	if (!light)
		return (exit_malloc_fail());
	s_split = ft_split(line, ' ');
	if (!s_split)
		return (-1);
	status = parse_vec3d(&light->origin, s_split[1]);
	light->ratio = ft_atof(s_split[2]);
	if (n == 4)
		status += parse_color(&light->color, s_split[3]);
	else
		light->color = vec3d_create(1.0, 1.0, 1.0);
	ft_str_array_clear(s_split, n);
	if (status < 0)
		return (exit_free(light));
	ft_lstpush_front(&scenario->lights, light);
	return (0);
}
