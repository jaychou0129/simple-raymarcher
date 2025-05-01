// 
// Created by Balajanovski on 25/12/2017.
//

#ifndef SIMPLE_RAYTRACER_CONFIGMANAGER_H
#define SIMPLE_RAYTRACER_CONFIGMANAGER_H

#include "Geometry/SceneObject.h"
#include "Lighting/LightBase.h"
#include "Util/NonCopyable.h"
#include "Camera.h"

#include <vector>
#include <memory>
#include <string>

class ConfigManager : public Util::NonCopyable {
public:
    void load_file(const std::string& file_src);

    static ConfigManager& instance();

    const std::shared_ptr<SceneObject> get_object(int index) const;
    size_t get_amount_of_objects() const { validate_config("amount of objects"); return m_objects.size(); }

    const std::shared_ptr<Camera> get_camera() const { return m_camera; }
    void set_camera_rotation(const Vec3f& pivot, double rad);

    const std::shared_ptr<LightBase> get_light(int index) const;
    size_t get_amount_of_lights() const { validate_config("amount of lights"); return m_lights.size(); }

    int get_screen_width() const { return m_screen_width; }
    int get_screen_height() const { return m_screen_height; }
    double get_power() const { return power; }
    double get_increment() const { return increment; }
private:
    std::vector<std::shared_ptr<SceneObject>> m_objects;
    std::vector<std::shared_ptr<LightBase>> m_lights;
    std::shared_ptr<Camera> m_camera;

    void validate_config(const std::string& field_accessed) const;

    int m_screen_width;
    int m_screen_height;
    double power;
    double increment;

    bool m_config_loaded = false;
};


#endif //SIMPLE_RAYTRACER_CONFIGMANAGER_H
