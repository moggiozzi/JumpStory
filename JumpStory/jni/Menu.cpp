#include "Menu.h"
#include "ResourceManager.h"
#include "GameState.h"

enum MenuEntry{ 
  ME_TITLE, 
  ME_PLAY, 
  ME_SOUND,
  ME_EXIT 
};

const uint entryCount = 4;
const char* pathToEntryTexture[entryCount] = { 
  "res/s_title.png",
  "res/s_play.png",
  "res/s_sound.png",
  "res/s_exit.png"
};

Texture entryTextures[ entryCount ];
Texture onTex, offTex;
Rect<int> entryRects   [ entryCount ];

bool Menu::init(){
  bool res = true;
  ResourceManager::loadImage("res/s_on.png", &onTex);
  ResourceManager::loadImage("res/s_off.png", &offTex);
  for(uint i=0; i<entryCount; i++ )
  {    
    ResourceManager::loadImage(pathToEntryTexture[i], &entryTextures[i]);

    entryRects[i].setSize( entryTextures[i].size );
    if ( entryRects[i].getWidth() > GLHelper::getWidth() )
      entryRects[i].setWidth( GLHelper::getWidth() );
    entryRects[i].setX((GLHelper::getWidth() - entryRects[i].getWidth()) / 2);
    if ( i>0 )
      entryRects[i].setY( entryRects[i-1].getBottom() + 20 );
    else
      entryRects[i].setY( 20 );
  }
  return res;
}

void Menu::draw(){
  GLHelper::setColor(1.0f,1.0f,1.0f);
  for ( uint i=0; i<entryCount; i++) {
    GLHelper::drawTexture(&entryTextures[i], entryRects[i]);
    if ( i == ME_SOUND )
    {
      if ( getSoundState() == true )
        GLHelper::drawTexture(&onTex, entryRects[i].getRight()+5, entryRects[i].y());
      else
        GLHelper::drawTexture(&offTex, entryRects[i].getRight()+5, entryRects[i].y());
    }
  }
}

void Menu::touch(int x, int y){
  Vector2<int> p(x,y);
  GameState gState = getGameState();
  if ( entryRects[ ME_PLAY ].isContain( p ) )
    setGameState( GS_INITLEVEL );
  else if ( entryRects[ ME_SOUND ].isContain( p ) )
    changeSoundState();
  else if ( entryRects[ ME_EXIT ].isContain( p ) )
    setGameState( GS_EXIT );
}

bool Menu::keyDown(uint keyCode){
  switch (keyCode)
  {
    case KEY_ESC:
      setGameState(GS_EXIT);
      return true;
    break;
    case KEY_ENTER:
      setGameState(GS_INITLEVEL);
      return true;
    break;
    default:
      return false;
  }
}
