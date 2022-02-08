#pragma once

#include "game_object.hpp"
#include "window.hpp"
#include "SDL_keyboard.h"

namespace ef {
    class KeyboardMovementController {
    public:
        struct KeyMappings {
            int moveLeft = SDLK_a;
            int moveRight = SDLK_d;
            int moveForward = SDLK_w;
            int moveBackward = SDLK_s;
            int moveUp = SDLK_e;
            int moveDown = SDLK_q;
            int lookLeft = SDLK_LEFT;
            int lookRight = SDLK_RIGHT;
            int lookUp = SDLK_UP;
            int lookDown = SDLK_DOWN;
        };

        void moveInPlaneXZ(const SDL_Event& sdlEvent, float dt, GameObject& gameObject);

        KeyMappings keys{};
        float moveSpeed{ 3.f };
        float lookSpeed{ 1.5f };
    };
}  // namespace ef