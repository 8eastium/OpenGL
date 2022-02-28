//
// Created by joe on 25.02.22.
//

#include <vector>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifndef VOXEL_RENDER_H
#define VOXEL_RENDER_H


class render {
public:
    void renderrectangle(std::vector<float> vertices, int numverts, GLFWwindow* window) {
        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(
                GL_ARRAY_BUFFER,
                vertices.size() * sizeof(float),
                &vertices.front(),
                GL_STATIC_DRAW
        );

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3,(void*)0);
        glEnableVertexAttribArray(0);
        glViewport(0, 0, 600, 600);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, numverts);
    }
    void renderpoint(std::vector<float> vertices,int size, int numverts) {
        //std::cout << "\nsize : " << sizeof(vertices) + (sizeof(float) * vertices.size());
        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(
                GL_ARRAY_BUFFER,
                vertices.size() * sizeof(float),
                &vertices.front(),
                GL_STATIC_DRAW
        );
        glPointSize( size );
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void *) 0);
        glEnableVertexAttribArray(0);
        glViewport(0, 0, 600, 600);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_POINTS, 0, numverts);
        vertices.clear();
    }
};


#endif //VOXEL_RENDER_H
