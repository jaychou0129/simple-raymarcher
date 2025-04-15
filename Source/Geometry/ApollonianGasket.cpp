#include "ApollonianGasket.h"

ApollonianGasket::ApollonianGasket(const Vec3f &center, const Material& surface_material, size_t iterations)
    : SceneObject(surface_material), m_center(center), m_iterations(iterations) { }

void ApollonianGasket::sdf(IN const Vec3f& position, OUT Intersection& output_intersection, IN const double power,) const {
    auto gasket_material = surface_material();

    Vec3f p = position - m_center;
    Color color = gasket_material.color();

    float min_radius = 0.0005f;
    float distance = 0.0f;
    float s = 1.0f;

    for (int i = 0; i < m_iterations; ++i) {
        float r2 = p.dot(p);
        if (r2 == 0.0f) break;

        // Sphere inversion
        p = p / r2;

        // Reflect across symmetry planes
        p = abs(p);
        float temp;
        if (p.x() < p.y()) {
            temp = p.x();
            p.set_x(p.y());
            p.set_y(temp);
        }
        if (p.x() < p.z()) {
            temp = p.x();
            p.set_x(p.z());
            p.set_z(temp);
        }
        if (p.y() < p.z()) {
            temp = p.y();
            p.set_y(p.z());
            p.set_z(temp);
        }

        // Tighten the packing
        p = p * 2.0f - Vec3f(1.0f, 1.0f, 1.0f);
        s *= 2.0f;
    }

    distance = 0.5f * p.len() / s - min_radius;

    // Optional: Slight color based on fractal depth
    Color fractal_color(0.6f, 0.4f, 0.9f); // A light purple tone
    Color mixed_color;
    mix(color, fractal_color, 0.4f, mixed_color);

    output_intersection = Intersection(distance,
                                       Material(gasket_material.float_specular(),
                                                gasket_material.float_diffuse(),
                                                gasket_material.float_ambient(),
                                                gasket_material.shininess(),
                                                mixed_color),
                                       position);
}
