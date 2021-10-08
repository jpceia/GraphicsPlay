/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:47:48 by jceia             #+#    #+#             */
/*   Updated: 2021/10/08 04:44:56 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "miniRT.h"

void	clean_object(void *obj)
{
	free(((t_object *)obj)->data);
	free(obj);
	obj = NULL;
}

void	clean_mlx_data(t_data *vars)
{
	if (!vars)
		return ;
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
	if (vars->scenario)
		clean_scenario(vars->scenario);
	if (vars->buf)
		free(vars->buf);
	free(vars);
}

void	clean_scenario(t_scenario *scenario)
{
	if (!scenario)
		return ;
	ft_lstclear(&scenario->cameras, free);
	ft_lstclear(&scenario->lights, free);
	ft_lstclear(&scenario->objects, clean_object);
	free(scenario);
}
