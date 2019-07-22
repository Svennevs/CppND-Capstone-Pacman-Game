#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"
#include "fields.h"

class Snake {
  public:
    enum class Direction { kUp, kDown, kLeft, kRight, kWait };
    Snake(int grid_width, int grid_height)
        : grid_width(grid_width),
        grid_height(grid_height),
        head_x(3),
        head_y(4) {}
    void Update(Fields const &fields);
    //void GrowBody();
    //bool SnakeCell(int x, int y);
    Direction direction = Direction::kUp;
    float speed{0.1f};
    int size{1};
    bool alive{true};
    float head_x;
    float head_y;
    //std::vector<SDL_Point> body;
  private:
    void UpdateHead();
    //void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);
    //bool growing{false};
    int grid_width;
    int grid_height;
    
};


#endif