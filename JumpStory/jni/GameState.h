#ifndef GAME_STATE_H_
#define GAME_STATE_H_

#include "Global.h"

enum GameState{
  GS_MENU,
  GS_INITLEVEL,
  GS_INGAME,
  GS_GAMEOVER,
  GS_PAUSE,
  GS_EXIT
};

GameState getGameState();
void setGameState(GameState gState);

void setSoundState(bool isEnable);
void changeSoundState();
bool getSoundState();

#endif