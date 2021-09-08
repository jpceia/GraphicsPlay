/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endswith.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 17:46:07 by jceia             #+#    #+#             */
/*   Updated: 2021/09/01 18:23:55 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_endswith(char *s, char *suff)
{
	int	index;
	int	suff_len;
	int	s_len;

	s_len = ft_strlen(s);
	suff_len = ft_strlen(suff);
	if (s_len < suff_len)
		return (0);
	index = s_len - suff_len;
	while (s[index] && s[index] == suff[index])
		index++;
	return (suff[index] == 0);
}
