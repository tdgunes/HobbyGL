//
// Created by Taha Doğan Güneş on 18/01/16.
//

#include <SDL_image.h>
#include <iostream>
#include "Sprite.h"
#include "Constants.h"

Sprite::Sprite(std::string path) : mode(GL_TRIANGLES) {
    position = glm::vec2(WIDTH / 2, HEIGHT / 2);
    SDL_Surface *surface = IMG_Load(path.c_str());
    loadTexture(surface);
}

Sprite::Sprite(const SDL_Surface *surface) {
    loadTexture(surface);
}

void Sprite::loadTexture(const SDL_Surface *surface) {
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glBindTexture(GL_TEXTURE_2D, 0);

    size = glm::vec2(surface->w, surface->h);
}


Sprite::~Sprite() {

}
