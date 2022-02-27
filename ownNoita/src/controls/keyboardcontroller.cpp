//
// Created by joe on 25.02.22.
//

#include "keyboardcontroller.h"

bool getkey(GLFWwindow* window, int key) {
    int zero = glfwGetKey(window, key);
    if (zero == GLFW_PRESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}