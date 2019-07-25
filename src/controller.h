#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "agent.h"

class Controller {
 public:
  void HandleInput(bool &running, Agent &pacman)  const;

};

#endif