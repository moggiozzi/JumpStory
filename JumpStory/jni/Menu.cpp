#include "Menu.h"
#include "ResourceManager.h"
#include "GameState.h"
#include "Settings.h"

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

  ME_INPUT_METHOD,
  ME_DISPLAY_ORIENTATION,

  ME_ENTRY_COUNT
};

const uint entryCount = ME_ENTRY_COUNT;
Texture entryTextures[ entryCount ];
Texture onTex, offTex;
Rect<int> entryRects [ entryCount ];
uint textSize=32;
Rect<int> inputMethod;
Rect<int> displayOrientation;

bool Menu::init(){
  textSize = std::min(GLHelper::getWidth(), GLHelper::getHeight()) / 10;

  int dy = textSize;
  //dy = dy>0 ? dy : 0;
  entryRects[ME_TITLE1].set(GLHelper::getWidth()/2-4*textSize/2,dy,4*textSize, textSize); //jump
  entryRects[ME_TITLE2].set(GLHelper::getWidth()/2-5*textSize/2,textSize+dy,5*textSize, textSize);//story
  entryRects[ME_PLAY].set(GLHelper::getWidth()/2-4*textSize/2,4*textSize+dy,4*textSize,textSize);//play
  entryRects[ME_EXIT].set(GLHelper::getWidth()/2-4*textSize/2,6*textSize+dy,4*textSize,textSize);//exit

  //dy = (GLHelper::getHeight()-6*textSize)/2;
  //dy = dy>0 ? dy : 0;
  entryRects[ME_PAUSE].set(GLHelper::getWidth()/2-5*textSize/2,dy,5*textSize, textSize);//pause
  entryRects[ME_RESUME].set(GLHelper::getWidth()/2-6*textSize/2,3*textSize+dy,6*textSize,textSize);//resume
  entryRects[ME_MENU].set(GLHelper::getWidth()/2-4*textSize/2,(int)(4.5*textSize)+dy,4*textSize,textSize);//menu

  //dy = (GLHelper::getHeight()-4*textSize)/2;
  //dy = dy>0 ? dy : 0;
  entryRects[ME_GAMEOVER].set(GLHelper::getWidth()/2-8*textSize/2,dy,8*textSize, textSize);//GameOver
  entryRects[ME_TRYAGAIN].set(GLHelper::getWidth()/2-8*textSize/2,3*textSize+dy,8*textSize,textSize);//TryAgain
  
  entryRects[ME_INPUT_METHOD].set(0,GLHelper::getHeight()-textSize,textSize,textSize);
  entryRects[ME_DISPLAY_ORIENTATION].set(GLHelper::getWidth()-textSize,GLHelper::getHeight()-textSize,textSize,textSize);
  entryRects[ME_INPUT_METHOD].setWidth( settings.getControlModeName().length() * textSize );

  return true;
}

void Menu::draw(){
  GLHelper::setColor(1.f,1.f,1.f);
  GameState gs = getGameState();
  switch (gs)
  {
  case GS_MENU:
    //GLHelper::setColor(1.0f,0.0f,0.0f);
    GLHelper::drawText(entryRects[ME_TITLE1].getPos(),"JUMP", textSize);
    GLHelper::drawText(entryRects[ME_TITLE2].getPos(),"STORY", textSize);
    GLHelper::setColor(1.0f,1.0f,1.0f);
    GLHelper::drawText(entryRects[ME_PLAY].getPos(),"Play",textSize);
    GLHelper::drawText(entryRects[ME_EXIT].getPos(),"Exit",textSize);
    break;
  case GS_PAUSE:
    //GLHelper::setColor(1.f,0.0f,0.0f);
    GLHelper::drawText(entryRects[ME_PAUSE].getPos(),"PAUSE",textSize);
    GLHelper::setColor(1.0f,1.0f,1.0f);
    GLHelper::drawText(entryRects[ME_RESUME].getPos(),"Resume",textSize);
    GLHelper::drawText(entryRects[ME_MENU].getPos(),"Menu",textSize);
    break;
  case GS_GAMEOVER:
    GLHelper::setColor(1.f,0.0f,0.0f);
    GLHelper::drawText(entryRects[ME_GAMEOVER].getPos(),"GameOver",textSize);
    GLHelper::setColor(1.0f,1.0f,1.0f);
    GLHelper::drawText(entryRects[ME_TRYAGAIN].getPos(),"TryAgain",textSize);
    GLHelper::drawText(entryRects[ME_MENU].getPos(),"Menu",textSize);
    break;
  default:
    break;
  }
  GLHelper::drawText(entryRects[ME_INPUT_METHOD].getPos(), settings.getControlModeName().c_str(), textSize);
  //GLHelper::drawText(entryRects[ME_DISPLAY_ORIENTATION].getPos(), settings.getOrientationName().c_str(), textSize);
}

void Menu::touch(int x, int y){
  Vector2<int> p(x,y);
  GameState gState = getGameState();
  switch (gState)
  {
  case GS_MENU:
    if ( entryRects[ ME_PLAY ].isContain( p ) )
      setGameState( GS_INGAME );
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
    if ( entryRects[ ME_TRYAGAIN ].isContain( p ) )
      setGameState( GS_INITLEVEL );
    else if ( entryRects[ ME_MENU ].isContain( p ) )
      setGameState( GS_MENU );
    break;
  }
  if ( entryRects[ME_INPUT_METHOD].isContain(p) )
  {
    settings.nextControlMode();
    entryRects[ME_INPUT_METHOD].setWidth( settings.getControlModeName().length() * textSize );
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
        setGameState(GS_INGAME);
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
    break;
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
    break;
  }
  return false;
}

