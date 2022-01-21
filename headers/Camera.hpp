/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Camera.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 01:32:16 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/21 10:37:03 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_HPP
# define CAMERA_HPP

#include "Vector.hpp"

struct CameraArgs
{
	rt::vector<float, 3> 	origin;
	rt::vector<float, 3> 	direction;
	float					fov;
};

class Camera
{
private:
	rt::vector<float, 3> 	_origin;
	rt::vector<float, 3> 	_direction;
    rt::vector<float, 3> 	_up;
    rt::vector<float, 3> 	_right;
	float					_fov;
    float					_view_width;


public:
    Camera();
    Camera(const CameraArgs& args);
    Camera(const Camera& rhs);
    Camera& operator=(const Camera& rhs);
    virtual ~Camera();

    void setup(int win_width, int win_height);

    // Getters
    rt::vector<float, 3> getPosition() const;
    rt::vector<float, 3> getDirection() const;
    rt::vector<float, 3> getUp() const;
    rt::vector<float, 3> getRight() const;
    float getFov() const;
    float getViewWidth() const;
};

#endif
