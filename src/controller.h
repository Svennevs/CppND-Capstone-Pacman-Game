#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include "fields.h"

class Controller {
 public:
  void HandleInput(bool &running, Snake &snake, Fields const &fields)  const;

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input, Fields const &fields) const;
};

#endif