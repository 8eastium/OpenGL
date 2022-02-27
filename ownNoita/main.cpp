#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>

#include "src/render.h"
#include "src/controls/keyboardcontroller.h"
#include "src/createshape.h"

struct Pixel{
    int id = 0;
    bool update = false;
    //float x = 0.0f, y = 0.0f;
};

void Debug(std:: string s, int m) {
    std::cout << s << "\t" << m << '\n';
}

float calpos(const int intpos) {
    float r = intpos;
    return r / 600 * 10  - 1;
}

void update(GLFWwindow* window) {
    int esc = glfwGetKey(window, GLFW_KEY_ESCAPE);
    if (esc == GLFW_PRESS)
    {   glfwTerminate();
        exit(0);
    }
    int zero = glfwGetKey(window, GLFW_KEY_0);
    if (zero == GLFW_PRESS) { glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); }
    else { glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); }
}

int main() {
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(600, 600, " oNoita ", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    double previousTime = glfwGetTime();
    int frameCount = 0;

    std::vector<float> pixels;
    Pixel grit[120][120]; // x // y
    int number_vertices = 0;

    while(!glfwWindowShouldClose(window)) {
        pixels.clear();
        number_vertices = 0;
        keyboardcontroller keys;
        createshape shape;
        render render;
        for (int p = 0; p < 120; ++p) {
            for (int i = 0; i < 120; ++i) {
                if (grit[p][i].id != 0 && grit[p][i].update == false) {
                    number_vertices += 1;
                    shape.createpoint(pixels, calpos(p), calpos(i), 0.0f);
                    render.renderpoint(pixels, 5, number_vertices);
                    if(grit[p][i -1].id == 0 && i >= 2) {
                        grit[p][i - 1] = grit[p][i];
                        grit[p][i].id = 0;
                    }
                    else if (grit[p - 1][i -1].id == 0 && i >= 2) {
                        grit[p - 1][i - 1] = grit[p][i];
                        grit[p][i].id = 0;
                    }
                    else if (grit[p + 1][i -1].id == 0 && i >= 2) {
                        grit[p + 1][i - 1] = grit[p][i];
                        grit[p][i].id = 0;
                    }
                }
            }
        }
        int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
        if(state == GLFW_PRESS) {
            double xpos, ypos;
            //getting cursor position
            glfwGetCursorPos(window, &xpos, &ypos);
            int togridx = round(xpos), togridy = round(ypos);
            togridy += 1;
            if (togridx / 5 < 120 && togridx / 5 > -120 &&togridy / 5 < 120 && togridy / 5 > -120) {
                togridy = (togridy * -1) - 1;
                grit[togridx / 5][togridy / 5].id = 1;
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
        glClearColor ( 0.2f,0.2f ,0.2f , 1.0f );
        glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        update(window);
        double currentTime = glfwGetTime();
        frameCount++;
        if ( currentTime - previousTime >= 1.0 )
        {
            std::cout << "\nFPS : " << frameCount;
            frameCount = 0;
            previousTime = currentTime;
        }
    }
    glfwTerminate();
}