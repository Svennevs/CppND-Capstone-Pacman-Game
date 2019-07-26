#include "game.h"

//constructor calls all agent constructors
Game::Game(std::string filename_map)
    : fields(filename_map), 
      pacman(fields, 23, 6),
      blinky(fields,pacman, 15,11),
      pinky(fields,pacman, 15,11),
      inky(fields,pacman, 15,11),
      clyde(fields,pacman, 15,11) {
        Monster::MonsterContainer.push_back(&blinky);
        Monster::MonsterContainer.push_back(&pinky);
        Monster::MonsterContainer.push_back(&inky);
        Monster::MonsterContainer.push_back(&clyde);
        lastSwitchTimeStamp = SDL_GetTicks();
      }


void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  bool frightened = false;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, pacman); // can remove fields
    Update();
    renderer.Render(pacman, fields );

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_end = SDL_GetTicks();
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every tenth, update the window title.
    if (frame_end - title_timestamp >= 100) {
      renderer.UpdateWindowTitle(fields.getFoodLeft(), 1000*frame_count/(frame_end - title_timestamp), pacman.getLives());
      frame_count = 0;
      title_timestamp = frame_end;
    }   

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}



void Game::Update() {
  if (!pacman.isAlive() || fields.getFoodLeft()==0) return;

  // Update Pacman
  pacman.Update();

  // Update Monsters
  for (Monster * monster : Monster::MonsterContainer){
    monster->Update();
    //check for collision of pacman and monsters
    if (pacman.getPosY() == monster->getPosY() && pacman.getPosX() == monster->getPosX()){
      if(Monster::getState() != Monster::State::frightened){
        if(pacman.die()){ //true if there are remaining lives. Reset all positions
          pacman.setPos(23,6); 
          monster->setPosAll(15,11);
        }
        return;
      } else {
        monster->setPos(15,11); //monster returns to base instantly
      }
    }
  }

  // Check if there is food here 
  if(fields.eatFood(pacman.getPosY() , pacman.getPosX()))
    score++; 
  

  // Check if there is a powerUp here
  Uint32 frame_end=SDL_GetTicks();
  if(fields.eatPowerUp(pacman.getPosY() , pacman.getPosX())){
    Monster::setState(Monster::State::frightened);
    lastSwitchTimeStamp = frame_end;
    switchInterval = durationFrightened;
  }

  // take care of monster state switching timers
  if (frame_end - lastSwitchTimeStamp >= switchInterval){
    switch (Monster::getState()){
      case Monster::State::frightened:
        Monster::setState( Monster::State::chase );
        switchInterval = durationChase;
        break;
      case Monster::State::chase:
        Monster::setState( Monster::State::scatter );
        switchInterval = durationScatter;
        break;
      case Monster::State::scatter:
        Monster::setState( Monster::State::chase );
        switchInterval = durationChase;
        break;
    }
    lastSwitchTimeStamp = frame_end;
  }

    
}

int Game::GetScore() const { return score; }

