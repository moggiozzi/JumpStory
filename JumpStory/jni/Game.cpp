#include "Game.h"

#include "GLHelper.h"
#include "ResourceManager.h"

Game::Game(){
  world.init();
}

void Game::draw(){
  GLHelper::clear(0, 0, 0);

  world.draw();

  char str[16];
  sprintf(str,"fps:%d",fps.getFps());
  GLHelper::drawText(0, 0, str);

  GLHelper::swapBuffers();
}

void Game::update(float dt){
  if(dt>0.06f)
    dt=0.06f;
  fps.add(dt);
  world.update(dt);
}

void Game::keyDown(uint keyCode){
  world.keyDown(keyCode);
}

void Game::touch(int x, int y){
  world.touch(x,y);
}