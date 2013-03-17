#include "Character.h"

Character::Character(Texture *charTex){
  sprite = new Sprite(charTex);
}

void Character::draw(){
  sprite->draw( (int) (pos.x - worldX), (int) (GLHelper::getHeight() - (pos.y - worldY)));
}