/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scenario.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 01:33:57 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/19 00:03:21 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENARIO_HPP
# define SCENARIO_HPP

# include <iostream>
# include <list>
# include "hittable/AHittable.hpp"
# include "Light.hpp"
# include "Camera.hpp"

struct AmbientLight
{
    rt::vector<float, 3>	color;
    float   ratio; //intensity;
};

struct ScenarioArgs
{
    std::string scene_fname;
    std::string output_fname;
    std::string title;
	int		width;
	int		height;
	int		n_reflections;
	int		n_antialias;
};

class Scenario
{
private:
    int _width;
    int _height;
    std::string _fname;
    AmbientLight _ambient_light;
    Camera *_camera;
    std::list<Light>    _lights;
    std::list<AHittable*> _hittables;
    rt::vector<float, 3> *_buf;

    int n_reflections;
    int n_antialias;


    Scenario(const Scenario& rhs) {} // set copy

    Scenario& operator=(const Scenario& rhs) { (void)rhs; return *this; }


public:
    Scenario() {}
    Scenario(const ScenarioArgs& args) :
        _width(args.width),
        _height(args.height),
        _fname(args.output_fname),
        _camera(NULL),
        _buf(new rt::vector<float, 3>[args.width * args.height])
    {
    }
    // Destructor
    ~Scenario()
    {
        for (std::list<AHittable*>::iterator it = _hittables.begin(); it != _hittables.end(); ++it)
            delete *it;
        delete _camera;
        delete[] _buf;
    }

    // Getters
    int getWidth() const { return _width; }
    int getHeight() const { return _height; }
    int getViewWidth() const { return _camera->getViewWidth(); }
    int getViewHeight() const { return _camera->getViewHeight(); }
    int getScreenWidth() const { return _camera->getPixelsWidth(); }
    int getScreenHeight() const { return _camera->getPixelsHeight(); }
    const AmbientLight& getAmbientLight() const { return _ambient_light; }
    rt::vector<float, 3> getCameraPosition() const { return _camera->getPosition(); }
    const std::list<AHittable*>& getHittables() const { return _hittables; }
    const std::list<Light>& getLights() const { return _lights; }
    // get buffer
    rt::vector<float, 3>* getPixels() const { return _buf; }
    std::string getFileName() const { return _fname; }
    const Camera* getCamera() const { return _camera; }

    // Setters
    void setAmbientLight(const AmbientLight& ambient_light) { _ambient_light = ambient_light; }
    void addLight(const Light& light) { _lights.push_back(light); }
    void addHittable(AHittable* hittable) { _hittables.push_back(hittable); }
    void setCamera(Camera* camera) {
        if (_camera)
            throw std::runtime_error("Camera already set");
        _camera = camera;
    }
    void setupCamera()
    {
        if (!_camera)
            throw std::runtime_error("Camera not set");
        _camera->setup(this->getWidth(), this->getHeight());
    }
    void setPixel(int i, int j, const rt::vector<float, 3>& color) { _buf[i * _width + j] = color; }
};

#endif
