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

void Renderer::Render(Pacman const pacman, SDL_Point const &food, Fields const &fields) {
  SDL_Rect block;
  block.w = screen_width / fields.getGrid_width();
  block.h = screen_height / fields.getGrid_height();

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);
  
  // Render walls and food
  for(int x=0;x<fields.getGrid_width();x++){
    for(int y=0;y<fields.getGrid_height();y++){
      if(fields.isWall(x,y)){
        SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0x00, 0xFF);
        block.x = x * block.w;
        block.y = y * block.h;
        SDL_RenderDrawRect(sdl_renderer, &block);
      } else if (fields.hasFood(x,y)){
        SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        block.x = x * block.w;
        block.y = y * block.h;
        SDL_RenderFillRect(sdl_renderer, &block);         
      }
    }
  }
  
  // Render monster (replace by loop)
  for (Monster * monster : Monster::MonsterContainer){
    block.x = monster->getPosX() * block.w;
    block.y = monster->getPosY() * block.h;
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render pacman
  block.x = pacman.getPosX() * block.w;
  block.y = pacman.getPosY() * block.h;
  if (pacman.isAlive()) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int foodLeft, int fps) {
  std::string title{"Food left: " + std::to_string(foodLeft) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
