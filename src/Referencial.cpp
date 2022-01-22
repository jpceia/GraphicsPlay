/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Referencial.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 04:36:12 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/22 05:04:18 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Referencial.hpp"

Referencial::Referencial()
{
    _forward[2] = 1.0f;
    _up[1] = 1.0f;
    _right[0] = 1.0f;
}

Referencial::Referencial(const ReferencialArgs& args)
{
    _position = args.position;
    _forward = args.forward.normalize();
    if (args.up.dot(_forward) != 0)
        _up = args.up.normalize(); // temporary
    else if (_forward[1] == 1.0)
        _up[2] = 1.0f;
    else
        _up[1] = 1.0f;
    _right = rt::cross(_forward, _up);
    _up = rt::cross(_right, _forward); // ensure orthogonality
}

Referencial& Referencial::operator=(const Referencial& rhs)
{
    if (this != &rhs)
    {
        _position = rhs._position;
        _forward = rhs._forward;
        _up = rhs._up;
        _right = rhs._right;
    }
    return *this;
}

// Getters
vec3f Referencial::getPosition() const { return _position; }
vec3f Referencial::getForward() const { return _forward; }
vec3f Referencial::getUp() const { return _up; }
vec3f Referencial::getRight() const { return _right; }
