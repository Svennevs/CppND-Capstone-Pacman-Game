#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "agent.h"
#include "fields.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height);
  ~Renderer();

  void Render(Pacman const pacman, Fields const &fields);
  void UpdateWindowTitle(int foodLeft, int fps, int lives);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
 
};

#endif