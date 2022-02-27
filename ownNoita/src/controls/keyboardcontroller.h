//
// Created by joe on 25.02.22.
//

#include <GLFW/glfw3.h>

#ifndef VOXEL_KEYBOARDCONTROLLER_H
#define VOXEL_KEYBOARDCONTROLLER_H


class keyboardcontroller {
public:
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
};


#endif //VOXEL_KEYBOARDCONTROLLER_H
