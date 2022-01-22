/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Disk.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 23:30:05 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/22 03:16:12 by jpceia           ###   ########.fr       */
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
    vec3f _center;
    vec3f _normal;
    float _radius;

    // non copyable
    Disk(const Disk& rhs);
    Disk& operator=(const Disk& rhs);

public:
    Disk(const DiskArgs& args);

    virtual ~Disk() {}

    bool hit(const Ray3f& r, const Range& t_rng, HitRecord& rec) const;
};

#endif
