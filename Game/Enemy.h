#pragma once

#include "GameObject.h"
#include <glm/glm.hpp>

using namespace glm;

class Enemy : public GameObject
{
public:
    Enemy(vec3 position);
    void update(vec3 playerPosition);

private:
    const float speed = 0.5f;
};