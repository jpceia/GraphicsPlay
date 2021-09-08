/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 12:29:55 by jceia             #+#    #+#             */
/*   Updated: 2021/09/08 15:30:43 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>  // O_RDONLY
#include "libft.h"
#include "color.h"
#include "miniRT.h"
#include <stdio.h>

int	parse_ambient_from_line(t_scenario *scenario, char *line)
{
	int		N;
	int		status;
	char	**s_split;

	N = ft_strwc(line, ' ');
	if (N != 3)
		exit_invalid_line(line);
	s_split = ft_split(line, ' ');
	if (!s_split)
		return (-1);
	scenario->ambient.ratio = ft_atoi(s_split[1]);
	status = parse_color(&scenario->ambient.color, s_split[2]);
	ft_str_array_clear(s_split, N);
	if (status < 0)
		return (-1);
	return (0);
}


int	parse_camera_from_line(t_scenario *scenario, char *line)
{
	t_camera	*camera;
	char		**s_split;
	int			status;
	int			N;

	N = ft_strwc(line, ' ');
    if (N != 4)
		return (exit_invalid_line(line));
	camera = (t_camera *)malloc(sizeof(*camera));
	if (!camera)
		return (exit_malloc_fail());
    s_split = ft_split(line, ' ');
	if (!s_split)
		return (-1);
	status = parse_point3D(&camera->orig, s_split[1]);
	status += parse_point3D(&camera->direction, s_split[2]);
	camera->fov = ft_atoi(s_split[3]);
	ft_str_array_clear(s_split, N);
	if (status < 0)
		return (exit_free(camera));
	ft_lstadd_front(&scenario->cameras, ft_lstnew(camera));
	return (0);
}


int	parse_light_from_line(t_scenario *scenario, char *line)
{
	t_light	*light;
	char	**s_split;
	int		status;
	int		N;

	N = ft_strwc(line, ' ');
    if (N < 3 || N > 4)
		exit_invalid_line(line);
	light = (t_light *)malloc(sizeof(*light));
	if (!light)
		return (exit_malloc_fail());
    s_split = ft_split(line, ' ');
	if (!s_split)
		return (-1);
	status = parse_point3D(&light->orig, s_split[1]);
	light->ratio = ft_atoi(s_split[2]);
	if (N == 4)
		status += parse_color(&light->color, s_split[3]);
	else
		light->color = color_create(1, 1, 1, 1);
    ft_str_array_clear(s_split, N);
    if (status < 0)
		return (exit_free(light));
	ft_lstadd_front(&scenario->lights, ft_lstnew(light));
	return (0);
}