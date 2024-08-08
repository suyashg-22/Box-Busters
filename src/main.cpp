#include <game.hpp>

int main()
{ 

  //init srand
  std::srand(static_cast<unsigned>(time(NULL)));

  Game game;
  
  while(game.running() && !game.getendgame()){ 

    //update
    game.update();

    //render
    game.render();

  }
  return 0; 
}