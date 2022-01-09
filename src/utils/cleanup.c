/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:47:48 by jceia             #+#    #+#             */
/*   Updated: 2022/01/09 21:15:51 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "miniRT.h"

void	object_clean(void *obj)
{
	if (!obj)
		return ;
	free(((t_object *)obj)->data);
	free(obj);
}

void	data_clean(void *ptr)
{
	t_data	*vars;

	if (!ptr)
		return ;
	vars = (t_data *)ptr;
	camera_clean(vars->camera);
	ft_lstclear(&vars->lights, free);
	ft_lstclear(&vars->objects, object_clean);
	if (vars->buf)
	{
		free(vars->buf);
		vars->buf = NULL;
	}
	if (vars->file_name)
	{
		free(vars->file_name);
		vars->file_name = NULL;
	}
	free(vars);
}

void	*clean_exit(void *ptr, char *msg, void (*del)(void *), int do_exit)
{
	fprintf(stderr, "%s\n", msg);
	if (del)
		del(ptr);
	if (do_exit)
		exit(EXIT_FAILURE);
	return (NULL);
}
