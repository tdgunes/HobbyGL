//
// Created by Taha Doğan Güneş on 18/01/16.
//

#include <stdio.h>
#include <stdlib.h>
#include "shaders.h"
#include "utils.h"


void Shaders_check(GLuint shaderID) {
    GLint Result = GL_FALSE;
    int32_t logLength;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        char errorMessage[logLength];
        glGetShaderInfoLog(shaderID, logLength, NULL, &errorMessage[0]);
        fprintf(stderr, "%s\n", errorMessage);
    }
}

GLuint Shaders_load(const char *vertex_file_path, const char *fragment_file_path) {
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    const char *vertexShaderCode = read_file(vertex_file_path);
    const char *fragmentShaderCode = read_file(fragment_file_path);

    if (!vertexShaderCode || !fragmentShaderCode) {
        fprintf(stderr, "Unable read shaders!\n");
    }

    printf("Compiling shader: %s\n", vertex_file_path);
    glShaderSource(vertexShaderID, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShaderID);
    Shaders_check(vertexShaderID);


    printf("Compiling shader: %s\n", fragment_file_path);
    glShaderSource(fragmentShaderID, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShaderID);
    Shaders_check(fragmentShaderID);


    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);


    GLint result = GL_FALSE;
    int32_t logLength;
    glGetProgramiv(programID, GL_LINK_STATUS, &result);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLength);

    if (logLength > 0) {
        char errorMessage[logLength];
        glGetProgramInfoLog(programID, logLength, NULL, &errorMessage[0]);
        fprintf(stderr, "%s\n", &errorMessage[0]);
    }

    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);


    free(vertexShaderCode);
    free(fragmentShaderCode);

    return programID;
}
