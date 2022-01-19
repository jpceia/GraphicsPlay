/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scenario.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 01:09:27 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/19 03:45:39 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Scenario.hpp"
#include "miniRT.h"

float	convert_scale(float x, float view_size, float screen_size)
{
	return (view_size * (x / screen_size - 0.5));
}


Scenario::Scenario(const Scenario& rhs) { (void)rhs; } // set copy
Scenario& Scenario::operator=(const Scenario& rhs) { (void)rhs; return *this; }

Scenario::Scenario() {}
Scenario::Scenario(const ScenarioArgs& args) :
    _width(args.width),
    _height(args.height),
    _antialias(args.n_antialias),
    _reflections(args.n_antialias),
    
    _camera(NULL),
    _buf(new rt::vector<float, 3>[args.width * args.height])
{
}
// Destructor
Scenario::~Scenario()
{
    for (std::list<AHittable*>::iterator it = _hittables.begin(); it != _hittables.end(); ++it)
        delete *it;
    delete _camera;
    delete[] _buf;
}

// Getters
int Scenario::getWidth() const { return _width; }
int Scenario::getHeight() const { return _height; }
int Scenario::getViewWidth() const { return _camera->getViewWidth(); }
int Scenario::getViewHeight() const { return _camera->getViewHeight(); }
int Scenario::getScreenWidth() const { return _camera->getPixelsWidth(); }
int Scenario::getScreenHeight() const { return _camera->getPixelsHeight(); }
const AmbientLight& Scenario::getAmbientLight() const { return _ambient_light; }
rt::vector<float, 3> Scenario::getCameraPosition() const { return _camera->getPosition(); }
const std::list<AHittable*>& Scenario::getHittables() const { return _hittables; }
const std::list<Light>& Scenario::getLights() const { return _lights; }
// get buffer
rt::vector<float, 3>* Scenario::getPixels() const { return _buf; }
const Camera* Scenario::getCamera() const { return _camera; }

// Setters
void Scenario::setAmbientLight(const AmbientLight& ambient_light) { _ambient_light = ambient_light; }
void Scenario::addLight(const Light& light) { _lights.push_back(light); }
void Scenario::addHittable(AHittable* hittable) { _hittables.push_back(hittable); }
void Scenario::setCamera(Camera* camera) {
    if (_camera)
        throw std::runtime_error("Camera already set");
    _camera = camera;
}
void Scenario::setupCamera()
{
    if (!_camera)
        throw std::runtime_error("Camera not set");
    _camera->setup(this->getWidth(), this->getHeight());
}
void Scenario::setPixel(int i, int j, const rt::vector<float, 3>& color) { _buf[i * _width + j] = color; }

void Scenario::draw(const std::string& fname)
{
    this->setupCamera();
    for (int i = 0; i < this->getScreenHeight(); ++i)
        for (int j = 0; j < this->getScreenWidth(); ++j)
            this->setPixel(i, j, _raytrace_pixel(i, j));
    create_bmp(fname, _camera->getPixelsWidth(),  _camera->getPixelsHeight(), _buf);
}


t_rgb	Scenario::_raytrace_pixel_contribution(int i, int j) const
{
	float x = convert_scale(i, this->getViewWidth(), this->getScreenWidth());
	float y = convert_scale(j, this->getViewHeight(), this->getScreenHeight());
	rt::vector<float, 3> v; // multiply cam basis by (arr[0], arr[1], 1)
	v[0] = _camera->getRight()[0] * x + _camera->getUp()[0] * y + _camera->getDirection()[0];
	v[1] = _camera->getRight()[1] * x + _camera->getUp()[1] * y + _camera->getDirection()[1];
	v[2] = _camera->getRight()[2] * x + _camera->getUp()[2] * y + _camera->getDirection()[2];
	rt::Ray<float, 3> ray(_camera->getPosition(), v);
	return (_raytrace_single(ray, _reflections)); // last arg is reflection depth
}

t_rgb	Scenario::_raytrace_pixel(int i, int j) const
{
	t_rgb	color;
    int a, b;

	for (int k = 0; k < _antialias; ++k)
	{
		a = (float)j + ((0.5 + k) / _antialias);
		for (int l = 0; l < _antialias; ++l)
		{
			b = (float)i + ((0.5 + l) / _antialias);
			color += _raytrace_pixel_contribution(a, b);
		}
	}
	color /= (_antialias * _antialias);
	return (color);
}


t_rgb	Scenario::_hit_light_contribution(const HitRecord &rec, const Light& light) const
{
	HitRecord	hit_before_light;
    const Material&   mat = rec.hittable->getMaterial();

	rt::Ray<float, 3>	ray_to_light = rt::Ray<float, 3>(rec.p, light.getOrigin() - rec.p);
	float dist = ray_to_light.getDirection().length();
	if (_raytrace_hit(ray_to_light, 1e-3, hit_before_light))
		if (hit_before_light.t < dist)
			return (t_rgb());
    // Diffuse intensity
    float diffuse_intensity = rt::dot(ray_to_light.getDirection(), rec.normal) * mat.diffusion;
    diffuse_intensity = std::max(diffuse_intensity, 0.0f);
    // Specular intensity
    float specular_intensity = rt::dot(ray_to_light.getDirection(), rec.reflected);
	if (specular_intensity < 0)
        specular_intensity = 0;
    else
        specular_intensity = std::pow(specular_intensity, mat.shininess) * mat.specular;
    float light_intensity = light.getRatio() * (diffuse_intensity + specular_intensity);
	return (light.getColor() * light_intensity);
}

t_rgb   Scenario::_reflection_contribution(const HitRecord& rec, int n_reflections) const
{
	rt::Ray<float, 3>	ray(rec.p, rec.reflected);
    const Material&   mat = rec.hittable->getMaterial();
	t_rgb	color_shadow = _raytrace_single(ray, n_reflections - 1);
	return (color_shadow * mat.mirror);
}

t_rgb	Scenario::_hit_color(const HitRecord& rec, int n_reflections) const
{
	const Material& mat = rec.hittable->getMaterial();

	rt::vector<float, 3> color_shadow = _ambient_light.color * mat.ambient * _ambient_light.ratio;
	for (std::list<Light>::const_iterator it = _lights.begin(); it != _lights.end(); ++it)
		color_shadow += _hit_light_contribution(rec, *it);
	color_shadow = rt::elementwise_product(rec.color, color_shadow);
	if (n_reflections > 0)
		color_shadow += _reflection_contribution(rec, n_reflections);
	return (color_shadow);
}

bool	Scenario::_raytrace_hit(const rt::Ray<float, 3> &ray, float t_min, HitRecord& rec) const
{
	bool		hit_anything = false;
	HitRecord	hit_rec;

	for (std::list<AHittable *>::const_iterator it = _hittables.begin(); it != _hittables.end(); ++it)
	{
		AHittable *hittable = *it;
		if (hittable->hit(ray, t_min, 100000.0f, hit_rec))
		{
			hit_anything = true;
			hit_rec.hittable = hittable; // check this
			if (hit_rec.t < rec.t)
				rec = hit_rec;
		}
	}
	if (hit_anything)
	{
		//rec.normal = (vec3d_random() * rec.hittable->getMaterial().wrinkle).normalize();
		if (rt::dot(ray.getDirection(), rec.normal) > 0)
			rec.normal *= -1; // -v is invalid ??
		rec.reflected = ray.reflected(rec.normal);
	}
	return (hit_anything);
}

t_rgb	Scenario::_raytrace_single(const rt::Ray<float, 3>& primary_ray, int n_reflections) const
{
	HitRecord	rec;
	
	if (_raytrace_hit(primary_ray, 1e-2, rec))
		return (_hit_color(rec, n_reflections));
	return (_ambient_light.color);
}
