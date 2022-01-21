/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deg2eq.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:11:50 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/21 16:12:23 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool Range::contains(float x) const
{
    return (x >= min && x <= max);
}

bool deg2eq_solve(const Deg2eqParams& args, Range* rng)
{
    float disc = args.b * args.b - 4 * args.a * args.c;
    if (disc < 0)
        return (false);
    float sqrt_disc = std::sqrt(disc);
    rng->min = (-args.b - sqrt_disc) / (2 * args.a);
    rng->max = (-args.b + sqrt_disc) / (2 * args.a);
    return (true);
}
