/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 23:32:00 by jpceia            #+#    #+#             */
/*   Updated: 2022/03/11 16:19:14 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Camera.hpp"

Camera::Camera() {}

Camera::Camera(const CameraArgs& args) :
    _ref(args.ref),
    _fov(args.fov),
    _view_width(2 * std::tan(M_PI * args.fov / 360.0f))
{

}

Camera::Camera(const Camera& rhs)
{
    _ref = rhs._ref;
    _fov = rhs._fov;
    _view_width = rhs._view_width;
} // set copy

Camera& Camera::operator=(const Camera& rhs)
{
    if (this != &rhs)
    {
        _ref = rhs._ref;
        _fov = rhs._fov;
        _view_width = rhs._view_width;
    }
    return *this;
}

Camera::~Camera() {}

// ----------------------------------------------------------------------------
//                                  Getters
// ----------------------------------------------------------------------------

vec3f Camera::getPosition() const { return _ref.getPosition(); }
vec3f Camera::getDirection() const { return _ref.getForward(); }
vec3f Camera::getUp() const { return _ref.getUp(); }
vec3f Camera::getRight() const { return _ref.getRight(); }
float Camera::getFov() const { return _fov; }
float Camera::getViewWidth() const { return _view_width; }
