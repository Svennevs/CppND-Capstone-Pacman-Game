## Summary
This version of the game Pacman was my final project submission for the Udacity C++ Nanodegree. It has most relevant features of the original game, but some details were omitted to keep it simple.
The main source for the game rules was this: https://gameinternals.com/post/2072558330/understanding-pac-man-ghost-behavior. The four different ghost characters (Blinky, Pinky, Inky, Clyde) are included. Rendering is basic: all elements are squared blocks. 
* Pacman is yellow
* Empty paths are black
* Paths with food are dark yellow
* Paths with powerups are orange
* Walls are grey
* The monsters are colored Red, Pink, Orange and Cyan

Operation is through the arrow keys on the keybard. There is one level and pacman has 3 lives to complete it. Careful, there is no break after losing a life.

## Code structure
The code was based on the snakeGame example. The game loop of this example was kept intact.
* the snake class was replaced by an Agent class, with derived classes Pacman and Monster
* the monster class has derived classes Blinky, Pinky, Inky and Clyde
* a fields class was added. This loads the map (level1.map) from the data folder. It is used by the Game,Agent and Renderer class

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Rubric satisfaction
* The project demonstrates an understanding of C++ functions and control structures  (I have tried to organise the project into functions)
* The project reads data from a file and process the data, or the program writes data to a file (it reads the map from ./data/level1.map)
* The project uses Object Oriented Programming techniques (I made some classes, like Agent, Pacman, Monster, Fields)
* Classes use appropriate access specifiers for class members (I tried to, please see agents.h and agent.cpp)
* Class constructors utilize member initialization lists (for example the Agent class)
* Classes abstract implementation details from their interfaces (I tried to, please see agents and game)
* Classes encapsulate behavior (worked with getters and setters)
* Classes follow an appropriate inheritance hierarchy (Agent -> Pacman or Monsters -> Blinky/Pinky/Inky/Clyde. I specified override functions)
* Derived class functions override virtual base class functions.
* Templates generalize functions in the project (please see Wrap function in Agent.cpp)
* The project makes use of references in function declarations (reference to field object in Agent and Renderer)

The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.



