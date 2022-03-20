/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scenario.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 01:09:27 by jpceia            #+#    #+#             */
/*   Updated: 2022/03/20 12:18:36 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Scenario.hpp"
#include "miniRT.hpp"
#include "gradient.hpp"
#include "task/WorkManager.hpp"
#include "task/DrawPixelTask.hpp"
#include <vector>

float convert_scale(float x, float view_size, float screen_size)
{
    return (view_size * (x / screen_size - 0.5));
}


Scenario::Scenario(const Scenario& rhs)
{
    (void)rhs;
} // set copy

Scenario& Scenario::operator=(const Scenario& rhs)
{
    (void)rhs;
    return *this;
}

Scenario::Scenario()
{
}

Scenario::Scenario(const ScenarioArgs& args) :
    _width(args.width),
    _height(args.height),
    _antialias(args.n_antialias),
    _reflections(args.n_antialias),
    _buf(new vec3f[args.width * args.height]),
    _rng(Range(1e-3, 1e10))
{
}

// Destructor
Scenario::~Scenario()
{
    for (std::list<AHittable*>::iterator it = _hittables.begin();
        it != _hittables.end(); ++it)
        delete *it;
    delete[] _buf;
}

// ----------------------------------------------------------------------------
//                                  Getters
// ----------------------------------------------------------------------------

int Scenario::getWidth() const
{
    return _width;
}

int Scenario::getHeight() const
{
    return _height;
}

int Scenario::getViewWidth() const
{
    return _camera.getViewWidth();
}

int Scenario::getViewHeight() const
{
    return _height * _camera.getViewWidth() / _height;
}

const AmbientLight& Scenario::getAmbientLight() const
{
    return _ambient_light;
}

vec3f Scenario::getCameraPosition() const
{
    return _camera.getPosition();
}

const std::list<AHittable*>& Scenario::getHittables() const
{
    return _hittables;
}

const std::list<Light>& Scenario::getLights() const
{
    return _lights;
}

// get buffer
vec3f* Scenario::getPixels() const
{
    return _buf;
}

// ----------------------------------------------------------------------------
//                                  Setters
// ----------------------------------------------------------------------------
void Scenario::setAmbientLight(const AmbientLight& ambient_light)
{
    _ambient_light = ambient_light;
}

void Scenario::setCamera(const Camera& camera) { _camera = camera; }

void Scenario::addLight(const Light& light)
{
    _lights.push_back(light);
}

void Scenario::addHittable(AHittable* hittable)
{
    if (hittable)
        _hittables.push_back(hittable);
}

void Scenario::setPixel(int i, int j, const vec3f& color)
{
    _buf[i * _width + j] = color;
}

inline const vec3f& Scenario::getPixel(int i, int j) const
{
    return _buf[i * _width + j];
}

void Scenario::draw(const std::string& fname)
{
    Mutex mutex;
    WorkManager manager(NUM_THREADS);

    int N = 2 * 2;
    float epsilon = 1e-4;

    // Draw thumbnail ( skipping N pixels for each step )
    for (int i = 0; i < _height; i += N)
        for (int j = 0; j < _width; j += N)
            manager.push_task(new DrawPixelTask(*this, mutex, i, j, 1));
    manager.push_task(NULL);
    manager.init();
    manager.wait();
    manager.reset();

    // Draw full image
    for (int i = 0; i < _height; ++i)
    {
        for (int j = 0; j < _width; ++j)
        {
            if (i % N == 0)
            {
                if (j % N == 0)
                    continue ;
                // else
                int j0 = (j / N) * N;
                int j1 = j0 + N;
                vec3f c0 = this->getPixel(i, j0);
                vec3f c1 = this->getPixel(i, j1);
                if ((c0 - c1).lengthSquared() > epsilon) // recalculate
                    manager.push_task(new DrawPixelTask(*this, mutex, i, j, 1));
                else // interpolate
                    this->setPixel(i, j, (c0 * (j1 - j) + c1 * (j - j0)) / (float)N);
            }
            else if (j % N == 0)
            {
                int i0 = (i / N) * N;
                int i1 = i0 + N;
                vec3f c0 = this->getPixel(i0, j);
                vec3f c1 = this->getPixel(i1, j);
                if ((c0 - c1).lengthSquared() > epsilon) // recalculate
                    manager.push_task(new DrawPixelTask(*this, mutex, i, j, 1));
                else // interpolate
                    this->setPixel(i, j, (c0 * (i1 - i) + c1 * (i - i0)) / (float)N);
            }
            else
            {
                int i0 = (i / N) * N;
                int i1 = i0 + N;
                int j0 = (j / N) * N;
                int j1 = j0 + N;
                vec3f c0 = this->getPixel(i0, j0);
                vec3f c1 = this->getPixel(i0, j1);
                vec3f c2 = this->getPixel(i1, j0);
                vec3f c3 = this->getPixel(i1, j1);
                if ((c0 - c1).lengthSquared() + (c2 - c3).lengthSquared() > epsilon) // recalculate
                    manager.push_task(new DrawPixelTask(*this, mutex, i, j, 1));
                else // interpolate
                {
                    vec3f color;
                    color += c0 * (i1 - i) * (j1 - j);
                    color += c1 * (i1 - i) * (j - j0);
                    color += c2 * (i - i0) * (j1 - j);
                    color += c3 * (i - i0) * (j - j0);
                    this->setPixel(i, j, color / (float)(N * N));
                }
            }
        }
    }

    manager.push_task(NULL);
    manager.init();
    manager.wait();
    manager.reset();

    // Compute image absolute gradient
    std::vector<vec3f> grad_x(_width * _height);
    gradient_x(_buf, _width, _height, &grad_x[0]);
    std::vector<vec3f> grad_y(_width * _height);
    gradient_y(_buf, _width, _height, &grad_y[0]);
    std::vector<float> grad(_width * _height);
    for (int i = 0; i < _width * _height; ++i)
        grad[i] = grad_x[i].lengthSquared() + grad_y[i].lengthSquared();
    manager.reset();
    
    // Draw anti-aliased image
    for (int i = 0; i < _height; ++i)
        for (int j = 0; j < _width; ++j)
            if (grad[i * _width + j] > epsilon)
                manager.push_task(new DrawPixelTask(*this, mutex, i, j));
    manager.push_task(NULL);
    manager.init();
    manager.wait();
    create_bmp(fname, _width,  _height, _buf);
}

vec3f    Scenario::_raytrace_pixel_contribution(float a, float b) const
{
    float view_width = _camera.getViewWidth();
    float view_height = _height * view_width / _width;
    float x = convert_scale(a, view_width, _width);
    float y = convert_scale(b, view_height, _height);
    vec3f e_x = _camera.getRight();
    vec3f e_y = _camera.getUp();
    vec3f e_z = _camera.getDirection();
    vec3f v;
    v[0] = e_x[0] * x + e_y[0] * y + e_z[0];
    v[1] = e_x[1] * x + e_y[1] * y + e_z[1];
    v[2] = e_x[2] * x + e_y[2] * y + e_z[2];
    Ray3f ray(_camera.getPosition(), v);
    return (_raytrace_single(ray, _reflections)); // last arg is reflection depth
}

vec3f    Scenario::raytrace_pixel(int i, int j, int antialias) const
{
    vec3f    color;
    float a, b;

    antialias = antialias ? antialias : _antialias;
    for (int k = 0; k < antialias; ++k)
    {
        a = (float)j + ((0.5 + k) / antialias);
        for (int l = 0; l < antialias; ++l)
        {
            b = (float)i + ((0.5 + l) / antialias);
            color += _raytrace_pixel_contribution(a, b);
        }
    }
    color /= (antialias * antialias);
    return color;
}


vec3f    Scenario::_hit_light_contribution(const HitRecord &rec, const Light& light) const
{
    const Material& mat = rec.hittable->getMaterial();
    Ray3f ray_to_light = Ray3f(rec.p, light.getPosition() - rec.p);
    float dist = (light.getPosition() - rec.p).length();
    HitRecord hit_before_light;
    if (_raytrace_hit(ray_to_light, _rng, hit_before_light))
        if (hit_before_light.t < dist)
            return (vec3f());
    // Diffuse intensity
    float diffuse_intensity = rt::dot(ray_to_light.getDirection(), rec.normal) * mat.diffusion;
    diffuse_intensity = std::max(diffuse_intensity, 0.0f);
    // Specular intensity
    float specular_intensity = 0;
    if (mat.specular > 0)
    {
        specular_intensity = rt::dot(ray_to_light.getDirection(), rec.reflected);
        if (specular_intensity < 0)
            specular_intensity = 0;
        else
            specular_intensity = std::pow(specular_intensity, mat.shininess) * mat.specular;    
    }
    float light_intensity = light.getIntensity() * (diffuse_intensity + specular_intensity);
    return (light.getColor() * light_intensity);
}

vec3f   Scenario::_reflection_contribution(const HitRecord& rec, int n_reflections) const
{
    const Material& mat = rec.hittable->getMaterial();
    Ray3f ray(rec.p, rec.reflected);
    vec3f color_shadow = _raytrace_single(ray, n_reflections - 1);
    return (color_shadow * mat.mirror);
}

vec3f    Scenario::_hit_color(const HitRecord& rec, int n_reflections) const
{
    const Material& mat = rec.hittable->getMaterial();
    vec3f color_shadow = _ambient_light.color * mat.ambient * _ambient_light.ratio;
    for (std::list<Light>::const_iterator it = _lights.begin(); it != _lights.end(); ++it)
        color_shadow += _hit_light_contribution(rec, *it);
    color_shadow = rt::elementwise_product(mat.color, color_shadow);
    if (n_reflections > 0 && mat.mirror > 1e-3)
        color_shadow += _reflection_contribution(rec, n_reflections);
    return (color_shadow);
}

bool    Scenario::_raytrace_hit(const Ray3f &ray, const Range& rng, HitRecord& rec) const
{
    bool hit_anything = false;

    for (std::list<AHittable *>::const_iterator it = _hittables.begin(); it != _hittables.end(); ++it)
    {
        HitRecord hit_rec;
        if ((*it)->hit(ray, rng, hit_rec))
        {
            if (!hit_anything || hit_rec.t < rec.t)
            {
                rec = hit_rec;
                rec.hittable = *it;
                hit_anything = true;    
            }
        }
    }
    if (hit_anything)
    {
        const Material& mat = rec.hittable->getMaterial();
        if (mat.wrinkle > 1e-5)
        {
            rec.normal = rec.normal + (vec3d_random() * mat.wrinkle);
            rec.normal = rec.normal.normalize();
        }
        if (rt::dot(ray.getDirection(), rec.normal) > 0)
            rec.normal *= -1; // -v is invalid ??
        rec.reflected = ray.reflected(rec.normal);
    }
    return (hit_anything);
}

vec3f    Scenario::_raytrace_single(const Ray3f& primary_ray, int n_reflections) const
{
    HitRecord    rec;

    if (_raytrace_hit(primary_ray, _rng, rec))
        return (_hit_color(rec, n_reflections));
    return (_ambient_light.color);
}
