#include "agent.h"
#include <iostream>



void Agent::Update() {

  SDL_Point previous = pos; //capture previous truncated position

  UpdateDirection();
  MoveInDirection();
  
  SDL_Point current_cell{
      static_cast<int>(pos_x),
      static_cast<int>(pos_y)};  // Capture truncated position after updating

  //Stop if new position is a wall:
  if(fields.isWall(Wrap(current_cell.y,fields.getGrid_height()),Wrap(current_cell.x,fields.getGrid_width())  )){
    StopAtWall();
  }

  //update truncated position
  pos.x = static_cast<int>(pos_x);
  pos.y = static_cast<int>(pos_y); 

  /*
  if truncated position has changed, allow direction changes again.
  this prevents monsters from moving backwards at intersections
   */
  if (! isEqualPoint(pos,previous)) { 
    hasChosenDirectionThisCell= false;
  }

}


bool Agent::ChangeDirection() {
  SDL_Point posNew = pos;  //copy previous truncated position

  //predict future position
  switch (directionchange){
    case Direction::kUp :
      posNew.y--;
      break;
    case Direction::kDown :
      posNew.y++;
      break;
    case Direction::kLeft :
      posNew.x--;
      break;
    case Direction::kRight :
      posNew.x++;
      break;
  }

  //don't allow change if the next cell in this direction is a wall
  if(fields.isWall( Wrap(posNew.y,fields.getGrid_height()),Wrap(posNew.x,fields.getGrid_width()) )) {
    return false;}
  direction = directionchange;
  
  return true;
}

template <typename T> T Agent::Wrap(T input, int const & range){
  //allows for exiting screen and reentering at the other side
  return fmod(input + range, range);
}


void Agent::MoveInDirection() {
  switch (direction) {
    case Direction::kUp:
      pos_y -= speed;
      break;

    case Direction::kDown:
      pos_y += speed;
      break;

    case Direction::kLeft:
      pos_x -= speed;
      break;

    case Direction::kRight:
      pos_x += speed;
      break;
    case Direction::kWait: 
      break;
    case Direction::kMove:
      pos_y -= speed; //arbitrary direction
  }

  pos_x = Wrap(pos_x,fields.getGrid_width());
  pos_y = Wrap(pos_y,fields.getGrid_height());
}

void Agent::StopAtWall() {
  direction = Direction::kWait;
  pos_x = static_cast<float>(pos.x); //reset position to previous cell
  pos_y = static_cast<float>(pos.y);
}


//Pacman definitions

void Pacman::UpdateDirection(){
  if(direction != directionchange ){ //directionchange is set by keyboard in controller object
    ChangeDirection();
  }
}


//Monster definitions
std::vector<Monster *> Monster::MonsterContainer; //static container with monster pointers

Monster::State Monster::state = State::chase; //initialization of static monster state

//monster constructor initializes random number generator
Monster::Monster(Fields &fields, Pacman &_pacman, float y_ini, float x_ini)
    : Agent(fields, y_ini, x_ini),
      random_dir(0,3),
      engine(dev()),
      pacman(_pacman) {}


void Monster::UpdateDirection(){
  
  if(!hasChosenDirectionThisCell || direction==Direction::kWait){ //always allow direction changes if waiting for wall
    std::vector<Direction> order = DirectionPreference();

    for(Direction _direction : order){
      if(_direction != opposite[direction]){  // not allowed to go in opposite direction
        directionchange = _direction;         // propose direction change (equivalent of key stroke for pacman)
        if (ChangeDirection()){break;}        // checking for walls here, changing if possible
      }
    }
    hasChosenDirectionThisCell=true;
  }
}




std::vector<Agent::Direction> Monster::TargetMove(SDL_Point targetPos){
  //will move in direction of target, preferably in the farther dimension

  std::vector<Direction> order;
  int x_delta = targetPos.x - pos.x;
  int y_delta = targetPos.y - pos.y;

  Direction horizontalPreference=Direction::kRight;
  Direction verticalPreference=Direction::kDown;

  if (x_delta<0)
    horizontalPreference = Direction::kLeft;
  if (y_delta<0)
    verticalPreference = Direction::kUp;

  if(std::abs(x_delta) > std::abs(y_delta)){
    order.push_back(horizontalPreference);
    order.push_back(verticalPreference);
  } else{
    order.push_back(verticalPreference);
    order.push_back(horizontalPreference);
  }
  order.push_back(opposite[order[1]]);
  order.push_back(opposite[order[0]]); //last preference is opposite to the first preference

  return order;
}


SDL_Point Monster::PredictPacman(int n){

  SDL_Point futurePos{pacman.getPosX(),pacman.getPosY()}; 

  //predict pacmans position n steps ahead and use as target:
  switch (pacman.getDirection()){
    case Direction::kUp:
      futurePos.y= Wrap(futurePos.y-n,fields.getGrid_height());
      break;
    case Direction::kDown:
      futurePos.y = Wrap(futurePos.y+n,fields.getGrid_height());
      break;
    case Direction::kLeft:
      futurePos.x = Wrap(futurePos.x-n,fields.getGrid_width());
      break;
    case Direction::kRight:
      futurePos.x = Wrap(futurePos.x+n,fields.getGrid_width());
      break;
  }
  return futurePos;
}


std::vector<Agent::Direction> Monster::RandomMove(){
  //this is called when monsters are in frightened state

  std::vector<Direction> order;
  int randomInt = random_dir(engine);
  order.push_back(static_cast<Direction>(randomInt));
  return order;
}




std::vector<Agent::Direction> Blinky::DirectionPreference(){
  //Blinky simply targets pacmans position

  SDL_Point pacmanPos{pacman.getPosX(),pacman.getPosY()};
  
  switch (state){
    case State::chase:
      return TargetMove(pacmanPos);        // following
    case State::scatter:
      return TargetMove(scatterTarget);
  }
  //else frightened
  return RandomMove();
}


std::vector<Agent::Direction> Pinky::DirectionPreference(){
  //Pinky tries to ambush pacman by targeting its predicted position

  switch (state){
    case State::chase:
      return TargetMove(PredictPacman(4));  //ambush
    case State::scatter:
      return TargetMove(scatterTarget);
  }
  //else frightened
  return RandomMove();
}


std::vector<Agent::Direction> Inky::DirectionPreference(){
  //Inky targets a strange combination of pacmans 
  //predicted position and Blinkys position

  Monster * blinky = MonsterContainer[0];
  
  SDL_Point blinkyPos{blinky->getPosX(),blinky->getPosX()};
  SDL_Point pacmanFut = PredictPacman(2);

  SDL_Point targetPos{ Wrap(pacmanFut.x + (pacmanFut.x-blinkyPos.x)*2,fields.getGrid_width()), 
                       Wrap(pacmanFut.y + (pacmanFut.y-blinkyPos.y)*2,fields.getGrid_height())};

  switch (state){
    case State::chase:
      return TargetMove(targetPos); 
    case State::scatter:
      return TargetMove(scatterTarget);
  }
  //else frightened
  return RandomMove();
}

std::vector<Agent::Direction> Clyde::DirectionPreference(){
  //Clyde targets pacman like Blinky, unless he gets too close
  
  SDL_Point pacmanPos{pacman.getPosX(),pacman.getPosY()};
  int distToPacman = std::abs(pacmanPos.x- pos.x) + std::abs(pacmanPos.y - pos.y);

  switch (state){
    case State::chase:
      if (distToPacman < 6){
        return TargetMove(scatterTarget); // go to own corner if too close
      } else {
        return TargetMove(pacmanPos); // chase pacman if far away
      }
    case State::scatter:
      return TargetMove(scatterTarget);
  }
  //else frightened
  return RandomMove();
}
