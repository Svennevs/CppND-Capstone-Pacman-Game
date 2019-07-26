#ifndef AGENT_H
#define AGENT_H

#include <random>
#include <vector>
#include <map>
#include "SDL.h"
#include "fields.h"

class Agent {
  public:
    enum class Direction { kUp=0, kLeft=1, kDown=2, kRight=3, kWait=4, kMove=5 }; //kMove is a placeholder to make the opposite map work
    std::map<Direction, Direction> opposite {{Direction::kUp, Direction::kDown}, {Direction::kDown, Direction::kUp},
                                             {Direction::kLeft, Direction::kRight}, {Direction::kRight, Direction::kLeft},
                                             {Direction::kWait, Direction::kMove}}; 
    
    Agent(Fields &_fields, float y_ini, float x_ini)
        : fields(_fields),
          pos_y(y_ini),
          pos_x(x_ini),
          pos{static_cast<int>(x_ini),static_cast<int>(y_ini)} {
            direction = Direction::kRight;
            directionchange = direction;
          }
          
    //getter/setters
    int getPosY() const {return pos.y;}
    int getPosX() const {return pos.x;}
    Direction getDirection() const {return direction;}
    void setDirectionchange(Direction _direction){directionchange=_direction;}
    void setPos(int y, int x){
      pos.y = y;
      pos.x = x;
      pos_y = static_cast<float>(y);
      pos_x = static_cast<float>(x);
    }

    //other member funcs
    void Update();
    bool ChangeDirection();
    bool isEqualPoint(SDL_Point p1, SDL_Point p2){
      if(p1.x==p2.x && p1.y==p2.y)return true;
      return false;
    }
    template <typename T> T Wrap(T input, int const &range);

    Fields &fields; //a reference to the Fields object

  protected:
    SDL_Point pos; 
    float pos_y;
    float pos_x;
    Direction direction;
    Direction directionchange; //this is set by the controller (keyboard) and invokes a change of direction if possible
    bool hasChosenDirectionThisCell=false; 
    float speed = 0.1;

  private:
    virtual void UpdateDirection(){};
    void StopAtWall();
    void MoveInDirection();
   
    
};



class Pacman : public Agent {
  /*Pacman is a derived class of agent
    In addition, it has lives (and related methods) 
    and it overrides the UpdateDirection method.
   */

  public:
    Pacman(Fields &fields, float y_ini, float x_ini):Agent(fields, y_ini, x_ini) {};
    bool die(){
      lives--;
      if(lives==0)
        alive=false;
      return alive;
    }
    bool isAlive() const {return alive;}
    int getLives(){return lives;}

  private:
    void UpdateDirection() override;
    bool alive{true};
    int lives = 3;
};




class Monster : public Agent {
  /*Monster is a derived class of agent
    A static container with monster containers is defined, and some methods
    For manipulation of all monsters at the same time.
    All monsters have a state (chase, scatter or frightened) changing
    their behaviour.

   */

  public:
    enum class State{chase , scatter, frightened};
    
    // a few static methods to handle all monsters at the same time
    static std::vector<Monster *> MonsterContainer;

    static void setState(State _state){
      state = _state;
      if(_state==State::frightened){
        setSpeedAll(0.05);
        turnAroundAll();
      } else {
        setSpeedAll(0.1);
      }
    }

    static void setSpeedAll(float _speed){
      for (Monster * monster : MonsterContainer){
        monster->speed = _speed;
      }
    }

    static void setPosAll(int y, int x){
      for (Monster * monster : MonsterContainer){
        monster->setPos(y,x);
      }
    }

    static void turnAroundAll(){
      for (Monster * monster : MonsterContainer){
        monster->direction = monster->opposite[monster->direction];
      }
    }

    static State getState() {return state;}

    Monster(Fields &fields, Pacman &_pacman, float y_ini, float x_ini);

    int getColorValueR() const {return ColorRGB[0];}
    int getColorValueG() const {return ColorRGB[1];}
    int getColorValueB() const {return ColorRGB[2];}

  protected:
    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_dir;
    Pacman &pacman;
    static State state;

    void UpdateDirection() override;
    std::vector<Direction> TargetMove(SDL_Point targetpos);
    std::vector<Direction> RandomMove();  
    SDL_Point PredictPacman(int n);

    virtual std::vector<Direction> DirectionPreference(){std::vector<Direction> placeholder; return placeholder;}

    std::vector<int> ColorRGB;
};

/* 
As in the real pacman, all 4 monsters have different behaviour.
To account for this they all have a derived class, with different color and
an overriden DirectionPreference method
*/

class Blinky : public Monster{
  public:
    Blinky(Fields &fields, Pacman &_pacman, float y_ini, float x_ini):Monster(fields, _pacman, y_ini, x_ini) {ColorRGB = {255,0,0};};
    
  private:
    std::vector<Direction> DirectionPreference() override;
    SDL_Point scatterTarget{3,3};
};
class Pinky : public Monster{
  public:
    Pinky(Fields &fields, Pacman &_pacman, float y_ini, float x_ini):Monster(fields, _pacman, y_ini, x_ini) {ColorRGB = {255,105,180};};
  private:
    std::vector<Direction> DirectionPreference() override;
    SDL_Point scatterTarget{3,24};
};

class Inky : public Monster{
  public:
    Inky(Fields &fields, Pacman &_pacman, float y_ini, float x_ini):Monster(fields, _pacman, y_ini, x_ini) {ColorRGB = {0,255,255};};
  private:
    std::vector<Direction> DirectionPreference() override;
    SDL_Point scatterTarget{24,26};
};

class Clyde : public Monster{
  public:
    Clyde(Fields &fields, Pacman &_pacman, float y_ini, float x_ini):Monster(fields, _pacman, y_ini, x_ini) {ColorRGB = {255,140,0};};
  private:
    std::vector<Direction> DirectionPreference() override;
    SDL_Point scatterTarget{24,3};
};



#endif