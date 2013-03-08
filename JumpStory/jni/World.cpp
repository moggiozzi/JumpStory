#include "World.h"

void World::draw(){
  collisionLayer.draw();
}

void World::init(){
  collisionLayer.generate();
}