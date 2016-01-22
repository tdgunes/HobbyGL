//
// Created by Taha Doğan Güneş on 19/01/16.
//

#pragma once


#include <SDL_scancode.h>
#include <queue>

class Controls {
private:
    bool scancodes[SDL_NUM_SCANCODES];

public:
    Controls();

    void update();

    bool isPressed(int scancode);

};


