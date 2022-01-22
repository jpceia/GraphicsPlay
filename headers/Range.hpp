/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Range.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 03:12:41 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/22 03:12:56 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANGE_HPP
# define RANGE_HPP

struct Deg2eqParams
{
    float a;
    float b;
    float c;
};

struct Range
{
    float min;
    float max;

    Range() : min(0), max(0) {}
    Range(float a, float b) : min(a), max(b) {}

    bool contains(float x) const;

    bool intersects(const Range& r) const;
};

bool deg2eq_solve(const Deg2eqParams& args, Range* rng);

#endif
