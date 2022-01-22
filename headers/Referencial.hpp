/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Referencial.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 04:19:54 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/22 04:50:55 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REFERENCIAL_HPP
# define REFERENCIAL_HPP

#include "Vector.hpp"

struct ReferencialArgs
{
	vec3f position;
    vec3f forward;
    vec3f up;
    // vec3f right; the right vector is calculated from the forward and up vectors
};

class Referencial
{
private:
	vec3f 	_position;
	vec3f 	_forward;
    vec3f 	_up;
    vec3f 	_right;

public:
    Referencial();
    Referencial(const ReferencialArgs& args);
    Referencial& operator=(const Referencial& rhs);
    virtual ~Referencial() {}

    // Getters
    vec3f getPosition() const;
    vec3f getForward() const;
    vec3f getUp() const;
    vec3f getRight() const;
};

#endif
