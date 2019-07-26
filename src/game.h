#ifndef GAME_H
#define GAME_H

#include <vector>
#include <iostream>
#include <cmath>
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

 private:
  Pacman pacman;
  Blinky blinky;
  Pinky pinky;
  Inky inky;
  Clyde clyde;
  
  Fields fields;

  Uint32 durationChase       = 18000;
  Uint32 durationScatter     = 7000;
  Uint32 durationFrightened  = 5000;
  Uint32 switchInterval      = 14000;
  Uint32 lastSwitchTimeStamp;

  int score{0};

  void Update();
};

#endif