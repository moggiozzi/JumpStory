//#include <errno.h>
// !!! only in codding
//#include <android/input.h> // for AInputEvent, AINPUT_EVENT_TYPE_MOTION, ...
//#include <android/native_app_glue/android_native_app_glue.h> // for android_app
// !!! only in codding !!!

#include <time.h>
#include "Game.h"
#include "ResourceManager.h"
#include "GLHelper.h"

clock_t lastTime=0, currentTime=0;

Game *game;

#ifdef __ANDROID__
#include <unistd.h> /* sleep() */
#include <android/sensor.h>
//static JavaVM *jvm;
JNIEnv *jni;
struct engine {
  struct android_app* app;
  ASensorManager* sensorManager;
  const ASensor* accelerometerSensor;
  ASensorEventQueue* sensorEventQueue;
  int animating;
  //struct saved_state state;
};

static int32_t engine_handle_input(struct android_app* app, AInputEvent* event) {
  struct engine* engine = (struct engine*)app->userData;
  if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION &&
    AMotionEvent_getAction(event) == AMOTION_EVENT_ACTION_DOWN) {
      float x = AMotionEvent_getX(event, 0);
      float y = AMotionEvent_getY(event, 0);
      game->touch(x,y);
      engine->animating = 1;
      return 1;
  }
  return 0;
}

static void engine_handle_cmd(struct android_app* app, int32_t cmd) {
  struct engine* engine = (struct engine*)app->userData;
  switch (cmd) {
  case APP_CMD_SAVE_STATE:
    //engine->app->savedState = malloc(sizeof(struct saved_state));
    //*((struct saved_state*)engine->app->savedState) = engine->state;
    //engine->app->savedStateSize = sizeof(struct saved_state);
    break;
  case APP_CMD_INIT_WINDOW:
    if (engine->app->window != NULL) {
      ResourceManager::init(engine->app->activity);
      GLHelper::init(engine->app->window);
      game = new Game();
      game->draw();
    }
    break;
  case APP_CMD_TERM_WINDOW:
    break;
  case APP_CMD_GAINED_FOCUS:
    // When our app gains focus, we start monitoring the accelerometer.
    if (engine->accelerometerSensor != NULL) {
      ASensorEventQueue_enableSensor(engine->sensorEventQueue,
        engine->accelerometerSensor);
      // We'd like to get 60 events per second (in us).
      ASensorEventQueue_setEventRate(engine->sensorEventQueue,
        engine->accelerometerSensor, (1000L/60)*1000);
    }
    break;
  case APP_CMD_LOST_FOCUS:
    // When our app loses focus, we stop monitoring the accelerometer.
    // This is to avoid consuming battery while not being used.
    if (engine->accelerometerSensor != NULL) {
      ASensorEventQueue_disableSensor(engine->sensorEventQueue,
        engine->accelerometerSensor);
    }
    // Also stop animating.
    engine->animating = 0;
    game->draw();
    break;
  }
}

void android_main(struct android_app* state) {
#ifndef NDEBUG
  // ожидание подключения отладчика
  //volatile bool bGo = false; // поймать
  volatile bool bGo = true; // не ловить
  while(!bGo) {
    sleep(1);
  }
#endif
  struct engine engine;
  // Make sure glue isn't stripped.
  app_dummy();

  memset(&engine, 0, sizeof(engine));
  state->userData = &engine;
  state->onAppCmd = engine_handle_cmd;
  state->onInputEvent = engine_handle_input;
  engine.app = state;

  // Prepare to monitor accelerometer
  engine.sensorManager = ASensorManager_getInstance();
  engine.accelerometerSensor = ASensorManager_getDefaultSensor(engine.sensorManager,
    ASENSOR_TYPE_ACCELEROMETER);
  engine.sensorEventQueue = ASensorManager_createEventQueue(engine.sensorManager,
    state->looper, LOOPER_ID_USER, NULL, NULL);

  if (state->savedState != NULL) {
    // We are starting with a previous saved state; restore from it.
    //engine.state = *(struct saved_state*)state->savedState;
  }

  while (1) {
    // Read all pending events.
    int ident;
    int events;
    struct android_poll_source* source;
    // If not animating, we will block forever waiting for events.
    // If animating, we loop until all events are read, then continue
    // to draw the next frame of animation.
    while ((ident=ALooper_pollAll(engine.animating ? 0 : -1, NULL, &events,
      (void**)&source)) >= 0) {
        // Process this event.
        if (source != NULL) {
          source->process(state, source);
        }
        // If a sensor has data, process it now.
        if (ident == LOOPER_ID_USER) {
          if (engine.accelerometerSensor != NULL) {
            ASensorEvent event;
            while (ASensorEventQueue_getEvents(engine.sensorEventQueue,
              &event, 1) > 0) {
                //                        LOGI("x=%f y=%f z=%f",
                //                                event.acceleration.x, event.acceleration.y,
                //                                event.acceleration.z);
            }
          }
        }
        if (state->destroyRequested != 0) {
          //engine_term_display(&engine);
          return;
        }
    }

    if (engine.animating) {
      currentTime = clock();
      game->update((float)(currentTime-lastTime)/CLOCKS_PER_SEC);
      game->draw();
      lastTime = currentTime;
    }
  }
}
#elif _WIN32
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                   LPSTR lpCmdLine, int iCmdShow){
                     WNDCLASS wc;
                     HWND hWnd;
                     MSG msg;
                     BOOL quit = FALSE;
                     float theta = 0.0f;
                     // register window class
                     wc.style = CS_OWNDC;
                     wc.lpfnWndProc = WndProc;
                     wc.cbClsExtra = 0;
                     wc.cbWndExtra = 0;
                     wc.hInstance = hInstance;
                     wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
                     wc.hCursor = LoadCursor( NULL, IDC_ARROW );
                     wc.hbrBackground = (HBRUSH)GetStockObject( BLACK_BRUSH );
                     wc.lpszMenuName = NULL;
                     wc.lpszClassName = "JumpStory";
                     RegisterClass( &wc );
                     // create main window
                     hWnd = CreateWindow( 
                       "JumpStory", "JumpStory", 
                       WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
                       400, 100, // window coords 
                       320, 480, // GLHelper::getWidth(), GLHelper::getHeight(), // window size
                       NULL, NULL, hInstance, NULL );
                     // enable OpenGL for the window
                     ResourceManager::init();
                     GLHelper::init( hWnd );
                     game = new Game();
                     currentTime = lastTime = clock();
                     // program main loop
                     while ( !quit )	{
                       // check for messages
                       if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE )  ){
                         // handle or dispatch messages
                         if ( msg.message == WM_QUIT ) {
                           quit = TRUE;
                         } else {
                           TranslateMessage( &msg );
                           DispatchMessage( &msg );
                         }
                       } else {
                         // Sleep(300); // for test
                         currentTime = clock();
                         // update
                         game->update((float)(currentTime-lastTime)/CLOCKS_PER_SEC);
                         lastTime = currentTime;
                         // draw
                         game->draw();
                       }
                     }
                     // shutdown OpenGL
                     GLHelper::terminate();
                     // destroy the window explicitly
                     DestroyWindow( hWnd );
                     return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
  switch (message) {
  case WM_CREATE:
    return 0;
  case WM_CLOSE:
    PostQuitMessage( 0 );
    return 0;
  case WM_DESTROY:
    return 0;
  case WM_KEYDOWN: {
    if (wParam==VK_ESCAPE) {
      PostQuitMessage(0);
    } else {
      game->keyDown(wParam);
    }
    return 0;
  }
  default:
    return DefWindowProc( hWnd, message, wParam, lParam );
  }
}

#elif __linux__
#endif
