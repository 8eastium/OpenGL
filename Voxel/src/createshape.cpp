//
// Created by joe on 26.02.22.
//

#include "createshape.h"
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

void createpoint(std::vector<float>& pointarray, float x, float y,float z) {
    pointarray.insert(pointarray.end(), {
            x,y,z
    });
}