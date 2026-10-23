#include <GLFW/glfw3.h>
#include <iostream>
#include <cassert>

#include "types.hpp"

namespace Blokk {

    class Window {

    private:
        GLFWwindow* window_; // Pointer to window handle
        bool init_failed_; // If the initialization has failed
        bool initialized_; // If attempted to initialize

    public:
        Window(); // Initializes variables
        ~Window(); // Terminates GLFW, destroys window
        bool init(); // Initializes GLFW, creates window, handles states

        bool shouldClose(); // Returns if the window should be closed
        void clear(Color c); // Clear the screen with a color
        void update(); // Updates the window by rendering and polling events

        void maximize(); // Maximizes the window on the current monitor
        void minimize(); // Minimizes the window to the taskbar

        void restore(); // Restores the window from being minimized or maximized
        void setTitle(const char* title); // Sets the window's title

        uint32_t getWidth(); // Get the width of the window
        uint32_t getHeight(); // Get the height of the window
        vector2<uint32_t> getDimensions(); // Get the dimensions of the window
        float getAspectRatio(); // Get the aspect ratio (width/height)

        // Gets the window handle (for manual control, other libraries, etc)
        GLFWwindow* getNativeWindow() const;
    };
}
