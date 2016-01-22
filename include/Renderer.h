//
// Created by Taha Doğan Güneş on 19/01/16.
//

#pragma once

#include <vector>
#include <GL/glew.h>


enum VBO {
    vbo_position = 0,
    vbo_uv,
    MAX_VBO,
};

class Sprite;

class Renderer {

private:
    GLuint programID;
    std::vector<Sprite *> list;
    GLuint vbo[MAX_VBO];
    GLuint vboindices;

public:
    Renderer();

    void add(Sprite *sprite);

    ~Renderer();


    void render();


};



