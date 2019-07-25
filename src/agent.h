#ifndef AGENT_H
#define AGENT_H

#include <random>
#include <vector>
#include <list>
#include <cmath>
#include <map>
#include "SDL.h"
#include "fields.h"

class Agent {
  public:
    enum class Direction { kUp=0, kLeft=1, kDown=2, kRight=3, kWait=4, kMove=5 }; //kMove is a placeholder to make the opposite map work
    std::map<Direction, Direction> opposite {{Direction::kUp, Direction::kDown}, {Direction::kDown, Direction::kUp},
                                             {Direction::kLeft, Direction::kRight}, {Direction::kRight, Direction::kLeft},
                                             {Direction::kWait, Direction::kMove}}; 
    
    Agent(Fields &_fields, float x_ini, float y_ini)
        : fields(_fields),
          pos_x(x_ini),
          pos_y(y_ini),
          pos{static_cast<int>(x_ini),static_cast<int>(y_ini)} {
            direction = Direction::kRight;
            directionchange = direction;
          }
          
    
    //getter/setters
    float getPosX() const {return pos.x;}
    float getPosY() const {return pos.y;}
    //Direction getDirection() const {return direction;}
    void setDirectionchange(Direction _direction){directionchange=_direction;}

    //other member funcs
    void Update();
    bool ChangeDirection();
    template <typename T> T Wrap(T input, int const &range);

    Fields &fields;

  protected:
    SDL_Point pos; 
    float pos_x;
    float pos_y;
    Direction direction;
    Direction directionchange;

  private:
    virtual void UpdateDirection(){};
    void StopAtWall();
    void MoveInDirection();

    /* int grid_width;
    int grid_height; */
    float speed{0.1f};
    
};


class Pacman : public Agent {
  public:
    Pacman(Fields &fields, float x_ini, float y_ini):Agent(fields, x_ini, y_ini) {};
    void die(){alive=false;}
    bool isAlive() const {return alive;}

  private:
    void UpdateDirection() override;
    bool alive{true};
};


class Monster : public Agent {

  public:
    static std::vector<Monster *> MonsterContainer;

    Monster(Fields &fields, Pacman &_pacman, float x_ini, float y_ini);

  private:
    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_dir;
    Pacman &pacman;

    void UpdateDirection() override;
    std::vector<Direction> DirectionPreference();

};



#endif