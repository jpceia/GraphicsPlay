/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 01:32:16 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/22 04:25:37 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_HPP
# define CAMERA_HPP

#include "Vector.hpp"

struct CameraArgs
{
	vec3f 	origin;
	vec3f 	direction;
	float					fov;
};

class Camera
{
private:
	vec3f 	_origin;
	vec3f 	_direction;
    vec3f 	_up;
    vec3f 	_right;
	float					_fov;
    float					_view_width;


public:
    Camera();
    Camera(const CameraArgs& args);
    Camera(const Camera& rhs);
    Camera& operator=(const Camera& rhs);
    virtual ~Camera();

    // Getters
    vec3f getPosition() const;
    vec3f getDirection() const;
    vec3f getUp() const;
    vec3f getRight() const;
    float getFov() const;
    float getViewWidth() const;
};

#endif
