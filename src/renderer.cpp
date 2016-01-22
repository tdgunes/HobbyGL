//
// Created by Taha Doğan Güneş on 19/01/16.
//

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Renderer.h"
#include "Constants.h"
#include "Shaders.h"
#include "Sprite.h"


Renderer::Renderer() {
    glClearColor(0.0f, 0.0f, 1.0f, 0.0f);

    GLuint vaoid;
    glGenVertexArrays(1, &vaoid);
    glBindVertexArray(vaoid);


    programID = Shaders_load("./shaders/simple.vs", "./shaders/simple.fs");

    static const GLfloat vertices[] = {0, 1.0, 0, // top left corner
                                       1.0, 1.0, 0, // top right corner
                                       1.0, 0, 0, // bottom right corner
                                       0, 0, 0}; // bottom left corner

    static const GLfloat uvs[] = {0, 0,
                                  1, 0,
                                  1, 1,
                                  0, 1};

    static const unsigned int indices[] = {0, 1, 2, // first triangle (bottom left - top left - top right)
                                           0, 2, 3}; // second triangle (bottom left - top right - bottom right)

    glGenBuffers(MAX_VBO, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[vbo_position]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[vbo_uv]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

    glGenBuffers(1, &vboindices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboindices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
}

void Renderer::add(Sprite *sprite) {
    list.push_back(sprite);
}

void Renderer::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glm::mat4 projection = glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT);
    glUseProgram(programID);


    for (Sprite *sprite : list) {
        glm::mat4 MVP = projection * glm::scale(
                glm::translate(glm::mat4(1.0f), glm::vec3(sprite->position.x, sprite->position.y, 0.0f)),
                glm::vec3(sprite->size.x, sprite->size.y, 0.0f));


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, sprite->textureID);

        glUniformMatrix4fv(glGetUniformLocation(programID, "MVP"), 1, GL_FALSE, &MVP[0][0]);
        glUniform1i(glGetUniformLocation(programID, "tex"), 0);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[vbo_position]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[vbo_uv]);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *) 0);


        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboindices);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *) 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
    }


}

Renderer::~Renderer() {
    glDeleteBuffers(MAX_VBO, vbo);
    glDeleteVertexArrays(MAX_VBO, vbo);
    glDeleteProgram(programID);
}
