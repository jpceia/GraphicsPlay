/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 23:32:00 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/18 23:34:13 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Camera.hpp"

Camera::Camera(const Camera& rhs) {} // set copy

Camera& Camera::operator=(const Camera& rhs) { (void)rhs; return *this; }

Camera::Camera(const CameraArgs& args) :
    _origin(args.origin),
    _direction(args.direction),
    _fov(args.fov)
{
}

Camera::~Camera() {}

void Camera::setup(int win_width, int win_height)
{
    this->pixels_width = win_width;
    this->pixels_height = win_height;
    this->view_width = 2 * std::tan(M_PI * this->_fov / 360);
    this->view_height = win_height * this->view_width / win_width;

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

// Getters
rt::vector<float, 3> Camera::getPosition() const { return _origin; }
rt::vector<float, 3> Camera::getDirection() const { return _direction; }
rt::vector<float, 3> Camera::getUp() const { return _up; }
rt::vector<float, 3> Camera::getRight() const { return _right; }

float Camera::getFov() const { return _fov; }
int Camera::getPixelsWidth() const { return pixels_width; }
int Camera::getPixelsHeight() const { return pixels_height; }
float Camera::getViewWidth() const { return view_width; }
float Camera::getViewHeight() const { return view_height; }