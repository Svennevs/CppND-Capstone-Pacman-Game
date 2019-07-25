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

  void Render(Pacman const pacman, SDL_Point const &food, Fields const &fields);
  void UpdateWindowTitle(int foodLeft, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  /* const std::size_t grid_width;
  const std::size_t grid_height; */
};

#endif