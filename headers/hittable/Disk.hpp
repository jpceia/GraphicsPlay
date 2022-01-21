/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Disk.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 23:30:05 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/21 15:17:24 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISK_HPP
# define DISK_HPP

#include "AHittable.hpp"

struct DiskArgs
{
    rt::vector<float, 3> p;
    rt::vector<float, 3> direction;
    float radius;
    Material material;
};

class Disk : public AHittable
{
private:
    rt::vector<float, 3> center;
    rt::vector<float, 3> n;
    float radius;

    // non copyable
    Disk(const Disk& rhs);
    Disk& operator=(const Disk& rhs);

public:
    Disk(const DiskArgs& args);

    virtual ~Disk() {}

    bool hit(const rt::Ray<float, 3>& r, float t_min, float t_max, HitRecord& rec) const;
};

#endif
