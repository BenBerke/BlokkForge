#include <GLFW/glfw3.h>
#include <iostream>
#include <cassert>

#include "types.hpp"

namespace Blokk {
    Window::Window() {
        window_ = nullptr;
        initialized_ = false;
        init_failed_ = false;
    }

    Window::~Window() {
        if (window_ != nullptr) 
            glfwDestroyWindow(window_);
        glfwTerminate();
    }

    bool Window::init() {

        assert(!init_failed_ && "Blokk: GLFW Initialization failed, but tried to re-initialize");
        if (initialized_) {
            return true;
        }

        // Initialize GLFW
        if (!glfwInit()) { // Return error if fails
            std::cerr << "Blokk: Failed to initialize GLFW \n";
            init_failed_ = true;
            return false;
        }

        // Create the actual window
        window_ = glfwCreateWindow(800, 600, "Blokk Engine", NULL, NULL);
        if (!window_) { // If fails return an error and terminate
            std::cerr << "Blokk: Failed to create GLFW window \n";
            glfwTerminate();
            init_failed_ = true;
            return false;
        }

        // Graphics commands connect to THIS window
        glfwMakeContextCurrent(window_);

        //-------------------------------------------------------------------
        initialized_ = true;
        return true;
    }

    // Returns if the window should be closed
    bool Window::shouldClose() {
        // Initialize, if fails, throw an error
        assert(init() && "Blokk: GLFW Initialization failed, but tried to run function");

        // Get value from GLFW
        return glfwWindowShouldClose(window_);
    }

    // Clear the screen
    void Window::clear(Color c) {
        glClearColor(c.r, c.g, c.b, c.a);
        glClear(GL_COLOR_BUFFER_BIT);
    }


    // Updates the window by rendering and polling events
    void Window::update() {
        assert(initialized_ && !init_failed_ && "Blokk: Cannot update an uninitialized window!");
        glfwSwapBuffers(window_); // Flipped drawing onto the screen
        glfwPollEvents(); // Checks for keys, dragging, and resizing
    }


    // Instantly maximizes the window on the current monitor
    void Window::maximize() {
        assert(window_ != nullptr);
        glfwMaximizeWindow(window_);
    }

    // Minimizes the window to the taskbar
    void Window::minimize() {
        assert(window_ != nullptr);
        glfwIconifyWindow(window_);
    }

    // Restores the window from being minimized or maximized
    void Window::restore() {
        assert(window_ != nullptr);
        glfwRestoreWindow(window_);
    }
        
    // Sets the window's title
    void Window::setTitle(const char* title)
    {
        assert(initialized_ && window_ != nullptr);
        glfwSetWindowTitle(window_, title);
    }

    // Get the width of the window
    uint32_t Window::getWidth() {
        assert(window_ != nullptr && "Blokk: Window is not correctly initialized before using Window::getWidth");
        int32_t width;
        glfwGetWindowSize(window_, &width, nullptr);
        return width;
    }

    // Get the height of the window
    uint32_t Window::getHeight() {
        assert(window_ != nullptr && "Blokk: Window is not correctly initialized before using Window::getHeight");
        int32_t height;
        glfwGetWindowSize(window_, nullptr, &height);
        return height;
    }

    // Get the dimensions of the window
    vector2<uint32_t> Window::getDimensions() {
        assert(window_ != nullptr && "Blokk: Window is not correctly initialized before using Window::getDimensions");
        vector2<int32_t> dimensions;
        glfwGetWindowSize(window_, &dimensions.x, &dimensions.y);
        return dimensions;
    }

    // Get the aspect ratio (width/height)
    float Window::getAspectRatio() {
        assert(window_ != nullptr && "Blokk: Window is not correctly initialized before using Window::getAspectRatio");
        vector2<int32_t> dimensions = getDimensions();
        return static_cast<float>(dimensions.x) / static_cast<float>(dimensions.y);
    }

    // Gets the window handle (for manual control, other libraries, etc)
    GLFWwindow* Window::getNativeWindow() const {
        assert(window_ != nullptr);
        return window_;
    }
}
