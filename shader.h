#ifndef SHADER_H_
#define SHADER_H_
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

typedef struct shader_program{
    GLuint shader_id;
    const char *vsrc;
    const char *fsrc;
}Shader;

GLuint makeShader(GLenum type, const char *src);
GLuint makeShaderProgram(GLuint sh1, GLuint sh2);
GLuint load_program(const char *p1, const char *p2);

Shader init_shader(const char *vsrc, const char *fsrc);

#endif