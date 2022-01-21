/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 23:32:00 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/21 10:37:16 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Camera.hpp"

Camera::Camera() {}

Camera::Camera(const CameraArgs& args) :
    _origin(args.origin),
    _direction(args.direction),
    _fov(args.fov),
    _view_width(2 * std::tan(M_PI * args.fov / 360.0f))
{
    this->_direction = this->_direction.normalize();
    // setup basis
    rt::vector<float, 3> tmp_up;
    if (this->_direction[1] == 1.0)
        tmp_up[2] = 1.0;
    else
        tmp_up[1] = 1.0;
    this->_right = rt::cross(this->_direction, tmp_up);
    this->_up = rt::cross(this->_right, this->_direction);
}

Camera::Camera(const Camera& rhs)
{
    this->_direction = rhs._direction;
    this->_origin = rhs._origin;
    this->_fov = rhs._fov;
    this->_view_width = rhs._view_width;
    this->_up = rhs._up;
    this->_right = rhs._right;
} // set copy

Camera& Camera::operator=(const Camera& rhs)
{
    if (this != &rhs)
    {
        this->_direction = rhs._direction;
        this->_origin = rhs._origin;
        this->_fov = rhs._fov;
        this->_view_width = rhs._view_width;
        this->_up = rhs._up;
        this->_right = rhs._right;
    }
    return *this;
}

Camera::~Camera() {}

// Getters
rt::vector<float, 3> Camera::getPosition() const { return _origin; }
rt::vector<float, 3> Camera::getDirection() const { return _direction; }
rt::vector<float, 3> Camera::getUp() const { return _up; }
rt::vector<float, 3> Camera::getRight() const { return _right; }

float Camera::getFov() const { return _fov; }
float Camera::getViewWidth() const { return _view_width; }