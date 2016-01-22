//
// Created by Taha Doğan Güneş on 18/01/16.
//

#pragma once

#include <glm/detail/type_vec2.hpp>
#include <GL/glew.h>
#include <string>

class SDL_Surface;

class Sprite {
public:
    Sprite(std::string);

    Sprite(const SDL_Surface *surface);

    ~Sprite();

    glm::vec2 position;
    glm::vec2 size;
    GLuint textureID;

private:

    GLenum mode;


    void loadTexture(const SDL_Surface *surface);
};



