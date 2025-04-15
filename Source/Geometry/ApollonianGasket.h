#ifndef APOLLONIANGASKET_H
#define APOLLONIANGASKET_H

#include "Material.h"
#include "SceneObject.h"
#include "Vec3f.h"
#include "Intersection.h"

class ApollonianGasket : public SceneObject {
public:
    ApollonianGasket(const Vec3f& center, const Material& surface_material, size_t iterations = 10);

    virtual void sdf(IN const Vec3f& position, OUT Intersection& output_intersection, IN const double power) const override;

private:
    Vec3f m_center;
    int m_iterations;
};

#endif
