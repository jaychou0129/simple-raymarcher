#include "Application.h"

#include "ScreenBuffer.h"
#include "ImageBuffer.h"
#include "Util/Shader.h"
#include "ConfigManager.h"

#include <stdexcept>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>


void initiate_png_mode(std::shared_ptr<PixelBufferBase>& pixel_buffer,
                       std::shared_ptr<Screen<int>>& screen) {
    std::cout << "\nPlease enter the location to where you want the scene to be drawn\nExample: To draw to files named "
            "scene_0.png, scene_1.png, ..., type scene" << std::endl;

    std::string src;
    while (!(std::cin >> src))
        ;

    pixel_buffer = std::make_shared<ImageBuffer>(screen, src);
}

void initiate_opengl_mode(std::shared_ptr<PixelBufferBase>& pixel_buffer,
                          std::shared_ptr<Screen<int>>& screen) {
    // Initialise pointer to a draw buffer
    pixel_buffer = std::make_shared<ScreenBuffer>(screen, "Shaders/vertex.vert", "Shaders/fragment.frag");
}

Application::Application() {
    std::cout << "Running raymarcher created by Balajanovski and modified by the Magical Fractals! team for CS 184 project..." << std::endl;

    m_screen = std::make_shared<Screen<int>>(0, ConfigManager::instance().get_screen_width(),
                                             0, ConfigManager::instance().get_screen_height());
    m_scene =  std::make_shared<Scene>();

#if defined(GLFW_FOUND) && defined(OPENGL_FOUND) && defined(PNG_FOUND)
    std::cout << "\nWould you like to draw the scene to a window or an image?\n"
              << "Type W for window or I for image" << std::endl;

    char response;
    while (!(std::cin >> response))
        ;

    switch (response) {
        case 'W' : case 'w' :
        {
            initiate_opengl_mode(m_stream, m_screen);
        }
            break;

        case 'I' : case 'i' :
        {
            initiate_png_mode(m_stream, m_screen);
        }
            break;

        default:
        {
            std::cout << "\nInvalid response: Shutting down" << std::endl;
            exit(EXIT_FAILURE);
        }
            break;
    }

#elif defined(GLFW_FOUND) && defined(OPENGL_FOUND)
    std::cout << "Warning: libPNG not found, initiating OpenGL mode" << std::endl;
    initiate_opengl_mode(m_stream, m_screen);
#elif defined(PNG_FOUND)
    std::cout << "Warning: GLFW / OpenGL not found, initiating libPNG mode" << std::endl;
    initiate_png_mode(m_stream, m_screen);
#else
    std::cout << "Fatal Error: Neither libPNG or GLFW were found\nShutting down..." << std::endl;
    exit(EXIT_FAILURE);
#endif

    m_raymarcher = std::make_shared<Raymarcher>(m_scene, m_stream, m_screen);
}

Application::~Application() {
    glfwTerminate();
}


void Application::run_loop() {
    // for (int i = 0; i < 360; i += 10) {
    //     std::cout << "Rendering frame " << i / 10 + 1 << " of 36" << std::endl;
    //     auto start_time = std::chrono::high_resolution_clock::now();
        
    //     // ConfigManager::instance().set_camera_rotation(Vec3f(0, 0, 0), i * M_PI / 180.0);
    //     m_raymarcher->calculate_frame();
        
    //     auto end_time = std::chrono::high_resolution_clock::now();
    //     auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    //     std::cout << "Rendered in " << duration << " ms" << std::endl;
        
    //     m_stream->flush();
    // }
    while(true) {
        m_raymarcher->calculate_frame();
        m_raymarcher->update_power();
        m_stream->flush();
    }

    std::cout << "Closing down..." << std::endl;
}