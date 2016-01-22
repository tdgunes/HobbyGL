//
// Created by Taha Doğan Güneş on 19/01/16.
//

#include <SDL_events.h>
#include "Controls.h"

Controls::Controls() {
    for (int i = 0; i < SDL_NUM_SCANCODES; ++i) {
        scancodes[i] = false;
    }
}

void Controls::update() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        SDL_Scancode scancode;
        if (event.key.keysym.scancode < 512 && event.key.keysym.scancode >= 0)
            scancode = event.key.keysym.scancode;
        else
            scancode = (SDL_Scancode) SDL_GetKeyFromScancode(event.key.keysym.scancode);
        if (event.type == SDL_KEYUP)
            scancodes[scancode] = false;
        else if (event.type == SDL_KEYDOWN)
            scancodes[scancode] = true;
    }
}


bool Controls::isPressed(int scancode) {
    return scancodes[scancode];
}