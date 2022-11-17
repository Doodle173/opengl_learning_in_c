#include "shader.h"
#include "util.h"
GLuint makeShader(GLenum type, const char *src){
   GLuint shader = glCreateShader(type);
   glShaderSource(shader, 1, &src, NULL);
   glCompileShader(shader);
   GLint status;
   glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
   if(status == GL_FALSE){
      GLint len;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
      GLchar *info = calloc(len, sizeof(GLchar));
      glGetShaderInfoLog(shader, len, NULL, info);
      fprintf(stderr, "glCompileShader failed:\n%s\n", info);
   }
   return shader;
}

GLuint makeShaderProgram(GLuint sh1, GLuint sh2){
   GLuint prgm = glCreateProgram();
   glAttachShader(prgm, sh1);
   glAttachShader(prgm, sh2);
   glLinkProgram(prgm);
   GLint status;
   glGetProgramiv(prgm, GL_LINK_STATUS, &status);
   if(status == GL_FALSE){
      GLint length;
      glGetProgramiv(prgm, GL_INFO_LOG_LENGTH, &length);
      GLchar *info = calloc(length, sizeof(GLchar));
      glGetProgramInfoLog(prgm, length, NULL, info);
      fprintf(stderr, "glLinkProgram failed: %s\n", info);
   }

   glDetachShader(prgm, sh1);
   glDetachShader(prgm, sh2);
   glDeleteShader(sh1);
   glDeleteShader(sh2);
   return prgm;
}

GLuint load_program(const char *p1, const char *p2){
   GLuint sh1 = makeShader(GL_VERTEX_SHADER, p1);
   GLuint sh2 = makeShader(GL_FRAGMENT_SHADER, p2);

   GLuint prgm = makeShaderProgram(sh1, sh2);
   return prgm;
}

Shader init_shader(const char *vsrc, const char *fsrc){
   Shader sh;

   sh.vsrc = readFile(vsrc);
   sh.fsrc = readFile(fsrc);
   sh.shader_id = load_program(sh.vsrc, sh.fsrc);
   return sh;

}