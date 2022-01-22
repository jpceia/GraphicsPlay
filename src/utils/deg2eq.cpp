/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deg2eq.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:11:50 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/22 05:19:58 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>
#include "Range.hpp"

bool Range::contains(float x) const
{
    return (x >= min && x <= max);
}

bool Range::intersects(const Range& r) const
{
    return (contains(r.min) || contains(r.max) || r.contains(min) || r.contains(max));
}

bool deg2eq_solve(const Deg2eqParams& args, Range* rng)
{
    if (args.a == 0)
        return false;
    float disc = args.b * args.b - 4 * args.a * args.c;
    if (disc < 0)
        return (false);
    float sqrt_disc = std::sqrt(disc);
    rng->min = (-args.b - sqrt_disc) / (2 * args.a);
    rng->max = (-args.b + sqrt_disc) / (2 * args.a);
    return (true);
}
