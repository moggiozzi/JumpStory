#include "Menu.h"
#include "ResourceManager.h"
#include "GameState.h"

enum MenuEntry{ 
  ME_TITLE1,
  ME_TITLE2, 
  ME_PLAY, 
  ME_EXIT,

  ME_PAUSE,
  ME_RESUME,
  ME_MENU,

  ME_GAMEOVER,
  ME_TRYAGAIN,


  ME_ENTRY_COUNT
};

const uint entryCount = ME_ENTRY_COUNT;
Texture entryTextures[ entryCount ];
Texture onTex, offTex;
Rect<int> entryRects [ entryCount ];
uint textSize=32;

bool Menu::init(){
  if ( GLHelper::getWidth()/64 > 8 )
    textSize = 64;
  else if ( GLHelper::getWidth()/32 > 8 )
    textSize = 32;
  else textSize = 16;
  entryRects[ME_TITLE1].set(GLHelper::getWidth()/2-4*textSize/2,textSize,4*textSize, textSize); //jump
  entryRects[ME_TITLE2].set(GLHelper::getWidth()/2-5*textSize/2,2*textSize,5*textSize, textSize);//story
  entryRects[ME_PLAY].set(GLHelper::getWidth()/2-4*textSize/2,4*textSize,4*textSize,textSize);//play
  entryRects[ME_EXIT].set(GLHelper::getWidth()/2-4*textSize/2,6*textSize,4*textSize,textSize);//exit

  entryRects[ME_PAUSE].set(GLHelper::getWidth()/2-5*textSize/2,1.5*textSize,5*textSize, textSize);//pause
  entryRects[ME_RESUME].set(GLHelper::getWidth()/2-6*textSize/2,3*textSize,6*textSize,textSize);//resume
  entryRects[ME_MENU].set(GLHelper::getWidth()/2-4*textSize/2,4.5*textSize,4*textSize,textSize);//menu

  entryRects[ME_GAMEOVER].set(GLHelper::getWidth()/2-8*textSize/2,1.5*textSize,8*textSize, textSize);//GameOver
  entryRects[ME_TRYAGAIN].set(GLHelper::getWidth()/2-8*textSize/2,3*textSize,8*textSize,textSize);//TryAgain
  //toMenu
  return true;
}

void Menu::draw(){
  GLHelper::setColor(1.f,1.f,1.f);
  GameState gs = getGameState();
  switch (gs)
  {
  case GS_MENU:
      GLHelper::drawText(entryRects[ME_TITLE1].getPos(),"JUMP", textSize);
      GLHelper::drawText(entryRects[ME_TITLE2].getPos(),"STORY", textSize);
      GLHelper::drawText(entryRects[ME_PLAY].getPos(),"Play",textSize);
      GLHelper::drawText(entryRects[ME_EXIT].getPos(),"Exit",textSize);
    break;
  case GS_PAUSE:
      GLHelper::drawText(entryRects[ME_PAUSE].getPos(),"PAUSE",textSize);
      GLHelper::drawText(entryRects[ME_RESUME].getPos(),"Resume",textSize);
      GLHelper::drawText(entryRects[ME_MENU].getPos(),"Menu",textSize);
    break;
  case GS_GAMEOVER:
      GLHelper::drawText(entryRects[ME_GAMEOVER].getPos(),"GameOver",textSize);
      GLHelper::drawText(entryRects[ME_TRYAGAIN].getPos(),"TryAgain",textSize);
      GLHelper::drawText(entryRects[ME_MENU].getPos(),"Menu",textSize);
    break;
  default:
    break;
  }
}

void Menu::touch(int x, int y){
  Vector2<int> p(x,y);
  GameState gState = getGameState();
  switch (gState)
  {
  case GS_MENU:
    if ( entryRects[ ME_PLAY ].isContain( p ) )
      setGameState( GS_INITLEVEL );
    //else if ( entryRects[ ME_SOUND ].isContain( p ) )
    //  changeSoundState();
    else if ( entryRects[ ME_EXIT ].isContain( p ) )
      setGameState( GS_EXIT );
    break;
  case GS_PAUSE:
    if ( entryRects[ ME_RESUME ].isContain( p ) )
      setGameState( GS_INGAME );
    else if ( entryRects[ ME_MENU ].isContain( p ) )
      setGameState( GS_MENU );
    break;
  case GS_GAMEOVER:
    if ( entryRects[ ME_RESUME ].isContain( p ) )
      setGameState( GS_INITLEVEL );
    else if ( entryRects[ ME_MENU ].isContain( p ) )
      setGameState( GS_MENU );
    break;
  }
}

bool Menu::keyDown(uint keyCode){
   GameState gState = getGameState();
  switch (gState)
  {
  case GS_MENU:
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
    }
    break;
  case GS_PAUSE:
    switch (keyCode)
    {

      case KEY_ESC:
        setGameState(GS_MENU);
        return true;
      break;
      case KEY_ENTER:
        setGameState(GS_INGAME);
        return true;
      break;
    }
  case GS_GAMEOVER:
    switch (keyCode)
    {

      case KEY_ESC:
        setGameState(GS_MENU);
        return true;
      break;
      case KEY_ENTER:
        setGameState(GS_INITLEVEL);
        return true;
      break;
    }
  }
  return false;
}
