#include "Sprite.h"

void Sprite::draw( int x, int y ) {
  GLHelper::drawTexture(texture_, x, y);
}

void Sprite::draw(Vector2<int>& pos, float angle){
  GLHelper::drawTexture(texture_, pos, angle);
}