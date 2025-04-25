#include "ApollonianGasket.h"
#include <algorithm>
#include <iostream>
#include <cmath>

ApollonianGasket::ApollonianGasket(const Vec3f& center, const Material& material, size_t iterations)
    : SceneObject(material), m_center(center), m_iterations(iterations) {}

void ApollonianGasket::sdf(const Vec3f& position, Intersection& output_intersection, const double power) const {
    Vec3f p = position - m_center;
    float scale = 1.0f;

    for (int i = 0; i < m_iterations; ++i) {
        float r2 = p.dot(p);
        if (r2 < 1e-6f) break;

        p = p / r2;
        p = abs(p);

        float x = p.x(), y = p.y(), z = p.z();
        if (x < y) { float tmp = x; x = y; y = tmp; }
        if (x < z) { float tmp = x; x = z; z = tmp; }
        if (y < z) { float tmp = y; y = z; z = tmp; }

        p = Vec3f(x, y, z);
        p = p * 2.5f - Vec3f(1.0f, 1.0f, 1.0f);
        scale *= 2.5f;
    }

    float dist = p.len() / scale - 0.05f;

    output_intersection = Intersection(dist, surface_material(), position);
}
