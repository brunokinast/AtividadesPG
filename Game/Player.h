#pragma once

#include "GameObject.h"
#include <glm/glm.hpp>
#include <glfw3.h>
#include <functional>

using namespace std;

struct keyInfo
{
    bool pressed = false;
    bool held = false;
};

class Player : public GameObject
{
public:
    Player(vec3 position, function<void(vec3)> createBullet, vec4 limits);
    void handleInput(keyInfo keys[]);
    vec3 getSize() override;

private:
    const vec4 limits;
    const float speed = 1.4f;
    function<void(vec3)> createBullet;
    void shoot(int dx, int dy);
};
