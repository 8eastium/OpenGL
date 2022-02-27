//
// Created by joe on 26.02.22.
//

#ifndef VOXEL_CREATESHAPE_H
#define VOXEL_CREATESHAPE_H

#include <vector>
#include <GLFW/glfw3.h>

class createshape {
public:
    void createrectangle(std::vector<float>& vertices, float size,float x, float y, float z) {
        vertices.insert(vertices.end(), {
                x - size, y - size, 0.0f,
                x + size, y + size, 0.0f,
                x + size, y - size, 0.0f,
                x - size, y + size, 0.0f,
                x + size, y + size, 0.0f,
                x - size, y - size, 0.0f,
        });
    }

    void createpoint(std::vector<float>& vertices ,float x, float y,float z) {
        vertices.insert(vertices.end(), {
                x,y,z
        });
    }
};


#endif //VOXEL_CREATESHAPE_H
