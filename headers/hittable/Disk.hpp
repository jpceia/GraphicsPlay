/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Disk.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 23:30:05 by jpceia            #+#    #+#             */
/*   Updated: 2022/02/12 13:11:17 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISK_HPP
# define DISK_HPP

# include "AHittable.hpp"

//struct Range;
//struct Material;

struct DiskArgs
{
    vec3f center;
    vec3f normal;
    float radius;
    Material material;
};

class Disk : public AHittable
{
private:
    const vec3f _center;
    const vec3f _normal;
    const float _radius;
    const float _radius_sq;

    // non-assignable
    Disk& operator=(const Disk& rhs);

public:
    Disk(const DiskArgs& args);
    Disk(const Disk& rhs);

    virtual ~Disk() {}

    bool hit(const Ray3f& ray, const Range& t_rng, HitRecord& rec) const;
};

#endif
