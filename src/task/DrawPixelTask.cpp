/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DrawPixelTask.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:38:36 by jpceia            #+#    #+#             */
/*   Updated: 2022/03/11 16:39:05 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "task/DrawPixelTask.hpp"
# include "Scenario.hpp"
# include "task/Mutex.hpp"
# include "task/LockGuard.hpp"
# include "task/Task.hpp"

DrawPixelTask::DrawPixelTask(Scenario& scenario, Mutex& mutex, int i, int j) :
        _scenario(scenario), _mutex(mutex), _i(i), _j(j)
{
}

void DrawPixelTask::run()
{
    vec3f color = _scenario.raytrace_pixel(_i, _j);
    {
        LockGuard lock(_mutex);
        _scenario.setPixel(_i, _j, color);
    }
}
