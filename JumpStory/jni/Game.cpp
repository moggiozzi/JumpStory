#include "Game.h"

#include "GLHelper.h"
#include "ResourceManager.h"
#include "AudioHelper.h"
#include "GameState.h"

Game::Game(){}
Texture bgTex;
bool Game::init(){
  bool res = true;
  setGameState(GS_MENU);
  res = res && menu.init();
  res = res && world.init();
  int sId;
  res = res && AudioHelper::open("res/main.ogg",sId);
  AudioHelper::update();
  AudioHelper::play(sId,false); // todo true

  ResourceManager::loadImage("res/bg.png",&bgTex);

  return res;
}

void Game::drawFps(){
  static char str[16];
  sprintf(str,"fps:%d",fps.getFps());
  GLHelper::setColor(1.f,1.f,1.f);
  GLHelper::drawText(0, 0, str);
}

void Game::draw(){
  GLHelper::clear(0, 0, 0);

  GLHelper::setColor(0.6f,0.6f,1.0f);
  uint x = (GLHelper::getWidth() - bgTex.getWidth())/2;
  uint y = (GLHelper::getHeight() - bgTex.getHeight())/2;
  GLHelper::drawTexture(&bgTex, x, y);

  GameState gState = getGameState();
  switch (gState)
  {
  case GS_INGAME:
    world.draw();
    break;
  case GS_PAUSE:
    world.draw(true);
    menu.draw();
    break;
  case GS_MENU: case GS_GAMEOVER:
    world.draw(false);
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
  case GS_INITLEVEL:
    world.initLevel();
    setGameState( GS_INGAME );
    break;
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