/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ray.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 23:37:14 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/21 16:34:20 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_HPP
# define RAY_HPP

# include <iostream>

namespace rt
{

template <typename T, std::size_t N>
class Ray
{
private:
    vector<T, N> _origin;
    vector<T, N> _direction;

    Ray() {}
public:
    
    Ray(vector<T, N> origin, vector<T, N> direction) : _origin(origin), _direction(direction.normalize()) {}
    Ray(const Ray& rhs) : _origin(rhs._origin), _direction(rhs._direction) {}
    virtual ~Ray() {}

    Ray& operator=(const Ray& rhs)
    {
        _origin = rhs._origin;
        _direction = rhs._direction;
        return *this;
    }

    vector<T, N> getOrigin() const { return _origin; }
    vector<T, N> getDirection() const { return _direction; }

    vector<T, N> getPointAt(float t) const { return _origin + _direction * t; }

    vector<T, N> reflected(vector<T, N> normal) const
    {
        return _direction - (normal * 2 * rt::dot(_direction, normal));
    }
};

} // namespace rt

typedef rt::Ray<float, 3> Ray3f;

#endif
