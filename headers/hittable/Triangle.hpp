/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Triangle.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 23:31:02 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/12 15:27:32 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLE_HPP
# define TRIANGLE_HPP

# include "APlaneSurface.hpp"

struct TriangleArgs
{
    vec3f vertex[3];
    Material material;
};

class Triangle : public APlaneSurface
{
private:
    const vec3f _coedge1;
    const vec3f _coedge2;

    // non-assignable
    Triangle& operator=(const Triangle& rhs) { (void)rhs; return *this; };

    bool _check_boundary(const vec3f& p) const;

public:
    Triangle(const TriangleArgs& args);
    Triangle(const Triangle& rhs);
    virtual ~Triangle() {}
};

#endif
