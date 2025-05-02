// 
// Created by Balajanovski on 25/12/2017.
//

#include "ConfigManager.h"
#include "Geometry/Arcane.h"
#include "Geometry/Vec3f.h"
#include "Geometry/Sphere.h"
#include "Geometry/Box.h"
#include "Geometry/Menger.h"
#include "Geometry/Plane.h"
#include "Lighting/DirectionalLight.h"
#include "Lighting/PointLight.h"
#include "Geometry/Mandelbulb.h"
#include "Geometry/ApollonianGasket.h"

#include <iostream>
#include <string>
#include <yaml-cpp/yaml.h>

ConfigManager& ConfigManager::instance() {
    static ConfigManager instance;
    return instance;
}

void ConfigManager::load_file(const std::string &file_src) {
    auto config = YAML::LoadFile(file_src);

    if (!config["screen-width"]) {
        throw std::runtime_error("config file syntax error: no screen-width field detected."
                                   "\nEither the screen-width was improperly declared or is non-existent");
    }
    m_screen_width = config["screen-width"].as<int>();


    if (!config["screen-height"]) {
        throw std::runtime_error("config file syntax error: no screen-height field detected."
                                   "\nEither the screen-height was improperly declared or is non-existent");
    }
    m_screen_height = config["screen-height"].as<int>();

    if (!config["power"]) {
        throw std::runtime_error("config file syntax error: no power field detected."
            "\nEither the power field was improperly declared or is non-existent");
    }
    power = config["power"].as<double>();

    if (!config["color"]) {
        throw std::runtime_error("config file syntax error: no color field detected."
            "\nEither the color field was improperly declared or is non-existent");
    }
    color = config["color"].as<std::string>();

    if (!config["increment"]) {
        throw std::runtime_error("config file syntax error: no power field detected."
            "\nEither the power field was improperly declared or is non-existent");
    }
    increment = config["increment"].as<double>();

    if (!config["camera"]) {
        throw std::runtime_error("config file syntax error: no camera field detected."
                                   "\nEither the camera was improperly declared or is non-existent");
    }
    m_camera = std::make_shared<Camera>(Vec3f(config["camera"]["X"].as<float>(),
                                              config["camera"]["Y"].as<float>(),
                                              config["camera"]["Z"].as<float>()));


    auto objects = config["objects"];
    for (int i = 0; i < objects.size(); ++i)
    {
        if (objects[i]["type"].as<std::string>() == "Sphere") {
            auto properties = objects[i]["properties"];
            m_objects.push_back(std::make_shared<Sphere>(properties["center"].as<Vec3f>(),
                                                             properties["radius"].as<float>(),
                                                             properties["material"].as<Material>()));
        }
        else if (objects[i]["type"].as<std::string>() == "Mandelbulb") {
            auto properties = objects[i]["properties"];
            m_objects.push_back(std::make_shared<Mandelbulb>(properties["center"].as<Vec3f>(),
                                                             properties["material"].as<Material>()));
        }
        else if (objects[i]["type"].as<std::string>() == "ApollonianGasket") {
            auto properties = objects[i]["properties"];
            m_objects.push_back(std::make_shared<ApollonianGasket>(properties["center"].as<Vec3f>(),
                                                             properties["material"].as<Material>(),
                                                             properties["iterations"].as<size_t>()));
        }
        else if (objects[i]["type"].as<std::string>() == "Arcane") {
            auto properties = objects[i]["properties"];
            m_objects.push_back(std::make_shared<Arcane>(properties["center"].as<Vec3f>(),
                                                             properties["material"].as<Material>(),
                                                             properties["iterations"].as<size_t>()));
        }
        else if (objects[i]["type"].as<std::string>() == "Plane") {
            auto properties = objects[i]["properties"];
            Vec3f vec3f_normal = properties["normal"].as<Vec3f>();
            m_objects.push_back(std::make_shared<Plane>(Vec4f(vec3f_normal.x(),
                                                                vec3f_normal.y(),
                                                                vec3f_normal.z(),
                                                                properties["offset"].as<float>()),
                                                         properties["material"].as<Material>()));
        }
        else if (objects[i]["type"].as<std::string>() == "Box") {
            auto properties = objects[i]["properties"];
            float width   = properties["width"].as<float>();
            float height  = properties["height"].as<float>();
            float breadth = properties["breadth"].as<float>();

            m_objects.push_back(std::make_shared<Box>(properties["center"].as<Vec3f>(),
                                                      Vec3f(width / 2, height / 2, breadth / 2),
                                                      properties["material"].as<Material>()));
        }
        else if (objects[i]["type"].as<std::string>() == "Menger") {
            auto properties = objects[i]["properties"];

            m_objects.push_back(std::make_shared<Menger>(properties["center"].as<Vec3f>(),
                                                      properties["material"].as<Material>(),
                                                      properties["iterations"].as<size_t>()));
        }
        else {
            throw std::runtime_error("config file syntax error: no such object type as " + objects[i]["type"].as<std::string>());
        }
    }

    auto lights = config["lights"];
    for (int i = 0; i < lights.size(); ++i) {
        if (lights[i]["type"].as<std::string>() == "DirectionalLight") {
            auto properties = lights[i]["properties"];
            m_lights.push_back(std::make_shared<DirectionalLight>(properties["pos"].as<Vec3f>(),
                                                                  properties["light_dir"].as<Vec3f>(),
                                                                  properties["ambient"].as<float>(),
                                                                  properties["diffuse"].as<float>(),
                                                                  properties["specular"].as<float>(),
                                                                  properties["intensity"].as<float>(),
                                                                  properties["color"].as<Color>()));
        }
        else if (lights[i]["type"].as<std::string>() == "PointLight") {
            auto properties = lights[i]["properties"];
            m_lights.push_back(std::make_shared<PointLight>(properties["pos"].as<Vec3f>(),
                                                                  properties["ambient"].as<float>(),
                                                                  properties["diffuse"].as<float>(),
                                                                  properties["specular"].as<float>(),
                                                                  properties["intensity"].as<float>(),
                                                                  properties["attenuation"].as<float>(),
                                                                  properties["color"].as<Color>()));
        }
        else {
            throw std::runtime_error("config file syntax error: no such light type as " + lights[i]["type"].as<std::string>());
        }
    }

    m_config_loaded = true;
}

const std::shared_ptr<SceneObject> ConfigManager::get_object(int index) const {
    validate_config("objects");

    if (index < 0 || index >= m_objects.size()) {
        throw std::runtime_error("error: in ConfigManager::get_object, attempt to access object out of range"
                                         "\naccessing index: " + std::to_string(index));
    }

    return m_objects[index];
}

const std::shared_ptr<LightBase> ConfigManager::get_light(int index) const {
    validate_config("lights");

    if (index < 0 || index >= m_lights.size()) {
        throw std::runtime_error("error: in ConfigManager::get_light, attempt to access object out of range"
                                         "\naccessing index: " + std::to_string(index));
    }

    return m_lights[index];
}

void ConfigManager::validate_config(const std::string& field_accessed) const {
    if (!m_config_loaded) {
        throw std::runtime_error("error: attempted to access field " +
                                         field_accessed +
                                         " before the config was loaded");
    }
}


void ConfigManager::set_camera_rotation(const Vec3f& pivot, double rad) {
    Vec3f translated = m_camera->initial_pos() - pivot;

    double cos_r = std::cos(rad);
    double sin_r = std::sin(rad);

    double x_new = translated.x() * cos_r - translated.z() * sin_r;
    double z_new = translated.x() * sin_r + translated.z() * cos_r;

    Vec3f new_pos = Vec3f(x_new, translated.y(), z_new) + pivot;
    std::cout << "radius: " << rad << "\tnew_position: " << new_pos.x() << ", " << new_pos.y() << ", " << new_pos.z() << std::endl;
    m_camera->set_pos(new_pos);
}