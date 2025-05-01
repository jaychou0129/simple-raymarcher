#ifndef SIMPLE_RAYTRACER_MANDELBULB_H
#define SIMPLE_RAYTRACER_MANDELBULB_H

#include "Vec3f.h"
#include "Ray.h"
#include "../Color.h"
#include "SceneObject.h"
#include "../Material.h"

class Mandelbulb : public SceneObject {
public:
Mandelbulb(const Vec3f &center, const Material& surface_material);

    Vec3f center()        const { return m_center;           }
    // Vec3f rotate_point_y(double cx, double cz, double angle, Vec3f p);
    virtual void sdf(IN const Vec3f& position, OUT Intersection& output_intersection, IN const double power) const override;

private:
    Vec3f m_center;
    double m_power;
    double m_power_incr;
};


#endif //SIMPLE_RAYTRACER_MANDELBULB_H