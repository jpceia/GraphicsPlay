/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_disk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 09:27:20 by jceia             #+#    #+#             */
/*   Updated: 2022/01/09 17:10:43 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_object	*parse_disk_from_line_aux(t_object *obj, char **s_split)
{
	t_disk	*disk;

	disk = (t_disk *)malloc(sizeof(*disk));
	if (!disk)
		return (clean_exit(NULL, MALLOC_ERR, NULL, 0));
	if (!parse_vec3d(&disk->center, s_split[1]))
		return (clean_exit(disk, PARSE_VEC_ERR, free, 0));
	if (!parse_vec3d(&disk->n, s_split[2]))
		return (clean_exit(disk, PARSE_VEC_ERR, free, 0));
	disk->radius = ft_atof(s_split[3]);
	obj->data = disk;
	return (obj);
}

t_object	*parse_disk_from_line(t_object *obj, char *line)
{
	t_object	*res;
	char		**s_split;
	int			n;

	obj->obj_type = DISK;
	n = ft_strwc(line, ' ');
	if (n < 5)
		return (clean_exit(NULL, LINE_FMT_ERR, NULL, 0));
	s_split = ft_split(line, ' ');
	if (!s_split)
		return (clean_exit(NULL, SPLIT_ERR, NULL, 0));
	res = parse_disk_from_line_aux(obj, s_split);
	if (res)
		res = parse_color(obj, s_split + 4, n - 4);
	ft_str_array_clear(s_split, n);
	if (!res)
		return (NULL);
	return (obj);
}
