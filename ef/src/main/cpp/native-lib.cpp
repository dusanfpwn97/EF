#include <jni.h>
#include <string>
#include <SDL.h>

extern "C" JNIEXPORT jstring JNICALL
Java_com_eferus_ef_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello 1 C++";

    SDL_Window* window;
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
            "An SDL2 window",                  // window title
            SDL_WINDOWPOS_UNDEFINED,           // initial x position
            SDL_WINDOWPOS_UNDEFINED,           // initial y position
            640,                               // width, in pixels
            480,                               // height, in pixels
            SDL_WINDOW_OPENGL                  // flags - see below
    );


    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        //printf("Could not create window: %s\n", SDL_GetError());
        printf("Could not create window");

    }

    return env->NewStringUTF(hello.c_str());
}