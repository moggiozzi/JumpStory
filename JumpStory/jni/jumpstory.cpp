#include <errno.h>
#include <android/sensor.h>
#include <unistd.h> /* sleep() */
#include <time.h>

#include "Global.h"
#include "Game.h"

//static JavaVM *jvm;
JNIEnv *jni;

clock_t lastTime=0, currentTime=0;

Game game;

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
        //engine->state.x = AMotionEvent_getX(event, 0);
        //engine->state.y = AMotionEvent_getY(event, 0);
        //game.touch(engine->state.x, engine->state.y);
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
            	game.init(app);
            	game.draw();
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
            game.draw();
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
        	//game.doStep((float)(currentTime-lastTime)/CLOCKS_PER_SEC);
            game.draw();
        	lastTime = currentTime;
        }
    }
}
