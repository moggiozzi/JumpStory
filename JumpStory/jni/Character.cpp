#include "Character.h"

Character::Character(Texture *charTex){
  sprite = new Sprite(charTex);
}

Character::~Character(){
  delete sprite;
}

void Character::draw(){
  sprite->draw( (int) (pos.x - worldX), (int) (GLHelper::getHeight() - (pos.y - worldY)));
}