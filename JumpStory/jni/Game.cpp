#include "Game.h"

#include "GLHelper.h"
#include "ResourceManager.h"

void Game::init(android_app* app){
    GLHelper::init(app->window);

	ResourceManager::init(app->activity);

	ResourceManager::loadImage("image.png");
	ResourceManager::loadImage("flower.png");

	//uint fid = ResourceManager::loadImage("font.png");
	//mTexture *fontTexture = ResourceManager::getTexture(fid);
	//GLHelper::setFontTexture(fontTexture);
}

void Game::draw(){
	GLHelper::clear(1, 0, 0);
	GLHelper::setColor(0,0,1);
	glEnableClientState(GL_VERTEX_ARRAY);
	GLHelper::drawLine2d(0,0,160,240);
    mTexture* texture = ResourceManager::getTexture(1);
    isnull("texture 1",texture);
    GLHelper::drawTexture(texture, 50, 50);

    //GLHelper::drawText(-GLHelper::getWidth()/2, GLHelper::getHeight()/2,"Hello world!");
    texture = ResourceManager::getTexture(2);
    GLHelper::drawTexture(texture, 150, 200);

    eglSwapBuffers(GLHelper::display, GLHelper::surface);
}

void Game::doStep(float dt){

}
