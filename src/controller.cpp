#include "controller.h"
#include <iostream>
#include <vector>
#include "SDL.h"

void Controller::ChangeDirection(Snake &snake , Snake::Direction input,
                                 Fields const &fields) const {
  
  int x_new = static_cast<int>(snake.head_x);
  int y_new = static_cast<int>(snake.head_y); 

  //don't allow change of direction towards wall
  switch (input){
    case Snake::Direction::kUp :
      y_new--;
      break;
    case Snake::Direction::kDown :
      y_new++;
      break;
    case Snake::Direction::kLeft :
      x_new--;
      break;
    case Snake::Direction::kRight :
      x_new++;
      break;
  }
  if(fields.isWall(x_new,y_new)){return;}
  snake.direction = input;

}

void Controller::HandleInput(bool &running, Snake &snake, Fields const &fields) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(snake, Snake::Direction::kUp,fields);
          break;

        case SDLK_DOWN:
          ChangeDirection(snake, Snake::Direction::kDown,fields);
          break;

        case SDLK_LEFT:
          ChangeDirection(snake, Snake::Direction::kLeft,fields);
          break;

        case SDLK_RIGHT:
          ChangeDirection(snake, Snake::Direction::kRight,fields);
          break;
      }
    }
  }
}