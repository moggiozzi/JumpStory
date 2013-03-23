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
Rect    entryRects   [ entryCount ];

bool Menu::init(){
  bool res = true;
  ResourceManager::loadImage("res/s_on.png", &onTex);
  ResourceManager::loadImage("res/s_off.png", &offTex);
  for(uint i=0; i<entryCount; i++ )
  {    
    ResourceManager::loadImage(pathToEntryTexture[i], &entryTextures[i]);

    entryRects[i].size = entryTextures[i].size;
    if ( entryRects[i].width > GLHelper::getWidth() )
      entryRects[i].width = GLHelper::getWidth();
    entryRects[i].x = (GLHelper::getWidth() - entryRects[i].width) / 2;
    if ( i>0 )
      entryRects[i].y = entryRects[i-1].getBottom() + 20;
    else
      entryRects[i].y = 20;
  }
  return res;
}

void Menu::draw(){
  for ( uint i=0; i<entryCount; i++) {
    GLHelper::drawTexture(&entryTextures[i], entryRects[i]);
    if ( i == ME_SOUND )
    {
      if ( getSoundState() == true )
        GLHelper::drawTexture(&onTex, entryRects[i].getRight()+5, entryRects[i].y);
      else
        GLHelper::drawTexture(&offTex, entryRects[i].getRight()+5, entryRects[i].y);
    }
  }
}

void Menu::touch(int x, int y){
  GameState gState = getGameState();
  if ( entryRects[ ME_PLAY ].isContain( x, y ) )
    setGameState( GS_INGAME );
  else if ( entryRects[ ME_SOUND ].isContain( x, y ) )
    changeSoundState();
  else if ( entryRects[ ME_EXIT ].isContain( x, y ) )
    setGameState( GS_EXIT );
}

void Menu::keyDown(uint keyCode){
  if (keyCode == KEY_ESC){
    setGameState(GS_EXIT);
    return;
  }
}
