#include "Game.h"

#include "GLHelper.h"
#include "ResourceManager.h"
#include "AudioHelper.h"
#include "GameState.h"

Game::Game(){}

bool Game::init(){
  bool res = true;
  setGameState(GS_MENU);
  res = res && menu.init();
  res = res && world.init();
  int sId;
  res = res && AudioHelper::open("res/main.ogg",sId);
  AudioHelper::update();
  AudioHelper::play(sId,false); // todo true
  return res;
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
    dt=0.06f; // �� ������� ��������: ������ 16����/���
  fps.add(dt);
  GameState gState = getGameState();
  switch (gState){
  case GS_INITLEVEL:
    world.initLevel();
    setGameState( GS_INGAME );
    //break;
  case GS_INGAME:
    world.update(dt);
    break;
  default:
    menu.update(dt);
    break;
  }
}

bool Game::keyDown(uint keyCode){
  GameState gState = getGameState();
  switch (gState){
  case GS_INGAME:
    return world.keyDown(keyCode);
  break;
  default:
    return menu.keyDown(keyCode);
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