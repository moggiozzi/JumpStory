#include "Character.h"
#include "WorldInfo.h"

Character::Character(Texture *charTex){
  sprite = new Sprite(charTex);
}

Character::~Character(){
  delete sprite;
}

void Character::draw(){
  sprite->draw( worldToDeviceX(pos.x()), worldToDeviceY(pos.y()));//.x - worldX), (int) (GLHelper::getHeight() - (pos.y - worldY)));
}