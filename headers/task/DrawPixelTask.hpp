/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DrawPixelTask.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:36:08 by jpceia            #+#    #+#             */
/*   Updated: 2022/03/14 12:51:18 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWPIXELTASK_HPP
# define DRAWPIXELTASK_HPP

# include "Scenario.hpp"
# include "task/Mutex.hpp"
# include "task/Task.hpp"

class DrawPixelTask : public Task
{
public:
    DrawPixelTask(Scenario& scenario, Mutex& mutex,
        int i, int j, int antialias = 1);
    void run();

public:
    Scenario& _scenario;
    Mutex& _mutex;
    int _i;
    int _j;
    int _antialias;
};

#endif
