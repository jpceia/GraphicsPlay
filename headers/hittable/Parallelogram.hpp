/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parallelogram.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 23:31:02 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/12 15:45:12 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARALLELOGRAM_HPP
# define PARALLELOGRAM_HPP

# include "APlaneSurface.hpp"

struct ParallelogramArgs
{
    vec3f vertex[3];
    Material material;
};

class Parallelogram : public APlaneSurface
{
private:
    const vec3f _coedge1;
    const vec3f _coedge2;

    // non-assignable
    Parallelogram& operator=(const Parallelogram& rhs) { (void)rhs; return *this; };

    bool _check_boundary(const vec3f& p) const;

public:
    Parallelogram(const ParallelogramArgs& args);
    Parallelogram(const Parallelogram& rhs);
    virtual ~Parallelogram() {}
};

#endif
