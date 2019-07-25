#include "controller.h"
#include <iostream>
#include "SDL.h"



void Controller::HandleInput(bool &running, Agent &pacman) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          pacman.setDirectionchange(Agent::Direction::kUp);
          break;

        case SDLK_DOWN:
          pacman.setDirectionchange(Agent::Direction::kDown);
          break;

        case SDLK_LEFT:
          pacman.setDirectionchange(Agent::Direction::kLeft);
          break;

        case SDLK_RIGHT:
          pacman.setDirectionchange(Agent::Direction::kRight);
          break;
      }
    }
  }
}