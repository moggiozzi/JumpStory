#include "Game.h"

#include "GLHelper.h"
#include "ResourceManager.h"
#include "AudioHelper.h"
#include "GameState.h"

Game::Game(){
  setGameState(GS_MENU);
  menu.init();
  world.init();
}

void Game::drawFps(){
  static char str[16];
  sprintf(str,"fps:%d",fps.getFps());
  GLHelper::drawText(0, 0, str);
}
void Game::draw(){
  GLHelper::clear(0, 0, 0);
  GameState gState = getGameState();
  switch (gState)
  {
  case GS_INGAME:
    world.draw();
    break;
  default:
    menu.draw();
    break;
  }
  drawFps();
  GLHelper::swapBuffers();
}

void Game::update(float dt){
  if ( dt <= 0 ) // ???
    return;
  if(dt>0.06f)
    dt=0.06f; // Не хватает ресурсов: меньше 16кадр/сек
  fps.add(dt);
  GameState gState = getGameState();
  switch (gState){
  case GS_INGAME:
    world.update(dt);
    break;
  default:
    menu.update(dt);
    break;
  }
}

void Game::keyDown(uint keyCode){
  GameState gState = getGameState();
  switch (gState){
  case GS_INGAME:
    world.keyDown(keyCode);
  break;
  default:
    menu.keyDown(keyCode);
  break;
  }
}

void Game::touch(int x, int y){
  GameState gState = getGameState();
  switch (gState){
  case GS_INGAME:
      world.touch(x,y);
    break;
  default:
      menu.touch(x,y);
    break;
  }
}