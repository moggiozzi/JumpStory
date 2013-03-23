#include "GameState.h"

GameState gameState;
bool isSoundEnable = true;

GameState getGameState(){
  return gameState;
}
void setGameState(GameState gState){
  gameState = gState;
}

void setSoundState(bool isEnable){
  isSoundEnable = false;
}
void changeSoundState(){
  isSoundEnable = !isSoundEnable;
}
bool getSoundState(){
  return isSoundEnable;
}