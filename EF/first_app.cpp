#include "first_app.h"


void FirstApp::run() {
     while (!efWindow.shouldClose()) {
        glfwPollEvents();
     }
}
