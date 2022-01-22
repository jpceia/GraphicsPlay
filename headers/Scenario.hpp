/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scenario.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 01:33:57 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/22 03:56:16 by jpceia           ###   ########.fr       */
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
    vec3f	color;
    float   ratio; //intensity;
};

struct ScenarioArgs
{
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
    int _antialias;
    int _reflections;
    AmbientLight _ambient_light;
    Camera _camera;
    std::list<Light>    _lights;
    std::list<AHittable*> _hittables;
    vec3f *_buf;

    Scenario(const Scenario& rhs);
    Scenario& operator=(const Scenario& rhs);

    vec3f _hit_light_contribution(const HitRecord &rec, const Light& light) const;
    vec3f _reflection_contribution(const HitRecord& rec, int n_reflections) const;
    vec3f _hit_color(const HitRecord& rec, int n_reflections) const;
    vec3f _raytrace_single(const Ray3f& primary_ray, int n_reflections) const;
    vec3f _raytrace_pixel_contribution(int i, int j) const;
    vec3f _raytrace_pixel(int i, int j) const;
    bool  _raytrace_hit(const Ray3f &ray, const Range& rng, HitRecord& rec) const;
public:
    Scenario();
    Scenario(const ScenarioArgs& args);
    // Destructor
    ~Scenario();

    // Getters
    int getWidth() const;
    int getHeight() const;
    int getViewWidth() const;
    int getViewHeight() const;
    const AmbientLight& getAmbientLight() const;
    vec3f getCameraPosition() const;
    const std::list<AHittable*>& getHittables() const;
    const std::list<Light>& getLights() const;
    // get buffer
    vec3f* getPixels() const;

    // Setters
    void setAmbientLight(const AmbientLight& ambient_light);
    void setCamera(const Camera& camera);
    void addLight(const Light& light);
    void addHittable(AHittable* hittable);
    void setPixel(int i, int j, const vec3f& color);

    void draw(const std::string& fname);
};

#endif
