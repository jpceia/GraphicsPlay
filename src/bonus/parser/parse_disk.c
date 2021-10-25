/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_disk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 09:27:20 by jceia             #+#    #+#             */
/*   Updated: 2021/10/25 18:04:13 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_object	*parse_disk_from_line(t_object *obj, char *line)
{
	t_disk	*disk;
	char	**s_split;
	int		n;

	obj->obj_type = DISK;
	n = ft_strwc(line, ' ');
	if (n < 5)
		return (clean_exit(NULL, LINE_FMT_ERR, NULL, 0));
	disk = (t_disk *)malloc(sizeof(*disk));
	if (!disk)
		return (clean_exit(NULL, MALLOC_ERR, NULL, 0));
	s_split = ft_split(line, ' ');
	if (!s_split)
		return (clean_exit(disk, SPLIT_ERR, free, 0));
	if (!parse_vec3d(&disk->center, s_split[1]))
		return (clean_exit(disk, PARSE_VEC_ERR, free, 0));
	if (!parse_vec3d(&disk->n, s_split[2]))
		return (clean_exit(disk, PARSE_VEC_ERR, free, 0));
	disk->radius = ft_atof(s_split[3]);
	if (!parse_color(obj, s_split + 4, n - 4))
		return (clean_exit(disk, PARSE_RGB_ERR, free, 0));
	ft_str_array_clear(s_split, n);
	obj->data = disk;
	return (obj);
}
