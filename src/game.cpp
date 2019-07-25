#include "game.h"
#include <iostream>
#include "SDL.h"
#include <cmath>

Game::Game(std::string filename_map)
    : fields(filename_map), 
      pacman(fields, 4, 4),
      monster1(fields,pacman, 10,8),
      monster2(fields,pacman, 10,10),
      monster3(fields,pacman, 10,16),
      monster4(fields,pacman, 10,18) {
        Monster::MonsterContainer.push_back(&monster1);
        Monster::MonsterContainer.push_back(&monster2);
        Monster::MonsterContainer.push_back(&monster3);
        Monster::MonsterContainer.push_back(&monster4);
      }


void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, pacman); // can remove fields
    Update();
    renderer.Render(pacman, food, fields );

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every tenth, update the window title.
    if (frame_end - title_timestamp >= 100) {
      renderer.UpdateWindowTitle(fields.getFoodLeft(), 1000*frame_count/(frame_end - title_timestamp));
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

  pacman.Update();
  for (Monster * monster : Monster::MonsterContainer){
    
    monster->Update(); //update monster

    //check if monster kills pacman
    if (pacman.getPosX() == monster->getPosX() && pacman.getPosY() == monster->getPosY()){
      pacman.die();
      return;
    }

  }
  
  // Check if there's food over here 
  if(fields.eatFood(pacman.getPosX() , pacman.getPosY()))
    score++; //can remove score (or base it on time or so)
  
  

}

int Game::GetScore() const { return score; }

