<#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>

#include "src/render.h"
#include "src/controls/keyboardcontroller.h"
#include "src/createshape.h"

void update(GLFWwindow* window) {
    int esc = glfwGetKey(window, GLFW_KEY_ESCAPE);
    if (esc == GLFW_PRESS)
    {
        glfwTerminate();
        exit(0);
    }
    int zero = glfwGetKey(window, GLFW_KEY_0);
    if (zero == GLFW_PRESS) { glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); }
    else { glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); }
    glClearColor ( 0.2f,0.2f ,0.2f , 1.0f );
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

int main() {
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(600, 600, " Voxel ", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    std::vector<float> vertices;
    std::vector<float> points;
    

    float size = 0.05f;
    float x = 0.0f;
    float z = 0.0f;
    float y = 0.0f;
	int numverts = 0;

    double previousTime = glfwGetTime();
    int frameCount = 0;

	while(!glfwWindowShouldClose(window)) {
        vertices.clear();
        points.clear();

        keyboardcontroller key;
        if (key.getkey(window, 87)) { y += 0.005; }
        if (key.getkey(window, 83)) { y -= 0.005; }
        if (key.getkey(window, 68)) { x += 0.005; }
        if (key.getkey(window, 65)) { x -= 0.005; }
       // if ()
        y -= 0.005;

        render render;
        createshape shape;
        numverts += 1;
        shape.createpoint(vertices ,x, y ,z);
        render.renderpoint(vertices, 6 ,numverts);
        //render.renderpoint(points, numverts + 194, 6 ,window);

        glfwSwapBuffers(window);
        glfwPollEvents();
        update(window);

        double currentTime = glfwGetTime();
        frameCount++;
        if ( currentTime - previousTime >= 1.0 )
        {
            std::cout <<"FPS : " << frameCount;
            std::cout << "\tY : "<< y << "\tX : "<< x << '\n';

            frameCount = 0;
            previousTime = currentTime;
        }
    }
    glfwTerminate();
}