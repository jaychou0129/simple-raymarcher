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

    virtual void sdf(IN const Vec3f& position, OUT Intersection& output_intersection) const override;

private:
    Vec3f m_center;
};


#endif //SIMPLE_RAYTRACER_MANDELBULB_H