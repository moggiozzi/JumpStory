#include "Character.h"

Character::Character(Texture *charTex){
  sprite = new Sprite(charTex);
}

void Character::draw(){
  sprite->draw(pos.x - worldX,GLHelper::getHeight() - (pos.y - worldY));
}