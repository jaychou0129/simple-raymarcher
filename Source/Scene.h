// 
// Created by Balajanovski on 14/12/2017.
//

#ifndef SIMPLE_RAYTRACER_SCENE_H
#define SIMPLE_RAYTRACER_SCENE_H

#include "Lighting/LightBase.h"

#include "Geometry/Sphere.h"
#include "Geometry/SceneObject.h"
#include "Geometry/Vec3f.h"
#include "Geometry/Intersection.h"

#include <vector>
#include <memory>

class Scene {
public:
    void sceneSDF(IN const Vec3f& position, OUT Intersection& output_intersection, double power);
};


#endif //SIMPLE_RAYTRACER_SCENE_H
