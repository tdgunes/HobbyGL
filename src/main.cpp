
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "Constants.h"
#include "Sprite.h"
#include "Renderer.h"
#include "Controls.h"


int main(int argc, char *argv[]) {

    SDL_Window *mainWindow = SDL_CreateWindow(
            "HobbyGL",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WIDTH,
            HEIGHT,
            SDL_WINDOW_OPENGL
    );

    if (!mainWindow) {
        fprintf(stderr, "Unable to create window\n");
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_GLContext mainContext = SDL_GL_CreateContext(mainWindow);
    SDL_GL_SetSwapInterval(1);

    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "GLEW failed to init!\n");
    }

    SDL_GL_SwapWindow(mainWindow);


    bool loop = true;


    Controls controls;
    Renderer renderer;

    Sprite plane("assets/plane.png");
    Sprite missile("assets/missile.png");
    plane.position.y = 10;
    renderer.add(&plane);
    renderer.add(&missile);


    while (loop) {


        renderer.render();


        controls.update();
        if (controls.isPressed(SDL_SCANCODE_ESCAPE)) {
            loop = false;
        }
        if (controls.isPressed(SDL_SCANCODE_RIGHT)) {
            plane.position.x += 5;
        }
        if (controls.isPressed(SDL_SCANCODE_LEFT)) {
            plane.position.x -= 5;
        }

        SDL_GL_SwapWindow(mainWindow);
    }




    SDL_GL_DeleteContext(mainContext);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();

    return 0;
}