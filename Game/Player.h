#pragma once

#include "GameObject.h"
#include <glm/glm.hpp>
#include <glfw3.h>

using namespace glm;

struct keyInfo
{
    bool pressed = false;
    bool held = false;
};

class Player : public GameObject
{
public:
    Player(vec3 position);
    void handleInput(keyInfo keys[]);

private:
    const float speed = 1.4f;
    void shoot(int dx, int dy);
};
