/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:47:48 by jceia             #+#    #+#             */
/*   Updated: 2021/09/08 15:24:08 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	clear_object(void *obj)
{
	free(((t_object *)obj)->data);
	free(obj);
	obj = NULL;
}

void    clear_scenario(t_scenario *scenario)
{
    ft_lstclear(&scenario->cameras, free);
    ft_lstclear(&scenario->lights, free);
    ft_lstclear(&scenario->objects, clear_object);
}