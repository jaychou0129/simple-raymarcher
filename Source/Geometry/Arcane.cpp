// Arcane.cpp
// Inspired by the fractal animation in Arcane

#include "Arcane.h"
#include <cmath>

Arcane::Arcane(const Vec3f& center, const Material& surface_material, int iterations)
    : SceneObject(surface_material), m_center(center), m_iterations(iterations) { }

void Arcane::sdf(IN const Vec3f& position, OUT Intersection& output_intersection, IN const double dummy) const {
    Vec3f p = position - m_center;
    float scale = 1.5f;
    float min_dist = 1e10f;

    // Base bounding sphere
    float bounding_radius = 1.5f;
    float base_sphere = p.len() - bounding_radius;
    min_dist = base_sphere;

    // Inversion-based sphere packing (Apollonian-like)
    for (int i = 0; i < m_iterations; ++i) {
        // Tiling space to create repeating patterns
        p.set_x(fmod(p.x() * scale, 2.0f) - 1.0f);
        p.set_y(fmod(p.y() * scale, 2.0f) - 1.0f);
        p.set_z(fmod(p.z() * scale, 2.0f) - 1.0f);

        // Radial distortion (bubble-like inversion)
        float r2 = p.dot(p);
        if (r2 == 0.0f) r2 = 1e-6f; // avoid division by zero
        float k = 1.0f / r2;
        p = p * k;

        scale *= 2.0f;
        float d = p.len() - 0.5f;
        min_dist = std::max(min_dist, -d / scale);
    }

    output_intersection = Intersection(min_dist, surface_material(), position);
}
