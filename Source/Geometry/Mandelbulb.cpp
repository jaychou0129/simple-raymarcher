#include "Mandelbulb.h"
#include "Geometry/Vec3f.h"
#include <cmath>
#define rot 100.f

Mandelbulb::Mandelbulb(const Vec3f &center, const Material& surface_material, double power, double increment)
    : SceneObject(surface_material), m_center(center), m_power(power), m_power_incr(increment) { }


// Vec3f Mandelbulb::rotate_point_y(double cx, double cz, double angle, Vec3f p) {
//     double s = std::sin(angle * M_PI / 180.0);
//     double c = std::cos(angle * M_PI / 180.0);

//     // translate point back to origin:
//     p = Vec3f(p.x() - cx, p.y(), p.z() - cz);

//     // rotate point
//     double xnew = p.x() * c - p.z() * s;
//     double znew = p.x() * s + p.z() * c;

//     // translate point back:
//     p = Vec3f(xnew + cx, p.y(), znew + cz);
//     return p;
// }

void Mandelbulb::sdf(IN const Vec3f& position, OUT Intersection& output_intersection, IN const double power) const {
    // Vec3f cam = position + center();
    Vec3f cam = position;

    // Rotate on y-axis — assuming you have a rotate_point_y function
    // cam = rotate_point_y(0, 0, rot, cam); // rot is assumed to be a member variable

    Vec3f z = cam;
    double dr = 1.0;
    double r = 0.0;

    const int MAX_ITER = 100; // or whatever is appropriate

    for (int i = 0; i < MAX_ITER; ++i) {
        r = z.len();
        if (r > 2.0) break;

        // Convert to polar coordinates
        double theta = std::acos(z.z() / r);
        double phi = std::atan2(z.y(), z.x());
        dr = std::pow(r, power - 1.0) * power * dr + 1.0;

        // Scale and rotate the point
        double zr = std::pow(r, power);
        theta *= power;
        phi *= power;

        // Convert back to cartesian coordinates
        double sin_theta = std::sin(theta);
        z = Vec3f(
            sin_theta * std::cos(phi),
            sin_theta * std::sin(phi),
            std::cos(theta)
        ) * zr;

        z = z + cam;
    }

    double dist = 0.5 * std::log(r) * r / dr;

    output_intersection = Intersection(dist, surface_material(), position);
}
