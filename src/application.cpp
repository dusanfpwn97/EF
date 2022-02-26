#include "application.h"

#include <iostream>

#include <SDL.h>

#include "glad/glad.h"

namespace ef
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::run()
	{
		while (true);
	}
	void Application::print()
	{
        SDL_Window* window = nullptr;

        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cout << "SDL could not be initialized: " <<
                SDL_GetError();
        }
        else { std::cout << "116\n"; }

        // Before we create our window, specify OpenGL version
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        // Request a window to be created for our platform
        // The parameters are for the title, x and y position,
        // and the width and height of the window.
        window = SDL_CreateWindow("C++ SDL2 Window",
            500,
            520,
            640,
            480,
            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

        // OpenGL setup the graphics context
        SDL_GLContext context;
        context = SDL_GL_CreateContext(window);

        // Setup our function pointers
        gladLoadGLES2Loader(SDL_GL_GetProcAddress);


        float positions[6] =
        {
            -0.5, -0.5,
            0.0, 0.5,
            0.5, -0.5
        };

        unsigned int buffer;
        glGenBuffers(1, &buffer);
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);



        // Infinite loop for our application
        bool gameIsRunning = true;
        while (gameIsRunning) {
            glViewport(0, 0, 640, 480);

            SDL_Event event;
            // Start our event loop
            while (SDL_PollEvent(&event)) {
                // Handle each specific event
                if (event.type == SDL_QUIT) {
                    gameIsRunning = false;
                }
                if (event.type == SDL_MOUSEMOTION) {

                }
                if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_0) {
                        //std::cout << "0 was pressed\n";
                    }

                }
                // Retrieve the state of all of the keys
                // Then we can query the scan code of one or more
                // keys at a time
                const Uint8* state = SDL_GetKeyboardState(NULL);
                if (state[SDL_SCANCODE_RIGHT]) {
                    std::cout << "right arrow key is pressed\n";
                }
            }

            glClearColor(0.15f, 0.17f, 0.15f, 1.0f);
            glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);


            glDrawArrays(GL_TRIANGLES, 0, 3);

            SDL_GL_SwapWindow(window);
        }

        // We destroy our window. We are passing in the pointer
        // that points to the memory allocated by the 
        // 'SDL_CreateWindow' function. Remember, this is
        // a 'C-style' API, we don't have destructors.
        SDL_DestroyWindow(window);

        // We safely uninitialize SDL2, that is, we are
        // taking down the subsystems here before we exit
        // We add a delay in order to see that our window
        // has successfully popped up.

        // our program.
        SDL_Quit();
        
	}
}