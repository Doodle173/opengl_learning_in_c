#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "util.h"
#include "shader.h"

static void error_callback(int error, const char *description)
{
   fprintf(stderr, "Error: %s\n", description);
}
int main(void)
{
   printf("test\n");
   GLFWwindow *window;
   if (!glfwInit())
   {
      return -1;
   }

   glfwSetErrorCallback(error_callback);

   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

   if (!window)
   {
      glfwTerminate();
      exit(EXIT_FAILURE);
   }

   glfwMakeContextCurrent(window);
   glfwSwapInterval(1);

   GLenum err = glewInit();
   if (GLEW_OK != err)
   {
      /* Problem: glewInit failed, something is seriously wrong. */
      fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
   }

   float vertices[] = {
       -0.5f, -0.5f, 0.0f,
       0.5f, -0.5f, 0.0f,
       0.0f, 0.5f, 0.0f
   };

   Shader my_shader = init_shader("resources/shaders/vertex.glsl", "resources/shaders/fragment.glsl");
   
   unsigned int vbo, vao;
   glGenVertexArrays(1, &vao);
   glGenBuffers(1, &vbo);
   glBindVertexArray(vao);

   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);

   glBindVertexArray(vao);


   
   while (!glfwWindowShouldClose(window))
   {
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      glUseProgram(my_shader.shader_id);

      int color_location = glGetUniformLocation(my_shader.shader_id, "triangle_color");
      glUniform4f(color_location, 0.0f, 0.0f, 1.0f, 1.0f);

      glBindVertexArray(vao);
      glDrawArrays(GL_TRIANGLES, 0, 3);
      
      glfwSwapBuffers(window);
      glfwPollEvents();
   }

   glfwDestroyWindow(window);
   glfwTerminate();
   exit(EXIT_SUCCESS);
}
