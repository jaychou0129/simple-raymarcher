// Arcane.h
#ifndef SIMPLE_RAYTRACER_ARCANE_H
#define SIMPLE_RAYTRACER_ARCANE_H

#include "Vec3f.h"
#include "Ray.h"
#include "../Color.h"
#include "SceneObject.h"
#include "../Material.h"

class Arcane : public SceneObject {
public:
    Arcane(const Vec3f& center, const Material& surface_material, int iterations);

    Vec3f center() const { return m_center; }

    virtual void sdf(IN const Vec3f& position,
                     OUT Intersection& output_intersection,
                     IN const double dummy = 0.0) const override;

private:
    Vec3f m_center;
    int m_iterations;
};

#endif // SIMPLE_RAYTRACER_ARCANE_H
