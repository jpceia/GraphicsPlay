/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 04:07:35 by jceia             #+#    #+#             */
/*   Updated: 2021/10/25 19:31:33 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"

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
