#include "agent.h"
#include <iostream>



void Agent::Update() {

  UpdateDirection();
  MoveInDirection();
  
  SDL_Point current_cell{
      static_cast<int>(pos_x),
      static_cast<int>(pos_y)};  // Capture cell after updating

  //Don't move if new position is a wall:
  if(fields.isWall(Wrap(current_cell.x,fields.getGrid_width()), Wrap(current_cell.y,fields.getGrid_height())  )){
    StopAtWall();
  }

  //update truncated position
  pos.x = static_cast<int>(pos_x);
  pos.y = static_cast<int>(pos_y); 

}

bool Agent::ChangeDirection() {
  SDL_Point posNew = pos;  //copy previous truncated position

  //predict possible (dep on truncation) new position
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

  //don't allow change of direction towards wall
  if(fields.isWall( Wrap(posNew.x,fields.getGrid_width()), Wrap(posNew.y,fields.getGrid_height()) )) {
    return false;}
  direction = directionchange;

  return true;
}

template <typename T> T Agent::Wrap(T input, int const & range){
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
    case Direction::kWait: //in case of running into a wall
      break;
  }

  // Wrap the Agent around to the beginning if going off of the screen.
  pos_x = Wrap(pos_x,fields.getGrid_width());
  pos_y = Wrap(pos_y,fields.getGrid_height());
}

void Agent::StopAtWall() {
  std::cout << "hit wall" << std::endl;
  direction = Direction::kWait;
  pos_x = static_cast<float>(pos.x);
  pos_y = static_cast<float>(pos.y);
}


//pacman definitions

void Pacman::UpdateDirection(){
  if(direction != directionchange ){
    ChangeDirection();
  }
}


//Monster definitions
std::vector<Monster *> Monster::MonsterContainer;

Monster::Monster(Fields &fields, Pacman &_pacman, float x_ini, float y_ini)
    : Agent(fields, x_ini, y_ini),
      random_dir(0,3),
      engine(dev()),
      pacman(_pacman) {}


void Monster::UpdateDirection(){
 
  //int randomdirection = random_dir(engine);
  std::vector<Direction> order = DirectionPreference();

  for(Direction _direction : order){
    if(_direction != opposite[direction]){  // not allowed to go in opposite direction
      directionchange = _direction;         // propose direction change (like a key stroke)
      if (ChangeDirection()){break;}        // if changed successfully -> done
    }
  }
   
}


std::vector<Agent::Direction> Monster::DirectionPreference(){
  //will move in direction of pacman, preferably in the farther dimension

  std::vector<Direction> order;
  int x_delta = pacman.getPosX() - pos.x;
  int y_delta = pacman.getPosY() - pos.y;

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


