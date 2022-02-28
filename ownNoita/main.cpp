#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>
#include <random>

#include "src/render.h"
#include "src/controls/keyboardcontroller.h"
#include "src/createshape.h"
//#include "src/shader.h"

struct Pixel{
    int id = 0;
    bool update = false;
    //float x = 0.0f, y = 0.0f;
};

static unsigned int CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, & result);
    if (!result) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout<< "failed to compile "<< (type == GL_VERTEX_SHADER ? "vertex " : "fragment ") << "shader!\n";
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader,const std::string& fragmentShader ) {
    unsigned int programm = glCreateProgram();
    unsigned int vs = CompileShader( GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader( GL_VERTEX_SHADER, fragmentShader);

    glAttachShader(programm, vs);
    glAttachShader(programm, fs);
    glLinkProgram(programm);
    glValidateProgram(programm);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return programm;
}

int random(int min, int max) //range : [min, max]
{
    static bool first = true;
    if (first)
    {
        srand( time(NULL) ); //seeding for the first time only!
        first = false;
    }
    return min + rand() % (( max + 1 ) - min);
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

    createshape shape;

    // Generates Shader object using shaders defualt.vert and default.frag
    // Shader shaderProgram("src/Shader/default.vert", "src/Shader/default.frag");




    float t[] =
            {
                    -.5f, -.5f, 0.f,
                    0.f, .5f, 0.f,
                    .5f, -.5f, 0.f
            };
    uint32_t v;

    std::string vertexShader =
            "#version 330 core\n"
            "layout (location = 0) in vec3 aPos; // the position variable has attribute position 0\n"
            "\n"
            "out vec4 vertexColor; // specify a color output to the fragment shader\n"
            "\n"
            "void main()\n"
            "{\n"
            "    gl_Position = vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor\n"
            "    vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // set the output variable to a dark-red color\n"
            "}\n";
    std::string fragmentShader =
            "#version 330 core\n"
            "\n"
            "layout(location = 0) out vec4 color;\n"
            "\n"
            "void main(){\n"
            "   color = vec4(0.3, 0.4, 0.2,1.0 );\n"
            "}\n";


    unsigned int shader = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shader);
    glGenBuffers(1, &v);
    glBindBuffer(GL_ARRAY_BUFFER, v);
    glBufferData(GL_ARRAY_BUFFER, sizeof(t)*sizeof(t)/sizeof(t[0]), &t[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void*)0);
    glEnableVertexAttribArray(0);

    glViewport(0, 0, 600, 600);


    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    //comment
        /*
        pixels.clear();
        number_vertices = 0;
        keyboardcontroller keys;
        render render;

        int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
        if(state == GLFW_PRESS) {
            double xpos, ypos;
            //getting cursor position
            glfwGetCursorPos(window, &xpos, &ypos);
            int togrid_x = round(xpos), togrid_y = round(ypos);
            togrid_y += 1;
            if (togrid_x / 5 <= 120 && togrid_x / 5 >= -120 && grit[togrid_x / 5][togrid_y / 5].id == 0) {
                togrid_y = (togrid_y * -1);
                if (keys.getkey(window,65)) {
                    if (keys.getkey(window, 87)) {
                        grit[togrid_x / 5][togrid_y / 5].id = 2;
                        grit[togrid_x / 5 + 1][togrid_y / 5].id = 2;
                        grit[togrid_x / 5 ][togrid_y / 5 + 1].id = 2;
                        grit[togrid_x / 5 - 1][togrid_y / 5].id = 2;
                        grit[togrid_x / 5][togrid_y / 5 - 1].id = 2;
                    }
                    else {
                        grit[togrid_x / 5][togrid_y / 5].id = 1;
                        grit[togrid_x / 5 + 1][togrid_y / 5].id = 1;
                        grit[togrid_x / 5 ][togrid_y / 5 + 1].id = 1;
                        grit[togrid_x / 5 - 1][togrid_y / 5].id = 1;
                        grit[togrid_x / 5][togrid_y / 5 - 1].id = 1;
                    }
                } else {
                    if (keys.getkey(window, 87)) {
                        grit[togrid_x / 5][togrid_y / 5].id = 2;
                    }
                    else {
                        grit[togrid_x / 5][togrid_y / 5].id = 1;
                    }
                }

            }
        }

        for (int x = 0; x < 120; ++x) {
            for (int y = 0; y < 120; ++y) {
                if (grit[x][y].id != 0) {
                    number_vertices += 1;
                    shape.createpoint(pixels, calpos(x), calpos(y), 0.0f);
                    if (grit[x][y].id == 1) {
                        if(grit[x][y - 1].id == 0 && y >= 1 ) {
                            grit[x][y - 1].id = grit[x][y].id;
                            grit[x][y].id = 0;
                        }
                        else if (grit[x - 1][y -1].id == 0 && y >= 1 && x >= 1 && grit[x - 1][y].id == 0) {
                            grit[x - 1][y - 1].id = grit[x][y].id;
                            grit[x][y].id = 0;
                        }
                        else if (grit[x + 1][y -1].id == 0 && y >= 1 && x <= 120&& grit[x + 1][y].id == 0) {
                            grit[x + 1][y - 1].id = grit[x][y].id;
                            grit[x][y].id = 0;
                        }
                    }
                }
            }
        }

        render.renderpoint(pixels, 5, number_vertices);

        //grit[random(50,70)][100].id = 1;

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
    }*/
    glfwTerminate();

}