#include "Mandelbulb.h"

Mandebulb::Mandelbulb(const Vec3f &center, float radius, const Material& surface_material)
        : m_center(center), m_radius(radius), m_radius2(radius * radius), SceneObject(surface_material) { }

void Mandelbulb::sdf(IN const Vec3f& position, OUT Intersection& output_intersection) const {
    Vec3f sample_point = position + center();
    output_intersection = Intersection(sample_point.len() - radius(), surface_material(), position);
    return;
}