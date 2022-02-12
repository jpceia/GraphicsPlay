/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   APlaneSurface.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 23:30:15 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/12 15:19:19 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APLANESURFACE_HPP
# define APLANESURFACE_HPP

# include "AHittable.hpp"

class APlaneSurface : public AHittable
{
private:
    // non-assignable
    APlaneSurface& operator=(const APlaneSurface& rhs) { (void)rhs; return *this; }

    virtual bool _check_boundary(const vec3f& p) const = 0;

protected:
    const vec3f _base;
    const vec3f _normal;

public:
    APlaneSurface(const APlaneSurface& rhs);
    APlaneSurface(
        const std::string& name,
        const Material& mat,
        const vec3f &base,
        const vec3f &normal);
    
    virtual ~APlaneSurface() {}

    bool hit(const Ray3f& ray, const Range& t_rng, HitRecord& rec) const;
};

#endif
