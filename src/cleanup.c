/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:47:48 by jceia             #+#    #+#             */
/*   Updated: 2021/10/08 07:54:52 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include "miniRT.h"

void	clean_object(void *obj)
{
	if (!obj)
		return ;
	free(((t_object *)obj)->data);
	free(obj);
}

void	clean_mlx_data(void *ptr)
{
	t_data	*vars;

	if (!ptr)
		return ;
	vars = (t_data *)ptr;
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
	ft_lstclear(&vars->cameras, free);
	ft_lstclear(&vars->lights, free);
	ft_lstclear(&vars->objects, clean_object);
	if (vars->buf)
		free(vars->buf);
	free(vars);
}

void	*clean_exit(void *ptr, char *msg, void (*del)(void *), int do_exit)
{
	perror(msg);
	if (del)
		del(ptr);
	if (do_exit)
		exit(EXIT_FAILURE);
	return (NULL);
}
