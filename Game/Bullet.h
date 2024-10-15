#pragma once

#include "GameObject.h"
#include <glm/glm.hpp>
#include <glfw3.h>

using namespace glm;

class Bullet : public GameObject
{
public:
    Bullet(vec3 position, vec3 direction);
    void update();

private:
    const float speed = 4.0f;
    vec3 direction;
};
