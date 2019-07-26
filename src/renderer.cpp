#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height)
    : screen_width(screen_width),
      screen_height(screen_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Pacman const pacman, Fields const &fields) {
  SDL_Rect block;
  block.w = screen_width / fields.getGrid_width();
  block.h = screen_height / fields.getGrid_height();

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);
  
  // Render walls and food
  for(int x=0;x<fields.getGrid_width();x++){
    for(int y=0;y<fields.getGrid_height();y++){
      if(fields.isWall(y,x)){
        SDL_SetRenderDrawColor(sdl_renderer, 50, 50, 50, 0);
        block.x = x * block.w;
        block.y = y * block.h;
        SDL_RenderFillRect(sdl_renderer, &block);
      } else if (fields.hasFood(y,x)){
        SDL_SetRenderDrawColor(sdl_renderer, 100, 100, 0, 0);
        block.x = x * block.w;
        block.y = y * block.h;
        SDL_RenderFillRect(sdl_renderer, &block);
      } else if (fields.hasPowerUp(y,x)){
        SDL_SetRenderDrawColor(sdl_renderer, 255, 100, 0, 0);
        block.x = x * block.w;
        block.y = y * block.h;
        SDL_RenderFillRect(sdl_renderer, &block);                 
      }
    }
  }
  
  // Render monsters
  for (Monster * monster : Monster::MonsterContainer){
    block.x = monster->getPosX() * block.w;
    block.y = monster->getPosY() * block.h;
    SDL_SetRenderDrawColor(sdl_renderer, monster->getColorValueR(), monster->getColorValueG(), monster->getColorValueB(), 150);
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render pacman
  block.x = pacman.getPosX() * block.w;
  block.y = pacman.getPosY() * block.h;
  if (pacman.isAlive()) {
    SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 0, 0);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 50, 0, 0, 0);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int foodLeft, int fps, int lives) {
  std::string title{"Food left: " + std::to_string(foodLeft) + " FPS: " + std::to_string(fps) + " Lives left: " + std::to_string(lives) };
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
