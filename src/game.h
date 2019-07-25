#ifndef GAME_H
#define GAME_H

#include <vector>
//#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "agent.h"
#include "fields.h"

class Game {
 public:

  Game(std::string filename_map);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  //int GetSize() const;

 private:
  Pacman pacman;
  Monster monster1;
  Monster monster2;
  Monster monster3;
  Monster monster4;
  Fields fields;

  SDL_Point food;
  //std::vector<SDL_Point> walls;

  //std::uniform_int_distribution<int> random_w;
  //std::uniform_int_distribution<int> random_h;

  int score{0};

  //void PlaceFood();
  void Update();
};

#endif