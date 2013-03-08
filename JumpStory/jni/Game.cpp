#include "Game.h"

#include "GLHelper.h"
#include "ResourceManager.h"
namespace{Texture t1;}
Game::Game(){
  ResourceManager::loadImage("image.png",&t1);
  world.init();
}

void Game::draw(){
  GLHelper::clear(1, 0, 0);
  GLHelper::setColor(0,0,1);
  //glEnableClientState(GL_VERTEX_ARRAY);
  GLHelper::drawLine2d(0,0,160,240);
  world.draw();

  GLHelper::drawTexture(&t1, 50, 50);

  //GLHelper::drawText(0, 16,"Hello world!");
  //texture = ResourceManager::getTexture(2);
  //GLHelper::drawTexture(texture, 150, 200);

  GLHelper::swapBuffers();
}

void Game::update(float dt){

}
